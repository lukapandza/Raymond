void
World::build() {

    int num_samples = 4096;

    this->max_samples = num_samples;
    this->variance_tolerance = 0.1;
    this->sample_batch_size = 32;

    double scale_factor = 60;


    vp.set_hres(32 * scale_factor);
    vp.set_vres(9 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(24);


    background_color = black;

    //tracer_ptr = new Whitted(this);
    tracer_ptr = new PathTrace(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0);
    set_ambient_light(ambient_ptr);

    int num = 8;

    //camera:
    Orthographic* cmr = new Orthographic;
    cmr->set_eye(num, 1, 0.00001);
    cmr->set_lookat(num, 0, 0);
    cmr->compute_dir();
    cmr->set_up_vector(0, 0, 1);
    cmr->compute_uvw();
    vp.set_pixel_size(1.0 / (1.8 * scale_factor));
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


    // floor

    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);
    
    Cylinder* s = new Cylinder(0, 4, .33, 0, PI / 4.0);
    s->set_material(ref);

    double sweep = 1.0 / 6.0;
    Cylinder* c_l = new Cylinder(0, 4, 1, PI - PI * sweep, PI + PI * sweep);

    
    double r = .4;

    for (int i(0); i < num; i++) {
    
        double x = 1 + 2 * i;

        for (int i(0); i < 6; i++) {
            Instance* ins = new Instance(s);
            ins->translate(0, 0, -r);
            ins->rotate_y(-90);
            ins->translate(0, 0, r);
            ins->rotate_y(30 + i * 60);
            ins->translate(x, 0, 0);
            add_object(ins);
        }

        Emissive* em_1 = new Emissive;
        em_1->set_ls(1.0);
        em_1->set_ce(RGBColor::convert_wave_length_nm_to_rgb(420 + i * (240 / (num - 1))));

        Instance* light_1 = new Instance(c_l);
        light_1->set_material(em_1);
        light_1->translate(x, 0, 0);
        add_object(light_1);

        Emissive* em_2 = new Emissive;
        em_2->set_ls(1.0);
        em_2->set_ce(RGBColor::convert_wave_length_nm_to_rgb(660 - i * (240 / (num - 1))));

        Instance* light_2 = new Instance(c_l);
        light_2->set_material(em_2);
        light_2->rotate_y(180);
        light_2->translate(x, 0, 0);
        add_object(light_2);
    }



}


