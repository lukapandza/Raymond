void
World::build() {

    /*
    * RUN HISTORY:
    *   2021-08-03 @ 13:59 ->   00:01:24
    *   2021-08-03 @ 14:08 ->   00:01:23 (changed trace_ray to pass by reference)
    *   2021-08-03 @ 15:29 ->   00:01:21 (see change in Matte::path_shade)
    *   2021-08-12 @ 12:55 ->   00:00:33 (switched to x64 build)
    *
    */
    int num_samples = 650;

    vp.set_hres(128);
    vp.set_vres(128);
    vp.set_samples(num_samples);
    vp.set_max_depth(10);

    background_color = black;
    tracer_ptr = new PathTrace(this);

    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(3.5, 2.5, 20);
    pinhole_ptr->set_lookat(3.5, 2.5, 0);
    pinhole_ptr->set_view_distance(12.0);
    pinhole_ptr->set_zoom(50.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:
    
    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.0);
    set_ambient_light(ambient_ptr);

    //light: 
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(64.0);
    emissive_ptr1->set_ce(1.0, 0.83, 0.6);

    Sampler* sampler_ptr = new MultiJittered(num_samples);

    RectangleObject* rectangle_ptr1 = new RectangleObject(3, 5, 4, 1, 0, 0, 0, 0, -1, 0, -1, 0);
    rectangle_ptr1->set_material(emissive_ptr1);
    rectangle_ptr1->set_sampler(sampler_ptr);
    add_object(rectangle_ptr1);

    AreaLight* area_light_ptr1 = new AreaLight;
    area_light_ptr1->set_object(rectangle_ptr1);
    area_light_ptr1->set_shadows(true);
    add_light(area_light_ptr1);

    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(0.0);
    mat->set_kd(0.8);
    mat->set_cd(1); // white

    //walls:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    Plane* ceiling = new Plane(Point3D(0, 5.0, 0), Normal(0.0024, -1, 0.00093));
    ceiling->set_material(mat);
    add_object(ceiling);

    Matte* mat_red = new Matte(*mat);
    mat_red->set_cd(1, 0.2, 0.2);
    Plane* west = new Plane(Point3D(1, 0, 0), Normal(1, 0, 0));
    west->set_material(mat_red);
    add_object(west);

    Plane* north = new Plane(Point3D(0, 0, 1), Normal(0, 0, 1));
    north->set_material(mat);
    add_object(north);

    Matte* mat_green = new Matte(*mat);
    mat_green->set_cd(0.2, 1, 0.2);
    Plane* east = new Plane(Point3D(6, 0, 0), Normal(-1, 0, 0));
    east->set_material(mat_green);
    add_object(east);

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