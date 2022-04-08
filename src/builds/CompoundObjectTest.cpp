void
World::build() {

    int num_samples = 1024;

    this->max_samples = num_samples;
    this->variance_tolerance = 0.1;
    this->sample_batch_size = 32;

    double scale_factor = 16;

    vp.set_hres(16 * scale_factor);
    vp.set_vres(16 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(12);

    background_color = black;

    tracer_ptr = new PathTrace(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.0);
    set_ambient_light(ambient_ptr);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(5, 5, 0);
    //pinhole_ptr->set_lookat(4.05, 1.5, 0);
    pinhole_ptr->set_lookat(1, 1, 0);
    pinhole_ptr->set_view_distance(10.0);
    pinhole_ptr->set_zoom(2 * scale_factor);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //light: 
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(1);
    //emissive_ptr1->set_ce(.77, 0.73, 0.94);
    emissive_ptr1->set_ce(.85, .85, .95);

    ConcaveSphere* sphere_ptr = new ConcaveSphere;
    sphere_ptr->set_radius(1000000.0);
    sphere_ptr->set_material(emissive_ptr1);
    add_object(sphere_ptr);


    // Materials:
    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(0.25);
    mat->set_kd(1);
    mat->set_cd(1); // white

    GlossyReflector* copper = new GlossyReflector;
    copper->set_cd(.72, .45, .2);
    copper->set_cs(.72, .45, .2);
    copper->set_cr(.72, .45, .2);
    copper->set_kd(.3);
    copper->set_ks(.1);
    copper->set_kr(.6);
    copper->set_samples(num_samples);
    copper->set_exp_s(64);
    copper->set_exp_r(4096);

    GlossyReflector* iron = new GlossyReflector(*copper);
    iron->set_cd(.34, .34, .32);
    iron->set_cs(.34, .34, .32);
    iron->set_cr(.34, .34, .32);

    GlossyReflector* silver = new GlossyReflector(*copper);
    silver->set_cd(.75, .75, .75);
    silver->set_cs(.75, .75, .75);
    silver->set_cr(.75, .75, .75);

    GlossyReflector* gold = new GlossyReflector(*copper);
    gold->set_cd(1, .84, 0);
    gold->set_cs(1, .84, 0);
    gold->set_cr(1, .84, 0);


    // floor:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    Compound* rod = new Compound;

    Cylinder* cyl = new Cylinder(-.5, .5, .25);
    rod->add_object(cyl);
    /*
    Disk* top_cap = new Disk(0, .5, 0, 0, 1, 0, .25);
    rod->add_object(top_cap);

    Disk* bot_cap = new Disk(0, -.5, 0, 0, -1, 0, .25);
    rod->add_object(bot_cap);
    */
    Sphere* top = new Sphere(Point3D(0, .5, 0), .25);
    rod->add_object(top);

    Sphere* bot = new Sphere(Point3D(0, -.5, 0), .25);
    rod->add_object(bot);

    Instance* cyl_ins = new Instance(rod->clone());
    cyl_ins->set_material(iron);
    cyl_ins->scale(1, 4, 1);
    cyl_ins->translate(0, 2, 0);
    add_object(cyl_ins);

    Instance* cyl_ins_2 = new Instance(rod->clone());
    cyl_ins_2->set_material(copper);
    cyl_ins_2->scale(1, 3, 1);
    cyl_ins_2->translate(0, 1.5, 1);
    add_object(cyl_ins_2);

    Instance* cyl_ins_3 = new Instance(rod->clone());
    cyl_ins_3->set_material(silver);
    cyl_ins_3->scale(1, 2, 1);
    cyl_ins_3->translate(1, 1, 1);
    add_object(cyl_ins_3);

    Instance* cyl_ins_4 = new Instance(rod->clone());
    cyl_ins_4->set_material(gold);
    cyl_ins_4->translate(1, .5, 0);
    add_object(cyl_ins_4);

    /*
    Instance* floor_disk = new Instance(rod->clone());
    floor_disk->set_material(silver);
    floor_disk->scale(6, .05, 6);
    floor_disk->translate(.5, 0, .5);
    add_object(floor_disk);
    */
}


