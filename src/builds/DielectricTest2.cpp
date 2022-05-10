void
World::build() {

    int num_samples = 16;

    this->max_samples = num_samples;
    this->variance_tolerance = 0.1;
    this->sample_batch_size = 32;

    double scale_factor = 240;

    vp.set_hres(16 * scale_factor);
    vp.set_vres(9 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(1);

    background_color = black;

    tracer_ptr = new Whitted(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.4);
    set_ambient_light(ambient_ptr);


    //camera:
    /*
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(5, 5, 5);
    //pinhole_ptr->set_lookat(4.05, 1.5, 0);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_view_distance(1);
    pinhole_ptr->set_zoom(8 * scale_factor);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;
    */

    
    Orthographic* cmr = new Orthographic;
    cmr->set_eye(5, 5, 5);
    cmr->set_lookat(0, 0, 0);
    vp.s = 1.0 / (1 * scale_factor);
    cmr->compute_uvw();
    camera_ptr = cmr;
    

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //light:

    /*
    Directional* l_r = new Directional;
    l_r->set_color(1, 0, 0);
    l_r->set_intensity(1.0);
    l_r->set_shadows(true);
    l_r->set_direction(Vector3D(1, 0, 0));
    add_light(l_r);

    Directional* l_g = new Directional;
    l_g->set_color(0, 1, 0);
    l_g->set_intensity(1.0);
    l_g->set_shadows(true);
    l_g->set_direction(Vector3D(0, 0, 1));
    add_light(l_g);

    Directional* l_b = new Directional;
    l_b->set_color(0, 0, 1);
    l_b->set_intensity(1.0);
    l_b->set_shadows(true);
    l_b->set_direction(Vector3D(0, 1, 0));
    add_light(l_b);
    */

    PointLight* l_r = new PointLight;
    l_r->set_location(5, 1, 1);
    l_r->set_color(1, 0, 0);
    l_r->set_intensity(1.0);
    l_r->set_shadows(false);
    add_light(l_r);

    PointLight* l_g = new PointLight;
    l_g->set_location(1, 1, 5);
    l_g->set_color(0, 1, 0);
    l_g->set_intensity(1.0);
    l_g->set_shadows(false);
    add_light(l_g);

    PointLight* l_b = new PointLight;
    l_b->set_location(1, 5, 1);
    l_b->set_color(0, 0, 1);
    l_b->set_intensity(1.0);
    l_b->set_shadows(false);
    add_light(l_b);


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
    dielectric_ptr->set_cf_in(RGBColor(1, 1, 1));
    dielectric_ptr->set_cf_out(RGBColor(1, 1, 1));

    Reflective* r_mat = new Reflective;
    r_mat->set_c(1, 1, 1);
    r_mat->set_cr(1, 1, 1);
    r_mat->set_ka(0);
    r_mat->set_kd(.2);
    r_mat->set_ks(.1);
    r_mat->set_kr(.7);
    r_mat->set_samples(num_samples);
    r_mat->set_exp(64);


    // floor:
    /*
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);
    */

    /*
    double thickness = .2;
    //glass boxes:
    Box* box = new Box(-2, 0, -.5 * thickness, 2, 2, .5 * thickness);
    box->set_material(dielectric_ptr);

    for (int i = 0; i < 4; i++) {
        Instance* ins = new Instance(box);
        ins->translate(0, 0, -1.5 + i);
        add_object(ins);
    }
    */

    // walls:
    double thickness = .5;

    Box* bot = new Box(0, -thickness, 0, 4, 0, 4);
    bot->set_material(mat);
    add_object(bot);

    Box* nor = new Box(-thickness, -thickness, -thickness, 4, 4, 0);
    nor->set_material(mat);
    add_object(nor);

    Box* eas = new Box(-thickness, -thickness, 0, 0, 4, 4);
    eas->set_material(mat);
    add_object(eas);

    /*
    //boxes:
    Box* b1 = new Box(.2, 0, .2, .8, 3, .8);
    b1->set_material(dielectric_ptr);
    add_object(b1);

    Box* b2_1 = new Box(1.2, 0, .2, 1.8, 2, .8);
    b2_1->set_material(dielectric_ptr);
    add_object(b2_1);

    Box* b2_2 = new Box(.2, 0, 1.2, .8, 2, 1.8);
    b2_2->set_material(dielectric_ptr);
    add_object(b2_2);

    Box* b3_1 = new Box(2.2, 0, .2, 2.8, 1, .8);
    b3_1->set_material(dielectric_ptr);
    add_object(b3_1);

    Box* b3_2 = new Box(1.2, 0, 1.2, 1.8, 1, 1.8);
    b3_2->set_material(dielectric_ptr);
    add_object(b3_2);

    Box* b3_3 = new Box(.2, 0, 2.2, .8, 1, 2.8);
    b3_3->set_material(dielectric_ptr);
    add_object(b3_3);
    */
    
    Box* obj = new Box(-.5, -.5, -.5, .5, .5, .5);
    
    
    Sphere* obj_2 = new Sphere(Point3D(0, 0, 0), .5);

    std::vector<Point3D> p;

    p.push_back(Point3D(.5, .5, .5));
    p.push_back(Point3D(1.5, .5, .5));
    p.push_back(Point3D(2.5, .5, .5));
    p.push_back(Point3D(.5, .5, 1.5));
    p.push_back(Point3D(1.5, .5, 1.5));
    p.push_back(Point3D(.5, .5, 2.5));

    p.push_back(Point3D(.5, 1.5, .5));
    p.push_back(Point3D(1.5, 1.5, .5));
    p.push_back(Point3D(.5, 1.5, 1.5));

    p.push_back(Point3D(.5, 2.5, .5));

    double scale = .8;
    double scale_2 = .6;

    for (int i = 0; i < p.size(); i++) {
    
        Instance* ins = new Instance(obj);
        ins->set_material(dielectric_ptr);
        ins->scale(scale, scale, scale);
        ins->translate(p[i].x, p[i].y, p[i].z);
        add_object(ins);

        Instance* ins_2 = new Instance(obj_2);
        ins_2->set_material(r_mat);
        ins_2->scale(scale_2, scale_2, scale_2);
        ins_2->translate(p[i].x, p[i].y, p[i].z);
        add_object(ins_2);
    }
    

}
