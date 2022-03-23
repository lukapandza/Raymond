void
World::build() {

    int num_samples = 4000;

    double scale_factor = 32;

    vp.set_hres(16 * scale_factor);
    vp.set_vres(9 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(16);

    background_color = black;

    tracer_ptr = new PathTrace(this);
    //tracer_ptr = new AreaLighting(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.0);
    set_ambient_light(ambient_ptr);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(0, 8, 5.9);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_view_distance(3.0);
    pinhole_ptr->set_zoom(2 * scale_factor);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //light: 
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(4);
    //emissive_ptr1->set_ce(.77, 0.73, 0.94);
    emissive_ptr1->set_ce(1, 1, 1);

    Sphere* sphere = new Sphere(Point3D(0, 8, 0), 2);
    sphere->set_material(emissive_ptr1);
    add_object(sphere);

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

    Phong* p_white = new Phong;
    p_white->set_samples(num_samples);
    p_white->set_exp(10000);
    p_white->set_kd(1);
    p_white->set_ks(1);
    p_white->set_c(1, 1, 1);



    //walls:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    Plane* ceiling = new Plane(Point3D(0, 10, 0), Normal(.00047, -1, .000012));
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
    double box_height = .2;

    Box* box = new Box(-radius, 0, -radius, radius, box_height, radius);
    box->set_material(mat_blue);

    for (int i = 0; i < 5; i++) {
        for (int ii = 0; ii < 5; ii++) {
        
            Phong* material = new Phong(*p_white);
            material->set_kd(1 - ii / 4.0);
            material->set_ks(0.0 + ii / 4.0);
            material->set_exp(pow(10, i));

            Point3D center(-4 + 2*i, box_height + radius, 4 - 2*ii);

            Sphere* ball = new Sphere(center, radius);
            ball->set_material(material);
            add_object(ball);

            Instance* tile = new Instance(box);
            tile->translate(-4 + 2 * i, 0, 4 - 2 * ii);
            add_object(tile);
        }
    }
    


}

