void
World::build() {

    int num_samples = 16384;

    this->max_samples = num_samples;
    this->variance_tolerance = 0.1;
    this->sample_batch_size = 32;

    double scale_factor = 32;

    
    vp.set_hres(16 * scale_factor);
    vp.set_vres(16 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(12);
    

    background_color = black;

    //tracer_ptr = new Whitted(this);
    tracer_ptr = new PathTrace(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0);
    set_ambient_light(ambient_ptr);

    double camera_distance = 400.0;

    //camera:
    
    /*
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(0, camera_distance, -0.001);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_view_distance(4.0);
    pinhole_ptr->set_zoom(512 * scale_factor);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;
    */
    
    
    Orthographic* cmr = new Orthographic;
    cmr->set_eye(0, 1, 0.00001);
    cmr->set_lookat(0, 0, 0);
    cmr->set_up_vector(0, 0, 1);
    cmr->compute_uvw();
    vp.set_pixel_size(1.0 / (5.12 * scale_factor));
    camera_ptr = cmr;
    

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //light:
    /*
    Directional* l_d = new Directional();
    l_d->set_color(1);
    l_d->set_intensity(2);
    l_d->set_direction(Vector3D(1, .25, .25));
    l_d->set_shadows(true);
    add_light(l_d);
    */

    /*
    PointLight* l1 = new PointLight();
    l1->set_shadows(true);
    l1->set_location(Point3D(0, .25, .75));
    l1->set_intensity(2);
    l1->set_color(.66, 0.17, 0.14);
    add_light(l1);

    PointLight* l2 = new PointLight();
    l2->set_shadows(true);
    l2->set_location(Point3D(.5, .25, 0));
    l2->set_intensity(2);
    l2->set_color(0.18, .58, 0.43);
    add_light(l2);
    */

    // Materials:
    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(1);
    mat->set_kd(1);
    mat->set_cd(1); // white

    Reflective* ref = new Reflective();
    ref->set_c(1, 1, 1);
    ref->set_samples(num_samples);
    ref->set_kr(1);
    ref->set_kd(0);
    ref->set_ks(0);
    ref->set_exp(16);

    double intensity = 4.0;

    Emissive* em1 = new Emissive;
    em1->set_ce(.66, 0.17, 0.14);
    //em1->set_ce(1, 0, 0);
    em1->set_ls(intensity);

    Emissive* em2 = new Emissive;
    em2->set_ce(0.18, .58, 0.43);
    //em2->set_ce(0, 1, 0);
    em2->set_ls(intensity);

    Emissive* em3 = new Emissive;
    em3->set_ce(0, 0, 1);
    em3->set_ls(intensity);

    
    // lights:

    double radius = .1;
    double gap = .02;
    double height = 1.25;
    double dist = .66;

    // sphere lights:
    /*
    Sphere* s = new Sphere(Point3D(0, height, dist), radius);

    Instance* s_r = new Instance(s);
    s_r->set_material(em1);
    s_r->rotate_y(60);
    add_object(s_r);

    Instance* s_g = new Instance(s);
    s_g->set_material(em2);
    s_g->rotate_y(-60);
    add_object(s_g);
    */

    //cylinder lights:
    Cylinder* lc = new Cylinder(0, 4, radius);
    Cylinder* lc_d = new Cylinder(0, 4, radius - gap);

    Instance* lc_1 = new Instance(lc);
    lc_1->set_material(em1);
    lc_1->translate(0, 0, dist);
    lc_1->rotate_y(60);
    add_object(lc_1);

    Instance* lc_1_d = new Instance(lc_d);
    lc_1_d->set_material(mat);
    lc_1_d->translate(0, 0, dist);
    lc_1_d->rotate_y(60);
    add_object(lc_1_d);

    Instance* lc_2 = new Instance(lc);
    lc_2->set_material(em2);
    lc_2->translate(0, 0, dist);
    lc_2->rotate_y(-60);
    add_object(lc_2);

    Instance* lc_2_d = new Instance(lc_d);
    lc_2_d->set_material(mat);
    lc_2_d->translate(0, 0, dist);
    lc_2_d->rotate_y(-60);
    add_object(lc_2_d);

    /*
    Instance* s_b = new Instance(s);
    s_b->set_material(em3);
    s_b->rotate_y(240);
    add_object(s_b);
    */

    /*
    Sphere* s1 = new Sphere(Point3D(0, height, .75), radius);
    s1->set_material(em1);
    add_object(s1);

    Sphere* s2 = new Sphere(Point3D(.5, height, 0), radius);
    s2->set_material(em2);
    add_object(s2);
    */

    // floor

    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    // cylinders:

    int num_cyls = 6;

    for (int i(0); i < num_cyls; i++) {
        Cylinder* cyl = new Cylinder(0, 4, 1, PI / 2 / num_cyls + i * TWO_PI / num_cyls, PI / 2 / num_cyls + i * TWO_PI / num_cyls + PI / num_cyls);
        cyl->set_material(ref);
        add_object(cyl);
    }
}


