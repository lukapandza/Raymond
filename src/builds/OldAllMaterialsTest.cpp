void
World::build() {

    int num_samples = 1024;

    vp.set_hres(256);
    vp.set_vres(256);
    vp.set_samples(num_samples);
    vp.set_max_depth(10);

    background_color = black;

    //tracer_ptr = new AreaLighting(this);
    tracer_ptr = new PathTrace(this);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(5, 2.5, 5);
    pinhole_ptr->set_lookat(1, 2.5, 1);
    pinhole_ptr->set_view_distance(12.0);
    pinhole_ptr->set_zoom(10.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.2);
    set_ambient_light(ambient_ptr);

    //lights: 
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(16);
    emissive_ptr1->set_ce(1.0, 0.89, 0.72);

    Sampler* sampler_ptr = new MultiJittered(num_samples);

    double light_size = .75;

    RectangleObject* rectangle_ptr1 = new RectangleObject(2, 4.99, 2, light_size, 0, 0, 0, 0, light_size, 0, -1, 0);
    rectangle_ptr1->set_material(emissive_ptr1);
    rectangle_ptr1->set_sampler(sampler_ptr);
    add_object(rectangle_ptr1);

    AreaLight* area_light_ptr1 = new AreaLight;
    area_light_ptr1->set_object(rectangle_ptr1);
    area_light_ptr1->set_shadows(true);
    add_light(area_light_ptr1);

    RectangleObject* rectangle_ptr2 = new RectangleObject(5, 4.99, 2, -light_size, 0, 0, 0, 0, light_size, 0, -1, 0);
    rectangle_ptr2->set_material(emissive_ptr1);
    rectangle_ptr2->set_sampler(sampler_ptr);
    add_object(rectangle_ptr2);

    AreaLight* area_light_ptr2 = new AreaLight;
    area_light_ptr2->set_object(rectangle_ptr2);
    area_light_ptr2->set_shadows(true);
    add_light(area_light_ptr2);

    RectangleObject* rectangle_ptr3 = new RectangleObject(2, 4.99, 5, light_size, 0, 0, 0, 0, -light_size, 0, -1, 0);
    rectangle_ptr3->set_material(emissive_ptr1);
    rectangle_ptr3->set_sampler(sampler_ptr);
    add_object(rectangle_ptr3);

    AreaLight* area_light_ptr3 = new AreaLight;
    area_light_ptr3->set_object(rectangle_ptr3);
    area_light_ptr3->set_shadows(true);
    add_light(area_light_ptr3);

    RectangleObject* rectangle_ptr4 = new RectangleObject(5, 4.99, 5, -light_size, 0, 0, 0, 0, -light_size, 0, -1, 0);
    rectangle_ptr4->set_material(emissive_ptr1);
    rectangle_ptr4->set_sampler(sampler_ptr);
    add_object(rectangle_ptr4);

    AreaLight* area_light_ptr4 = new AreaLight;
    area_light_ptr4->set_object(rectangle_ptr4);
    area_light_ptr4->set_shadows(true);
    add_light(area_light_ptr4);


    //materials:
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
    p_mat->set_samples(num_samples, 32);
    p_mat->set_ka(.4);
    p_mat->set_kd(.35);
    p_mat->set_cd(1, 1, 1);
    p_mat->set_cs(1, 1, 1);
    p_mat->set_ks(.65);

    Reflective* reflective = new Reflective;
    reflective->set_ka(0);
    reflective->set_kd(.025);
    reflective->set_ks(.025);
    reflective->set_kr(.95);
    reflective->set_cd(1);
    reflective->set_cs(1);
    reflective->set_cr(1);

    GlossyReflector* glossy_ptr = new GlossyReflector;
    glossy_ptr->set_samples(num_samples, 16);
    glossy_ptr->set_ka(0);
    glossy_ptr->set_kd(.025);
    glossy_ptr->set_ks(.025);
    glossy_ptr->set_kr(.95);
    glossy_ptr->set_cd(1);
    glossy_ptr->set_cs(1);
    glossy_ptr->set_cr(1);
    glossy_ptr->set_exponent(10000);



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
    RectangleObject* north_mirror = new RectangleObject(2, 0, 1.01, 3, 0, 0, 0, 4, 0, 0, 0, 1);
    north_mirror->set_material(reflective);
    add_object(north_mirror);

    RectangleObject* south_mirror = new RectangleObject(2, 0, 5.99, 3, 0, 0, 0, 4, 0, 0, 0, -1);
    south_mirror->set_material(reflective);
    add_object(south_mirror);

    RectangleObject* east_mirror = new RectangleObject(1.01, 0, 2, 0, 0, 3, 0, 4, 0, 1, 0, 0);
    east_mirror->set_material(glossy_ptr);
    add_object(east_mirror);

    RectangleObject* west_mirror = new RectangleObject(5.99, 0, 2, 0, 0, 3, 0, 4, 0, -1, 0, 0);
    west_mirror->set_material(glossy_ptr);
    add_object(west_mirror);

    // pyramid:
    Triangle* nw = new Triangle(3.5, 0, 3.0, 3, 0, 3.5, 3.5, 3, 3.5);
    nw->set_material(mat_blue);
    add_object(nw);
    
    Triangle* ne = new Triangle(3.5, 0, 3, 4, 0, 3.5, 3.5, 3, 3.5);
    ne->set_material(mat_blue);
    add_object(ne);
    
    Triangle* se = new Triangle(4, 0, 3.5, 3.5, 0, 4, 3.5, 3, 3.5);
    se->set_material(mat_blue);
    add_object(se);
    
    Triangle* sw = new Triangle(3.5, 0, 4, 3, 0, 3.5, 3.5, 3, 3.5);
    sw->set_material(mat_blue);
    add_object(sw);
    
}