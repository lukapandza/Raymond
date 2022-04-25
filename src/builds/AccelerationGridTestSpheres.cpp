void
World::build() {

    int num_samples = 9;

    //int num_spheres = 2;      // 00.407
    //int num_spheres = 4;      // 00.411
    //int num_spheres = 6;      // 00.404
    //int num_spheres = 8;      // 00.403
    //int num_spheres = 10;     // 00.400
    //int num_spheres = 12;     // 00.405
    //int num_spheres = 14;     // 00.400
    //int num_spheres = 16;     // 00.413
    //int num_spheres = 18;     // 00.400
    //int num_spheres = 20;     // 00.405
    //int num_spheres = 30;     // 01.230
    //int num_spheres = 40;     // 02.840
    //int num_spheres = 50;     // 04.470
    int num_spheres = 60;     //
    //int num_spheres = 70;     //
    //int num_spheres = 80;     //
    //int num_spheres = 90;     //
    //int num_spheres = 100;    //

    this->max_samples = num_samples;
    this->variance_tolerance = 0.1;
    this->sample_batch_size = 32;

    double scale_factor = 16;

    vp.set_hres(16 * scale_factor);
    vp.set_vres(16 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(12);

    background_color = black;

    tracer_ptr = new RayCast(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(.2);
    set_ambient_light(ambient_ptr);

    double camera_distance = 3.0;

    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(1.5 * camera_distance, 1.25 * camera_distance, 2 * camera_distance);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_view_distance(4.0);
    pinhole_ptr->set_zoom(8 * scale_factor);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //light:
    Directional* l_d = new Directional();
    l_d->set_color(1);
    l_d->set_intensity(2);
    l_d->set_direction(Vector3D(1, .25, .25));
    l_d->set_shadows(true);
    add_light(l_d);

    /*
    PointLight* p_l = new PointLight();
    p_l->set_location(0, 2, 0);
    p_l->set_intensity(1);
    p_l->set_shadows(true);
    p_l->set_color(1);
    add_light(p_l);
    */
    // Materials:
    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(1);
    mat->set_kd(1);
    mat->set_cd(1); // white

    float volume = 1 / pow(num_spheres, 3);
    float radius = pow(0.75 * volume / 3.14159, 0.333333);

    Sphere* sphere = new Sphere(Point3D(0, 0, 0), radius);

    Grid* grid_ptr = new Grid;
    //set_rand_seed(15);

    double min = -1.0 + radius;
    double max = 1.0 - radius;

    for (int i(0); i < num_spheres; i++)
        for (int ii(0); ii < num_spheres; ii++)
            for (int iii(0); iii < num_spheres; iii++) {

                Matte* mat_r = new Matte(*mat);
                mat_r->set_cd((i + 1) * 1.0 / num_spheres, (ii + 1) * 1.0 / num_spheres, (iii + 1) * 1.0 / num_spheres);

                Sphere* s = new Sphere(Point3D(min + i * (max - min) / num_spheres, min + ii * (max - min) / num_spheres, min + iii * (max - min) / num_spheres), radius);
                s->set_material(mat_r);
                grid_ptr->add_object(s);
            }
    

    grid_ptr->setup_cells();

    add_object(grid_ptr);
}


