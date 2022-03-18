void
World::build() {

    int num_samples = 256;

    vp.set_hres(256);
    vp.set_vres(256);
    vp.set_samples(num_samples);
    //vp.set_max_depth(2);      // 00:00:02.849
    //vp.set_max_depth(4);      // 00:00:04.887
    //vp.set_max_depth(6);      // 00:00:06.516
    //vp.set_max_depth(8);      // 00:00:08.542
    //vp.set_max_depth(10);     // 00:00:10.164
    //vp.set_max_depth(12);     // 00:00:12.178
    //vp.set_max_depth(14);     // 00:00:13.020
    //vp.set_max_depth(16);     // 00:00:14.625
    vp.set_max_depth(8);

    background_color = black;

    //tracer_ptr = new AreaLighting(this);
    tracer_ptr = new PathTrace(this);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(5, 3.5, 5);
    pinhole_ptr->set_lookat(2, 2.5, 2);
    pinhole_ptr->set_view_distance(12.0);
    //pinhole_ptr->set_zoom(3);
    pinhole_ptr->set_zoom(12);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.2);
    set_ambient_light(ambient_ptr);

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    //materials:
    Emissive* emissive_ptr1 = new Emissive;
    //emissive_ptr1->set_ls(12);
    emissive_ptr1->set_ls(16);
    emissive_ptr1->set_ce(1.0, 0.89, 0.72);

    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(0.25);
    mat->set_kd(1);
    mat->set_cd(1); // white

    Matte* mat_red = new Matte(*mat);
    mat_red->set_cd(.66, 0.17, 0.14);

    Matte* mat_green = new Matte(*mat);
    mat_green->set_cd(0.18, .48, 0.43);

    Matte* mat_blue = new Matte(*mat);
    mat_blue->set_cd(.57, .78, .99);

    Phong* p_mat = new Phong();
    p_mat->set_samples(num_samples);
    p_mat->set_exp(32);
    p_mat->set_ka(.4);
    p_mat->set_kd(.35);
    p_mat->set_cd(1, 1, 1);
    p_mat->set_cs(1, 1, 1);
    p_mat->set_ks(.65);

    Reflective* reflective = new Reflective;
    reflective->set_ka(0);
    reflective->set_kd(0);
    reflective->set_ks(0);
    reflective->set_kr(1);
    reflective->set_cd(1, 1, 1);
    reflective->set_cs(1, 1, 1);
    reflective->set_cr(1);

    GlossyReflector* glossy_ptr = new GlossyReflector;
    glossy_ptr->set_samples(num_samples);
    glossy_ptr->set_ka(0);
    glossy_ptr->set_kd(0);
    glossy_ptr->set_ks(0);
    glossy_ptr->set_kr(1);
    glossy_ptr->set_cd(1, 1, 1);
    glossy_ptr->set_cs(1, 1, 1);
    glossy_ptr->set_cr(1, 1, 1);
    glossy_ptr->set_exp_s(16);
    glossy_ptr->set_exp_r(50000);

    GlossyReflector* orb_mat = new GlossyReflector;
    orb_mat->set_samples(num_samples);
    orb_mat->set_ka(0);
    orb_mat->set_kd(.4);
    orb_mat->set_ks(.4);
    orb_mat->set_kr(.1);
    orb_mat->set_cd(0, 0, 0);
    orb_mat->set_cs(0, 0, 0);
    orb_mat->set_cr(.05, .2, .05); // green
    orb_mat->set_exp_s(16);
    orb_mat->set_exp_r(2048);

    Phong* copper = new Phong;
    copper->set_samples(num_samples);
    copper->set_exp(100);
    copper->set_ka(.4);
    copper->set_kd(.35);
    copper->set_cd(.72, .45, .2);
    copper->set_ks(.65);
    copper->set_cs(.72, .45, .2);

    Phong* gold = new Phong(*copper);
    gold->set_cd(.83, .68, .22); // gold
    gold->set_cs(.83, .68, .22); // gold

    // lights:
    double light_height = 4.5;
    double light_radius = .33;
    double ring_thickness = .067;

    Torus* light_ring = new Torus(light_radius, ring_thickness);
    light_ring->set_sampler(sampler_ptr);
    light_ring->set_material(copper);

    std::vector<Point3D> locations = { Point3D(2.25, light_height, 2.25), Point3D(4.75, light_height, 2.25), Point3D(2.25, light_height, 4.75), Point3D(4.75, light_height, 4.75) };

    for (int i(0); i < locations.size(); i++) {

        Sphere* sphere = new Sphere(locations[i], light_radius);
        sphere->set_sampler(sampler_ptr);
        sphere->set_material(emissive_ptr1);
        add_object(sphere);

        AreaLight* area_light = new AreaLight;
        area_light->set_object(sphere);
        area_light->set_shadows(true);
        add_light(area_light);

        
        Instance* ring1 = new Instance(light_ring);
        ring1->rotate_x(90);
        ring1->rotate_y(45);
        ring1->translate(locations[i]);
        add_object(ring1);

        Instance* ring2 = new Instance(light_ring);
        ring2->rotate_x(90);
        ring2->rotate_y(-45);
        ring2->translate(locations[i]);
        add_object(ring2);
    }

    // walls:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(p_mat);
    add_object(floor);

    Plane* ceiling = new Plane(Point3D(0, 5.0, 0), Normal(0.0024, -1, 0.00093));
    ceiling->set_material(mat);
    add_object(ceiling);

    Plane* west = new Plane(Point3D(1, 0, 0), Normal(1, 0, 0));
    west->set_material(mat_red);
    add_object(west);

    Plane* north = new Plane(Point3D(0, 0, 1), Normal(0, 0, 1));
    north->set_material(mat_green);
    add_object(north);

    Plane* east = new Plane(Point3D(6, 0, 0), Normal(-1, 0, 0));
    east->set_material(mat_red);
    add_object(east);

    Plane* south = new Plane(Point3D(0, 0, 6), Normal(0, 0, -1));
    south->set_material(mat_green);
    add_object(south);

    // mirrors:
    double gap = .15;
    
    RectangleObject* north_mirror = new RectangleObject(2, 0, 1 + gap, 3, 0, 0, 0, 4, 0, 0, 0, 1);
    north_mirror->set_material(reflective);
    add_object(north_mirror);

    RectangleObject* south_mirror = new RectangleObject(2, 0, 6 - gap, 3, 0, 0, 0, 4, 0, 0, 0, -1);
    south_mirror->set_material(reflective);
    add_object(south_mirror);

    RectangleObject* east_mirror = new RectangleObject(1 + gap, 0, 2, 0, 0, 3, 0, 4, 0, 1, 0, 0);
    east_mirror->set_material(glossy_ptr);
    add_object(east_mirror);

    RectangleObject* west_mirror = new RectangleObject(6 - gap, 0, 2, 0, 0, 3, 0, 4, 0, -1, 0, 0);
    west_mirror->set_material(glossy_ptr);
    add_object(west_mirror);
    

    // pyramid:
    std::vector<Point3D> corners = { Point3D(3.5, 0, 3), Point3D(4, 0, 3.5), Point3D(3.5, 0, 4), Point3D(3, 0, 3.5) };
    Point3D peak(3.5, 1.5, 3.5);

    for (int i(0); i < corners.size(); i++) {
        Triangle* triangle = new Triangle(corners[i], corners[(i + 1) % corners.size()], peak);
        triangle->set_material(orb_mat);
        add_object(triangle);
    }
    
    // orb:
    double orb_radius = .5;
    double spacing = 0;
    double orb_ring_thickness = .04;

    /*
    Sphere* orb = new Sphere(Point3D(3.5, peak.y + spacing + orb_radius, 3.5), orb_radius);
    orb->set_material(orb_mat);
    add_object(orb);
    */

    Torus* orb_ring = new Torus(orb_radius, orb_ring_thickness);
    orb_ring->set_sampler(sampler_ptr);
    orb_ring->set_material(gold);

    Torus* orb_ring_l = new Torus(sqrt(orb_radius * orb_radius + (orb_radius + .5 * spacing) * (orb_radius + .5 * spacing)), orb_ring_thickness);
    orb_ring_l->set_sampler(sampler_ptr);
    orb_ring_l->set_material(gold);

    
    Instance* orb_ring1 = new Instance(orb_ring);
    orb_ring1->rotate_x(90);
    orb_ring1->rotate_y(45);
    orb_ring1->translate(Point3D(3.5, peak.y + spacing + orb_radius, 3.5));
    add_object(orb_ring1);

    Instance* orb_ring2 = new Instance(orb_ring);
    orb_ring2->rotate_x(90);
    orb_ring2->rotate_y(-45);
    orb_ring2->translate(Point3D(3.5, peak.y + spacing + orb_radius, 3.5));
    add_object(orb_ring2);
    

    Instance* orb_ring3 = new Instance(orb_ring);
    orb_ring3->translate(Point3D(3.5, peak.y + spacing + orb_radius, 3.5));
    add_object(orb_ring3);
    
    /*
    Instance* orb_ring_l1 = new Instance(orb_ring_l);
    orb_ring_l1->rotate_x(90);
    orb_ring_l1->rotate_y(45);
    orb_ring_l1->translate(Point3D(3.5, peak.y + .5 * spacing, 3.5));
    add_object(orb_ring_l1);

    Instance* orb_ring_l2 = new Instance(orb_ring_l);
    orb_ring_l2->rotate_x(90);
    orb_ring_l2->rotate_y(-45);
    orb_ring_l2->translate(Point3D(3.5, peak.y + .5 * spacing, 3.5));
    add_object(orb_ring_l2);
    */
    
}