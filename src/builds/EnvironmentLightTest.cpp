void
World::build() {

    int num_samples = 256;

    double scale_factor = 16;

    vp.set_hres(16 * scale_factor);
    vp.set_vres(9 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(8);

    background_color = black;

    tracer_ptr = new PathTrace(this);
    //tracer_ptr = new AreaLighting(this);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.0);
    set_ambient_light(ambient_ptr);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(5.5, 1, 9);
    pinhole_ptr->set_lookat(5.5, 2, 1);
    pinhole_ptr->set_view_distance(3.0);
    pinhole_ptr->set_zoom(4 * scale_factor);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //light: 
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(1.6);
    emissive_ptr1->set_ce(.77, 0.73, 0.94);

    Emissive* emissive_ptr2 = new Emissive;
    emissive_ptr2->set_ls(16);
    emissive_ptr2->set_ce(.98, 0.83, 0.6);
    
    ConcaveSphere* sphere_ptr = new ConcaveSphere;
    sphere_ptr->set_radius(1000000.0);
    sphere_ptr->set_material(emissive_ptr1);
    add_object(sphere_ptr);
    
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

    Phong* p = new Phong;
    p->set_samples(num_samples);
    p->set_exp(10000);
    p->set_kd(.2);
    p->set_ks(.75);
    p->set_c(1, 1, 1);

    Phong* iron = new Phong(*p);
    iron->set_c(.34, .34, .32);

    Phong* bronze = new Phong(*p);
    bronze->set_c(.69, .55, .34);

    Phong* silver = new Phong(*p);
    silver->set_c(.753, .753, .753);

    Phong* gold = new Phong(*p);
    gold->set_c(.83, .67, .22);

    Phong* blu = new Phong(*p);
    blu->set_c(.22, .67, .82);



    //walls:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    double height = 4.0;
    double thickness = .25;
    double l_e_w = 9.0;
    double l_n_s = 9.0;
    
    Box* north_wall = new Box(1.0 - thickness, 0, 1 - thickness, 1 + l_e_w + thickness, height + thickness, 1);
    north_wall->set_material(mat);
    add_object(north_wall);
    

    Box* south_wall = new Box(1.0 - thickness, 0, 1 + l_n_s, 1 + l_e_w + thickness, height + thickness, 1 + l_n_s + thickness);
    south_wall->set_material(mat);
    add_object(south_wall);

    Box* west_wall = new Box(1.0 - thickness, 0, 1 - thickness, 1, height + thickness, 1 + l_n_s + thickness);
    west_wall->set_material(mat_red);
    add_object(west_wall);

    Box* east_wall = new Box(1 + l_e_w, 0, 1 - thickness, 1 + l_e_w + thickness, height + thickness, 1 + l_n_s + thickness);
    east_wall->set_material(mat_green);
    add_object(east_wall);

    // pillars:
    double width = .5;
    Box* pillar = new Box(-.25, -.25, -.25, .25, .25, .25);

    for (int i(0); i < 6; i++) {
        Instance* beam = new Instance(pillar);
        beam->set_material(i % 2 == 0 ? mat_green : mat_red);
        beam->scale(1, 1, 48);
        beam->translate(1.75 + i * 1.5, height + .75, 5.5);
        add_object(beam);
    }
    
    for (int i(0); i < 6; i++) {
        Instance* beam = new Instance(pillar);
        beam->set_material(mat);
        beam->scale(22, 1, 1);
        beam->translate(5.5, height + .25, 1.75 + i * 1.5);
        add_object(beam);
    }
    
    double leg_thickness = .0625;
    double shelf_thickness = .125;
    // shelves:
    Box* bronze_leg_w = new Box(4 - leg_thickness / 2, 0, 2.5, 4 + leg_thickness / 2, .5 - shelf_thickness, 3);
    bronze_leg_w->set_material(p);
    add_object(bronze_leg_w);

    Box* bronze_leg_e = new Box(7 - leg_thickness / 2, 0, 2.5, 7 + leg_thickness / 2, .5 - shelf_thickness, 3);
    bronze_leg_e->set_material(p);
    add_object(bronze_leg_e);

    Box* bronze_shelf = new Box(3.5, .5 - shelf_thickness, 2.5, 7.5, .5, 3);
    bronze_shelf->set_material(p);
    add_object(bronze_shelf);


    Box* silver_leg_w = new Box(4.5 - leg_thickness / 2, 0, 2, 4.5 + leg_thickness / 2, 1 - shelf_thickness, 2.5);
    silver_leg_w->set_material(p);
    add_object(silver_leg_w);

    Box* silver_leg_e = new Box(6.5 - leg_thickness / 2, 0, 2, 6.5 + leg_thickness / 2, 1 - shelf_thickness, 2.5);
    silver_leg_e->set_material(p);
    add_object(silver_leg_e);

    Box* silver_shelf = new Box(4, 1 - shelf_thickness, 2, 7, 1, 2.5);
    silver_shelf->set_material(p);
    add_object(silver_shelf);


    Box* gold_leg_w = new Box(5 - leg_thickness / 2, 0, 1.5, 5 + leg_thickness / 2, 1.5 - shelf_thickness, 2);
    gold_leg_w->set_material(p);
    add_object(gold_leg_w);

    Box* gold_leg_e = new Box(6 - leg_thickness / 2, 0, 1.5, 6 + leg_thickness / 2, 1.5 - shelf_thickness, 2);
    gold_leg_e->set_material(p);
    add_object(gold_leg_e);

    Box* gold_shelf = new Box(4.5, 1.5 - shelf_thickness, 1.5, 6.5, 1.5, 2);
    gold_shelf->set_material(p);
    add_object(gold_shelf);


    Box* last_shelf = new Box(5, 2 - shelf_thickness, 1, 6, 2, 1.5);
    last_shelf->set_material(p);
    add_object(last_shelf);

    
    // iron balls:
    for (int i(0); i < 5; i++) {
        double x = 3.5 + i;
        Sphere* ball = new Sphere(Point3D(x, .25, 3.25), .25);
        Phong* material = new Phong(*iron);
        ball->set_material(material);
        material->set_exp(pow(x - 2.5, 5));
        add_object(ball);
    }

    // bronze balls:
    for (int i(0); i < 4; i++) {
        double x = 4 + i;
        Sphere* ball = new Sphere(Point3D(x, .75, 2.75), .25);
        Phong* material = new Phong(*bronze);
        ball->set_material(material);
        material->set_exp(pow(x - 2.5, 5));
        add_object(ball);
    }

    // silver balls:
    for (int i(0); i < 3; i++) {
        double x = 4.5 + i;
        Sphere* ball = new Sphere(Point3D(x, 1.25, 2.25), .25);
        Phong* material = new Phong(*silver);
        ball->set_material(material);
        material->set_exp(pow(x - 2.5, 5));
        add_object(ball);
    }

    // gold balls:
    for (int i(0); i < 2; i++) {
        double x = 5 + i;
        Sphere* ball = new Sphere(Point3D(x, 1.75, 1.75), .25);
        Phong* material = new Phong(*gold);
        ball->set_material(material);
        material->set_exp(pow(x - 2.5, 5));
        add_object(ball);
    }

    // blu ball:
    Sphere* ball = new Sphere(Point3D(5.5, 2.255, 1.25), .25);
    ball->set_material(blu);
    blu->set_exp(pow(3, 5));
    add_object(ball);

    /*
    // area lights:
    Box* arm = new Box(-.25, -.0625, -.25, .25, .0625, 2);
    arm->set_material(iron);

    Disk* light1 = new Disk(0, .0725, 1.75, .225, 0, 1, 0);
    light1->set_material(emissive_ptr2);

    Disk* light2 = new Disk(0, .0725, 1.25, .225, 0, 1, 0);
    light2->set_material(emissive_ptr2);

    Disk* light3 = new Disk(0, .0725, .75, .225, 0, 1, 0);
    light3->set_material(emissive_ptr2);

    // west light:
    Instance* arm_w = new Instance(arm);
    add_object(arm_w);
    Instance* light1_w = new Instance(light1);
    add_object(light1_w);
    Instance* light2_w = new Instance(light2);
    add_object(light2_w);
    Instance* light3_w = new Instance(light3);
    add_object(light3_w);

    // east light:
    Instance* arm_e = new Instance(arm);
    add_object(arm_e);
    Instance* light1_e = new Instance(light1);
    add_object(light1_e);
    Instance* light2_e = new Instance(light2);
    add_object(light2_e);
    Instance* light3_e = new Instance(light3);
    add_object(light3_e);

    double w_z = -150;
    double w_y = -30;
    double w_x = -10;
    double w_t_x = 3;
    double w_t_y = 2.5;
    double w_t_z = 1;

    arm_w->rotate_z(w_z);
    //arm_w->rotate_y(w_y);
    arm_w->rotate_x(w_x);
    arm_w->translate(w_t_x, w_t_y, w_t_z);

    light1_w->rotate_z(w_z);
    //light1_w->rotate_y(w_y);
    light1_w->rotate_x(w_x);
    light1_w->translate(w_t_x, w_t_y, w_t_z);

    light2_w->rotate_z(w_z);
    //light2_w->rotate_y(w_y);
    light2_w->rotate_x(w_x);
    light2_w->translate(w_t_x, w_t_y, w_t_z);

    light3_w->rotate_z(w_z);
    //light3_w->rotate_y(w_y);
    light3_w->rotate_x(w_x);
    light3_w->translate(w_t_x, w_t_y, w_t_z);


    double e_z = 150;
    double e_y = 30;
    double e_x = -10;
    double e_t_x = 8;
    double e_t_y = 2.5;
    double e_t_z = 1;

    arm_e->rotate_z(e_z);
    //arm_e->rotate_y(e_y);
    arm_e->rotate_x(e_x);
    arm_e->translate(e_t_x, e_t_y, e_t_z);

    light1_e->rotate_z(e_z);
    //light1_e->rotate_y(e_y);
    light1_e->rotate_x(e_x);
    light1_e->translate(e_t_x, e_t_y, e_t_z);

    light2_e->rotate_z(e_z);
    //light2_e->rotate_y(e_y);
    light2_e->rotate_x(e_x);
    light2_e->translate(e_t_x, e_t_y, e_t_z);

    light3_e->rotate_z(e_z);
    //light3_e->rotate_y(e_y);
    light3_e->rotate_x(e_x);
    light3_e->translate(e_t_x, e_t_y, e_t_z);
    */

}

