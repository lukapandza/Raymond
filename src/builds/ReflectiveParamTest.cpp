void
World::build() {

    int num_samples = 256;

    this->max_samples = num_samples;
    this->variance_tolerance = 0.05;
    //this->variance_tolerance = 0.1;
    //this->variance_tolerance = 1;
    //this->variance_tolerance = 10;
    //this->variance_tolerance = 100;
    this->sample_batch_size = 16;

    double scale_factor = 16;

    vp.set_hres(16 * scale_factor);
    vp.set_vres(9 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(12);

    background_color = black;

    tracer_ptr = new PathTrace(this);
    //tracer_ptr = new AreaLighting(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.0);
    set_ambient_light(ambient_ptr);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(0, 2, 5.5);
    pinhole_ptr->set_lookat(0, 1.5, 0);
    //pinhole_ptr->set_lookat(0, 12, 0);
    pinhole_ptr->set_view_distance(3.0);
    pinhole_ptr->set_zoom(2 * scale_factor);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //light: 
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(12);
    //emissive_ptr1->set_ce(.77, 0.73, 0.94);
    emissive_ptr1->set_ce(1, 1, 1);

    Sphere* sphere = new Sphere;
    sphere->set_material(emissive_ptr1);

    Instance* light_sphere1 = new Instance(sphere);
    light_sphere1->scale(2, .25, 2);
    light_sphere1->translate(0, 12, 0);
    add_object(light_sphere1);

    /*
    Instance* light_sphere2 = new Instance(sphere);
    light_sphere2->scale(2, .25, 2);
    light_sphere2->translate(0, 12, 12);
    add_object(light_sphere2);

    Instance* light_sphere3 = new Instance(sphere);
    light_sphere3->scale(2, .25, 2);
    light_sphere3->translate(0, 12, 24);
    add_object(light_sphere3);
    */

    /*
    ConcaveSphere* sphere_ptr = new ConcaveSphere;
    sphere_ptr->set_radius(1000000.0);
    sphere_ptr->set_material(emissive_ptr1);
    add_object(sphere_ptr);
    */

    /*
    EnvironmentLight* light_ptr = new EnvironmentLight;
    light_ptr->set_material(emissive_ptr1);
    light_ptr->set_sampler(new MultiJittered(num_samples));
    light_ptr->set_shadows(true);
    add_light(light_ptr);
    */


    // Materials:
    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(0.25);
    mat->set_kd(.95);
    mat->set_cd(1); // white

    Matte* mat_red = new Matte(*mat);
    mat_red->set_cd(.66, 0.17, 0.14);

    Matte* mat_green = new Matte(*mat);
    mat_green->set_cd(0.18, .58, 0.43);

    Matte* mat_blue = new Matte(*mat);
    mat_blue->set_cd(.21, .12, .6);

    Reflective* r_mat = new Reflective;
    r_mat->set_samples(num_samples);
    r_mat->set_c(1, 1, 1);
    r_mat->set_exp(100);
    r_mat->set_kd(1.0);
    r_mat->set_ks(0.0);
    r_mat->set_cr(1, 1, 1);

    Phong* p_blue = new Phong;
    p_blue->set_samples(num_samples);
    p_blue->set_c(.22, .34, .8);
    p_blue->set_kd(.8);
    p_blue->set_ks(.2);
    p_blue->set_exp(256);

    Dielectric* dielectric_ptr = new Dielectric;
    dielectric_ptr->set_ka(0);
    dielectric_ptr->set_kd(0);
    dielectric_ptr->set_cd(1, 1, 1);
    dielectric_ptr->set_ks(0);
    dielectric_ptr->set_cs(1, 1, 1);
    dielectric_ptr->set_samples(num_samples);
    dielectric_ptr->set_exp(64);
    dielectric_ptr->set_ior_in(1.5);
    dielectric_ptr->set_ior_out(1.0);
    dielectric_ptr->set_cf_in(RGBColor(.8, .8, 1));
    dielectric_ptr->set_cf_out(RGBColor(1, 1, 1));
    



    //walls:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    Plane* ceiling = new Plane(Point3D(0, 12, 0), Normal(.00047, -1, .000012));
    ceiling->set_material(mat);
    add_object(ceiling);

    Plane* west = new Plane(Point3D(-6, 0, 0), Normal(1, 0, 0));
    west->set_material(mat_red);
    add_object(west);

    Plane* east = new Plane(Point3D(6, 0, 0), Normal(-1, 0, 0));
    east->set_material(mat_green);
    add_object(east);

    Plane* north = new Plane(Point3D(0, 0, -6), Normal(0, 0, 1));
    north->set_material(mat);
    add_object(north);

    Plane* south = new Plane(Point3D(0, 0, 6), Normal(0, 0, -1));
    south->set_material(mat);
    add_object(south);


    double radius = .8;
    double gap = .1;
    double box_height = .2;

    for (int i = 0; i < 5; i++) {

        Matte* box_mat = new Matte(*mat);
        box_mat->set_cd((1.0 - (i + 1) / 6.0) * RGBColor(.66, .17, .14) + (i + 1) / 6.0 * RGBColor(.18, .58, .43));

        Box* box = new Box(-4 + 2 * i - radius, gap, -radius, -4 + 2 * i + radius, gap + box_height, radius);
        box->set_material(dielectric_ptr);
        add_object(box);

        Reflective* sphere_mat = new Reflective(*r_mat);
        sphere_mat->set_kd(1.0 - i / 4.0);
        sphere_mat->set_kr(i / 4.0);

        Sphere* sphere = new Sphere(Point3D(-4 + 2 * i, gap + box_height + radius, 0), radius);
        sphere->set_material(sphere_mat);
        add_object(sphere);
    }

    double tile_gap = .2;
    double z = 6 -gap - box_height;

    std::vector<Point3D> points = {
        Point3D(0, 4, z), 
        Point3D(-1, 5, z), Point3D(1, 5, z),
        Point3D(-2, 6, z), Point3D(0, 6, z), Point3D(2, 6, z),
        Point3D(-3, 7, z), Point3D(-1, 7, z), Point3D(1, 7, z), Point3D(3, 7, z), 
        Point3D(-2, 8, z), Point3D(0, 8, z), Point3D(2, 8, z),
        Point3D(-1, 9, z), Point3D(1, 9, z),
        Point3D(0, 10, z)
    };

    Box* tile = new Box(-sqrt(2) * .5 + tile_gap * .5, -sqrt(2) * .5 + tile_gap * .5, -box_height, sqrt(2) * .5 - tile_gap * .5, sqrt(2) * .5 - tile_gap * .5, box_height);
    tile->set_material(p_blue);

    for (int i = 0; i < points.size(); i++) {
        
        Instance* tile_instance = new Instance(tile);
        tile_instance->rotate_z(45);
        tile_instance->translate(points[i].x, points[i].y, points[i].z);
        add_object(tile_instance);
    }



}

