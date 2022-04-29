void
World::build() {

    int num_samples = 256;

    this->max_samples = num_samples;
    this->variance_tolerance = 0.1;
    this->sample_batch_size = 32;

    double scale_factor = 32;

    // 1440 x 2560
    vp.set_hres(9 * scale_factor);
    vp.set_vres(16 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(24);


    background_color = black;

    //tracer_ptr = new Whitted(this);
    tracer_ptr = new PathTrace(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0);
    set_ambient_light(ambient_ptr);

    //camera:

    Orthographic* cmr = new Orthographic;
    cmr->set_eye(0, 1, 0.00001);
    cmr->set_lookat(0, 0, 0);
    cmr->set_up_vector(0, 0, 1);
    cmr->compute_uvw();
    vp.set_pixel_size(1.0 / (1.5 * scale_factor));
    camera_ptr = cmr;

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

    double y_0;


    // lights:

    double radius = .2;
    double gap = .04;
    double height = 1.25;
    double dist = 1.5;

    //cylinder lights:
    Cylinder* lc = new Cylinder(y_0, 4, radius);
    //Cylinder* lc_d = new Cylinder(0, 4, radius - gap);
    Box* lc_d = new Box(-.67 * radius, y_0, -.67 * radius, .67 * radius, 4, .67 * radius);

    Instance* lc_1 = new Instance(lc);
    lc_1->set_material(em1);
    lc_1->translate(0, 0, dist);
    add_object(lc_1);

    Instance* lc_1_d = new Instance(lc_d);
    lc_1_d->set_material(mat);
    lc_1_d->translate(0, 0, dist);
    add_object(lc_1_d);

    Instance* lc_2 = new Instance(lc);
    lc_2->set_material(em2);
    lc_2->translate(0, 0, dist);
    lc_2->rotate_y(180);
    add_object(lc_2);

    Instance* lc_2_d = new Instance(lc_d);
    lc_2_d->set_material(mat);
    lc_2_d->translate(0, 0, dist);
    lc_2_d->rotate_y(180);
    add_object(lc_2_d);

    // floor

    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    // rim cylinders:

    int num_cyls = 6;

    Cylinder* cyl = new Cylinder(y_0, 4, 1, 0, PI / num_cyls);

    for (int i(0); i < num_cyls; i++) {
        Instance* cyl_ins = new Instance(cyl);
        cyl_ins->rotate_y(180.0 / (2 * num_cyls) + i * 360.0 / num_cyls);
        cyl_ins->set_material(ref);
        add_object(cyl_ins);
    }

    for (int i(0); i < num_cyls; i++) {
        Instance* cyl_ins = new Instance(cyl);
        cyl_ins->rotate_y(3 * 180.0 / (2 * num_cyls) + i * 360.0 / num_cyls);
        cyl_ins->scale(1.5, 1, 3);
        cyl_ins->set_material(ref);
        add_object(cyl_ins);
    }



}


