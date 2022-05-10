void
World::build() {

    int num_samples = 1024;

    this->max_samples = num_samples;
    this->variance_tolerance = 0.1;
    this->sample_batch_size = 32;

    double scale_factor = 32;


    vp.set_hres(16 * scale_factor);
    vp.set_vres(9 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(24);


    background_color = black;

    //tracer_ptr = new Whitted(this);
    tracer_ptr = new PathTrace(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0);
    set_ambient_light(ambient_ptr);

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
    //vp.set_pixel_size(1.0 / (2.56 * scale_factor));
    vp.set_pixel_size(1.0 / (8 * scale_factor));
    camera_ptr = cmr;
    


    Sampler* sampler_ptr = new MultiJittered(num_samples);

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


    // lights:

    double radius = .2;
    double gap = .04;
    double height = 1.25;
    double dist = 1.5;

    //cylinder lights:
    Cylinder* lc = new Cylinder(0, 4, radius);
    //Cylinder* lc_d = new Cylinder(0, 4, radius - gap);
    Box* lc_d = new Box(-.67 * radius, 0, -.67 * radius, .67 * radius, 4, .67 * radius);

    Instance* lc_1 = new Instance(lc);
    lc_1->set_material(em1);
    lc_1->translate(0, 0, dist);
    lc_1->rotate_y(90);
    add_object(lc_1);

    Instance* lc_1_d = new Instance(lc_d);
    lc_1_d->set_material(mat);
    lc_1_d->translate(0, 0, dist);
    lc_1_d->rotate_y(90);
    add_object(lc_1_d);

    Instance* lc_2 = new Instance(lc);
    lc_2->set_material(em2);
    lc_2->translate(0, 0, dist);
    lc_2->rotate_y(-90);
    add_object(lc_2);

    Instance* lc_2_d = new Instance(lc_d);
    lc_2_d->set_material(mat);
    lc_2_d->translate(0, 0, dist);
    lc_2_d->rotate_y(-90);
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

    // rim cylinders:

    int num_cyls = 6;

    Cylinder* cyl = new Cylinder(0, 4, 1, 0, PI / num_cyls);

    for (int i(0); i < num_cyls; i++) {
        Instance* cyl_ins = new Instance(cyl);
        cyl_ins->rotate_y(3 * 180.0 / (2 * num_cyls) + i * 360.0 / num_cyls);
        cyl_ins->scale(2, 1, 1);
        cyl_ins->set_material(ref);
        add_object(cyl_ins);
    }

    // inner cylinders:
    /*
    double radius_i = 1.0 / 16;
    double size = 1.0;
    int num = 5;

    Cylinder* in_cyl = new Cylinder(0, 4, radius_i);

    for (int i (0); i < num; i++)
        for (int ii(0); ii < num; ii++) {
            
            Instance* in_ins = new Instance(in_cyl);
            in_ins->set_material(ref);
            in_ins->translate(-.5 * size + i * size / (num - 1), 0, -.5 * size + ii * size / (num - 1));
            in_ins->rotate_y(45);
            add_object(in_ins);
        }
    */

    /*
    double side = .25;

    // inner box:
    Box* box = new Box(-.5 * side, 0, -.5 * side, .5 * side, 4, .5 * side);

    Instance* box_ins = new Instance(box);
    box_ins->rotate_y(45);
    box_ins->scale(1, 1, 2);
    box_ins->set_material(ref);
    add_object(box_ins);
    */

    /*
    double radius_i = 1.0 / 16;
    Cylinder* in_cyl = new Cylinder(1.1, 4, radius_i);
    
    Instance* in_ins_1 = new Instance(in_cyl);
    in_ins_1->set_material(ref);
    in_ins_1->scale(1, 1, 4);
    in_ins_1->rotate_y(45);
    add_object(in_ins_1);

    Instance* in_ins_2 = new Instance(in_cyl);
    in_ins_2->set_material(ref);
    in_ins_2->scale(1, 1, 4);
    in_ins_2->rotate_y(-45);
    add_object(in_ins_2);
    */

    /*
    Sphere* s = new Sphere(Point3D(0, .1, 0), .125);
    s->set_material(ref);
    */
    Cylinder* s = new Cylinder(0, 4, .33, 0, PI / 6.0);
    s->set_material(ref);

    for (int i(0); i < 6; i++) {
        Instance* ins = new Instance(s);
        ins->translate(0, 0, -.33);
        ins->rotate_y(90);
        ins->translate(0, 0, .33);
        ins->rotate_y(30 + i * 60);
        add_object(ins);
    }

    
}


