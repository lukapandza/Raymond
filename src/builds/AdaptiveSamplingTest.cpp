void
World::build() {

    int num_samples = 1024;

    this->max_samples = num_samples;
    //this->variance_tolerance = 0;
    //this->variance_tolerance = 0.00001;   // 28%
    //this->variance_tolerance = 0.05;      // 29%
    this->variance_tolerance = 0.1;       // 29%
    //this->variance_tolerance = 0.25;      // 35%
    //this->variance_tolerance = 0.5;       // 53%
    //this->variance_tolerance = 1;         // 68%
    //this->variance_tolerance = 2;         // 89%
    //this->variance_tolerance = 10;
    //this->variance_tolerance = 100;
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
    pinhole_ptr->set_eye(4.99, 1, 4.99);
    //pinhole_ptr->set_lookat(4.05, 1.5, 0);
    pinhole_ptr->set_lookat(0, .8, 0);
    pinhole_ptr->set_view_distance(10.0);
    pinhole_ptr->set_zoom(8 * scale_factor);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //light: 
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(2.4);
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

    Matte* mat_red = new Matte(*mat);
    mat_red->set_cd(.66, 0.17, 0.14);

    Matte* mat_green = new Matte(*mat);
    mat_green->set_cd(0.18, .58, 0.43);

    Matte* mat_blue = new Matte(*mat);
    mat_blue->set_cd(.21, .12, .6);

    Reflective* r_mat = new Reflective;
    r_mat->set_samples(num_samples);
    r_mat->set_c(0, 0, 0);
    r_mat->set_exp(100);
    r_mat->set_kd(0);
    r_mat->set_ks(0);
    r_mat->set_kr(.4);
    //r_mat->set_cr(.21, .12, .6);
    r_mat->set_cr(.95, .95, .95);

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
    


    Phong* p_white = new Phong;
    p_white->set_samples(num_samples);
    p_white->set_c(.95, .85, .75);
    p_white->set_kd(.7);
    p_white->set_ks(.3);
    p_white->set_exp(256);


    // floor:

    double tile_size = .6;
    double tile_height = .0001;
    double gap = .05;

    Box* tile = new Box(-tile_size * .5 + gap * .5, -tile_height, -tile_size * .5 + gap * .5, tile_size * .5 - gap * .5, 0, tile_size * .5 - gap * .5);
    tile->set_material(p_white);

    for (int i(0); i < 10 / tile_size; i++) {
        for (int ii(0); ii < 10 / tile_size; ii++) {

            Instance* tile_ins = new Instance(tile);
            
            tile_ins->translate(i * tile_size, 0, i * tile_size * .333333);
            tile_ins->translate(ii * -.333333 * tile_size, 0, ii * tile_size);
            tile_ins->rotate_y(45);
            tile_ins->translate(-3.5, 0, 0);
            
            Point3D p = tile_ins->get_forward_matrix() * Point3D(0, 0, 0);
            
            if (p.x < 0 - tile_size || p.x > 5 + tile_size || p.z < 0 - tile_size || p.z > 5 + tile_size)
                continue;
            else
                add_object(tile_ins);
        }
    }

    RectangleObject* refl = new RectangleObject(0, -tile_height, 0, 5, 0, 0, 0, 0, 5, 0, 1, 0);
    refl->set_material(r_mat);
    add_object(refl);

    Plane* floor = new Plane(Point3D(0, -tile_height - .01, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);


    // walls:

    double win_bot = .75;
    double win_in_width = 1;
    double win_height = 3.25;
    double win_width = 3;
    double height = 5;


    RectangleObject* west_bottom = new RectangleObject(0, -tile_height, 0, 0, 0, 5, 0, win_bot, 0, 1, 0, 0);
    west_bottom->set_material(mat_red);
    add_object(west_bottom);

    RectangleObject* west_in = new RectangleObject(0, win_bot, 0, 0, 0, win_in_width, 0, win_height, 0, 1, 0, 0);
    west_in->set_material(mat_red);
    add_object(west_in);

    RectangleObject* west_out = new RectangleObject(0, win_bot, win_in_width + win_width, 0, 0, 5 - win_in_width - win_width, 0, win_height, 0, 1, 0, 0);
    west_out->set_material(mat_red);
    add_object(west_out);

    RectangleObject* west_top = new RectangleObject(0, height, 0, 0, -height + win_height + win_bot, 0, 0, 0, 5, 1, 0, 0);
    west_top->set_material(mat_red);
    add_object(west_top);


    RectangleObject* north_bottom = new RectangleObject(0, -tile_height, 0, 5, 0, 0, 0, win_bot, 0, 0, 0, 1);
    north_bottom->set_material(mat_green);
    add_object(north_bottom);

    RectangleObject* north_in = new RectangleObject(0, win_bot, 0, win_in_width, 0, 0, 0, win_height, 0, 0, 0, 1);
    north_in->set_material(mat_green);
    add_object(north_in);

    RectangleObject* north_out = new RectangleObject(win_in_width + win_width, win_bot, 0, 5 - win_in_width - win_width, 0, 0, 0, win_height, 0, 0, 0, 1);
    north_out->set_material(mat_green);
    add_object(north_out);

    RectangleObject* north_top = new RectangleObject(0, height, 0, 0, -height + win_height + win_bot, 0, 5, 0, 0, 0, 0, 1);
    north_top->set_material(mat_green);
    add_object(north_top);

    
    RectangleObject* south = new RectangleObject(0, -tile_height, 5, 5, 0, 0, 0, height, 0, 0, 0, -1);
    south->set_material(mat_green);
    add_object(south);

    RectangleObject* east = new RectangleObject(5, -tile_height, 0, 0, 0, 5, 0, height, 0, -1, 0, 0);
    east->set_material(mat_red);
    add_object(east);

    RectangleObject* ceiling = new RectangleObject(0, height, 0, 5, 0, 0, 0, 0, 5, 0, -1, 0);
    ceiling->set_material(mat);
    add_object(ceiling);
    

    // window frames
    double bottom_depth = 1;
    double bottom_height = .2;
    double bottom_width = win_width + .6;

    Box* bottom_frame = new Box(-bottom_width * .5, -bottom_height * .5, -bottom_depth * .5, bottom_width * .5, bottom_height * .5, bottom_depth * .5);
    bottom_frame->set_material(mat);

    Instance* west_bottom_frame = new Instance(bottom_frame);
    west_bottom_frame->rotate_y(90);
    west_bottom_frame->translate(0, win_bot - bottom_height * .5, win_in_width + .5 * win_width);
    add_object(west_bottom_frame);

    Instance* north_bottom_frame = new Instance(bottom_frame);
    north_bottom_frame->translate(win_in_width + .5 * win_width, win_bot - bottom_height * .5, 0);
    add_object(north_bottom_frame);


    double side_depth = .4;
    double side_width = .2;

    Box* side_frame = new Box(-side_width * .5, win_bot, -side_depth * .5, side_width * .5, win_bot + win_height, side_depth * .5);
    side_frame->set_material(mat);

    Instance* north_side_frame_w = new Instance(side_frame);
    north_side_frame_w->translate(win_in_width - side_width * .5, 0, 0);
    add_object(north_side_frame_w);

    Instance* north_side_frame_e = new Instance(side_frame);
    north_side_frame_e->translate(win_in_width + win_width + side_width * .5, 0, 0);
    add_object(north_side_frame_e);

    Instance* west_side_frame_n = new Instance(side_frame);
    west_side_frame_n->rotate_y(90);
    west_side_frame_n->translate(0, 0, win_in_width - side_width * .5);
    add_object(west_side_frame_n);

    Instance* west_side_frame_s = new Instance(side_frame);
    west_side_frame_s->rotate_y(90);
    west_side_frame_s->translate(0, 0, win_in_width + win_width + side_width * .5);
    add_object(west_side_frame_s);


    double top_height = .4;

    Box* top_frame = new Box(-side_width - win_width * .5, -top_height * .5, -side_depth * .5, side_width + win_width * .5, top_height * .5, side_depth * .5);
    top_frame->set_material(mat);

    Instance* north_top_frame = new Instance(top_frame);
    north_top_frame->translate(win_in_width + win_width * .5, win_bot + win_height + top_height * .5, 0);
    add_object(north_top_frame);

    Instance* west_top_frame = new Instance(top_frame);
    west_top_frame->rotate_y(90);
    west_top_frame->translate(0, win_bot + win_height + top_height * .5, win_in_width + win_width * .5);
    add_object(west_top_frame);


    double bar_radius = .08;

    Cylinder* bar_v = new Cylinder(win_bot, win_bot + win_height, bar_radius);
    bar_v->set_material(copper);

    Cylinder* bar_h = new Cylinder(-win_width * .5, win_width * .5, bar_radius);
    bar_h->set_material(copper);

    Instance* north_bar_v = new Instance(bar_v);
    north_bar_v->translate(win_in_width + win_width * .5, 0, 0);
    add_object(north_bar_v);

    Instance* north_bar_h_1 = new Instance(bar_h);
    north_bar_h_1->rotate_x(90);
    north_bar_h_1->translate(0, win_bot + win_height / 3, win_in_width + win_width * .5);
    add_object(north_bar_h_1);

    Instance* north_bar_h_2 = new Instance(bar_h);
    north_bar_h_2->rotate_x(90);
    north_bar_h_2->translate(0, win_bot + win_height * 2 / 3, win_in_width + win_width * .5);
    add_object(north_bar_h_2);

    Instance* west_bar_v = new Instance(bar_v);
    west_bar_v->translate(0, 0, win_in_width + win_width * .5);
    add_object(west_bar_v);

    Instance* west_bar_h_1 = new Instance(bar_h);
    west_bar_h_1->rotate_z(90);
    west_bar_h_1->translate(win_in_width + win_width * .5, win_bot + win_height / 3, 0);
    add_object(west_bar_h_1);

    Instance* west_bar_h_2 = new Instance(bar_h);
    west_bar_h_2->rotate_z(90);
    west_bar_h_2->translate(win_in_width + win_width * .5, win_bot + win_height * 2 / 3, 0);
    add_object(west_bar_h_2);


    // spheres:

    double r = .2;
    double h = sqrt(2 * r * r); // height of a pyramid

    // iron:
    Sphere* iron_ball = new Sphere(Point3D(0, 0, 0), r);
    iron_ball->set_material(iron);

    for (int i(0); i < 4; i++)
        for (int ii(0); ii < 4; ii++) {
            
            Instance* ball = new Instance(iron_ball);
            ball->translate(-3 * r + i * 2 * r, r, -3 * r + ii * 2 * r);
            ball->rotate_y(45);
            ball->translate(2.5, 0, 2.5);
            add_object(ball);
        }

    // copper:
    Sphere* copper_ball = new Sphere(Point3D(0, 0, 0), r);
    copper_ball->set_material(copper);

    for (int i(0); i < 3; i++)
        for (int ii(0); ii < 3; ii++) {

            Instance* ball = new Instance(copper_ball);
            ball->translate(-2 * r + i * 2 * r, r + h, -2 * r + ii * 2 * r);
            ball->rotate_y(45);
            ball->translate(2.5, 0, 2.5);
            add_object(ball);
        }

    // silver:
    Sphere* silver_ball = new Sphere(Point3D(0, 0, 0), r);
    silver_ball->set_material(silver);

    for (int i(0); i < 2; i++)
        for (int ii(0); ii < 2; ii++) {

            Instance* ball = new Instance(silver_ball);
            ball->translate(-r + i * 2 * r, r + 2 * h, -r + ii * 2 * r);
            ball->rotate_y(45);
            ball->translate(2.5, 0, 2.5);
            add_object(ball);
        }

    // gold:
    Sphere* gold_ball = new Sphere(Point3D(2.5, r + 3 * h, 2.5), r);
    gold_ball->set_material(gold);
    add_object(gold_ball);
}


