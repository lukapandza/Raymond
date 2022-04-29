void
World::build() {

    int num_samples = 25;

    this->max_samples = num_samples;
    this->variance_tolerance = 0.1;
    this->sample_batch_size = 32;

    double scale_factor = 32;

    vp.set_hres(16 * scale_factor);
    vp.set_vres(16 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(12);

    background_color = black;

    tracer_ptr = new Whitted(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.4);
    set_ambient_light(ambient_ptr);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(5, 3, 5);
    //pinhole_ptr->set_lookat(4.05, 1.5, 0);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_view_distance(1);
    pinhole_ptr->set_zoom(16 * scale_factor);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //light:

    PointLight* l2 = new PointLight;
    l2->set_location(0, 4, 0);
    l2->set_color(1);
    l2->set_intensity(4);
    l2->set_shadows(true);
    add_light(l2);


    // Materials:
    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(0.25);
    mat->set_kd(1);
    mat->set_cd(1); // white

    Matte* mat_r = new Matte(*mat);
    mat_r->set_cd(.66, 0.17, 0.14);

    Matte* mat_g = new Matte(*mat);
    mat_g->set_cd(0.18, .58, 0.43);

    Dielectric* dielectric_ptr = new Dielectric;
    dielectric_ptr->set_ka(0);
    dielectric_ptr->set_kd(0);
    dielectric_ptr->set_cd(1, 1, 1);
    dielectric_ptr->set_ks(0.2);
    dielectric_ptr->set_cs(1, 1, 1);
    dielectric_ptr->set_samples(num_samples);
    dielectric_ptr->set_exp(64);
    dielectric_ptr->set_ior_in(1.5);
    dielectric_ptr->set_ior_out(1.0);
    dielectric_ptr->set_cf_in(RGBColor(.8, .8, 1));
    dielectric_ptr->set_cf_out(RGBColor(1, 1, 1));


    // floor:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    
    double thickness = .2;
    //glass boxes:
    Box* box = new Box(-2, 0, -.5 * thickness, 2, 2, .5 * thickness);
    box->set_material(dielectric_ptr);

    for (int i = 0; i < 4; i++) {
        Instance* ins = new Instance(box);
        ins->translate(0, 0, -1.5 + i);
        add_object(ins);
    }

    Sphere* s_g = new Sphere(Point3D(0, .75, -3), .75);
    s_g->set_material(mat_g);
    add_object(s_g);

    Sphere* s_r = new Sphere(Point3D(-3, .75, 0), .75);
    s_r->set_material(mat_r);
    add_object(s_r);
    
    
    
}


