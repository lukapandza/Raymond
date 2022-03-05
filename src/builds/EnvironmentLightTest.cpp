void
World::build() {

    int num_samples = 900;

    vp.set_hres(512);
    vp.set_vres(512);
    vp.set_samples(num_samples);
    vp.set_max_depth(24);

    background_color = black;

    tracer_ptr = new AreaLighting(this);
    //tracer_ptr = new PathTrace(this);
    //tracer_ptr = new GlobalTrace(this);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(3.5, 2.5, 20);
    pinhole_ptr->set_lookat(3.5, 2.5, 0);
    pinhole_ptr->set_view_distance(12.0);
    pinhole_ptr->set_zoom(100.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    Sampler* sampler_ptr = new MultiJittered(num_samples);

    // ambient:

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.0);
    set_ambient_light(ambient_ptr);

    AmbientOccluder* occluder_ptr = new AmbientOccluder;
    occluder_ptr->set_intensity(0.9);
    occluder_ptr->set_color(white);
    occluder_ptr->set_min(0.00);
    occluder_ptr->set_sampler(sampler_ptr);
    set_ambient_light(occluder_ptr);

    //light: 
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(64.0);
    emissive_ptr1->set_ce(1.0, 0.83, 0.6);

    ConcaveSphere* sphere_ptr = new ConcaveSphere;
    sphere_ptr->set_radius(1000000.0);
    sphere_ptr->set_material(emissive_ptr1);
    //add_object(sphere_ptr);

    EnvironmentLight* light_ptr = new EnvironmentLight;
    light_ptr->set_material(emissive_ptr1);
    light_ptr->set_sampler(sampler_ptr);
    light_ptr->set_shadows(true);
    add_light(light_ptr);

    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(0.25);
    mat->set_kd(1);
    mat->set_cd(1); // white

    //walls:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    RectangleObject* ceiling = new RectangleObject(1, 5, 1, 5, 0, 0, 0, 0, 20.1, 0, -1, 0);
    ceiling->set_material(mat);
    add_object(ceiling);

    Matte* mat_red = new Matte(*mat);
    mat_red->set_cd(.66, 0.17, 0.14);
    RectangleObject* west = new RectangleObject(1, 0, 1, 0, 5, 0, 0, 0, 20.1, 1, 0, 0);
    west->set_material(mat_red);
    add_object(west);

    RectangleObject* north = new RectangleObject(1, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 1);
    north->set_material(mat);
    add_object(north);

    RectangleObject* south = new RectangleObject(1, 0, 20.1, 5, 0, 0, 0, 5, 0, 0, 0, -1);
    south->set_material(mat);
    add_object(south);

    Matte* mat_green = new Matte(*mat);
    mat_green->set_cd(0.18, .48, 0.43);

    double window_depth = .25;
    double window_height = 1.5;
    double window_start_height = 3.0;
    double window_width = 1.0;

    Box* box_bottom = new Box(6, 0, 1, 6 + window_depth, window_start_height, 20.1);
    box_bottom->set_material(mat_green);
    add_object(box_bottom);

    Box* box_far = new Box(6, window_start_height, 1, 6 + window_depth, window_start_height + window_height, 3.5 - window_width * .5);
    box_far->set_material(mat_green);
    add_object(box_far);

    Box* box_near = new Box(6, window_start_height, 3.5 + window_width * .5, 6 + window_depth, window_start_height + window_height, 20.1);
    box_near->set_material(mat_green);
    add_object(box_near);

    Box* box_top = new Box(6, window_start_height + window_height, 1, 6 + window_depth, 5, 20.1);
    box_top->set_material(mat_green);
    add_object(box_top);



    //boxes:
    Instance* box1 = new Instance(new Box(-0.75, 0, -0.75, 0.75, 3.0, 0.75));
    box1->set_material(mat);
    box1->rotate_y(15);
    box1->translate(2.5, 0, 2.75);
    add_object(box1);

    Instance* box2 = new Instance(new Box(-0.75, 0, -0.75, 0.75, 1.5, 0.75));
    box2->set_material(mat);
    box2->rotate_y(-15);
    box2->translate(4.5, 0, 4);
    add_object(box2);
}