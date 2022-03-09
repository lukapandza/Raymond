void
World::build() {

    int num_samples = 900;

    vp.set_hres(512);
    vp.set_vres(512);
    vp.set_samples(num_samples);
    vp.set_max_depth(12);

    background_color = black;

    //tracer_ptr = new AreaLighting(this);
    tracer_ptr = new PathTrace(this);
    //tracer_ptr = new GlobalTrace(this);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(3.5, 2.5, 20);
    //pinhole_ptr->set_eye(3.5, 2.5, 11.9);
    pinhole_ptr->set_lookat(3.5, 2.5, 0);
    pinhole_ptr->set_view_distance(12.0);
    //pinhole_ptr->set_view_distance(5.0);
    pinhole_ptr->set_zoom(100.0);
    //pinhole_ptr->set_zoom(80.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.4);
    set_ambient_light(ambient_ptr);

    //light: 
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(24);
    //emissive_ptr1->set_ls(64);
    //emissive_ptr1->set_ce(1.0, 0.83, 0.6);
    emissive_ptr1->set_ce(1.0, 0.89, 0.72);

    Sampler* sampler_ptr = new MultiJittered(num_samples);


    RectangleObject* rectangle_ptr1 = new RectangleObject(3, 4.99, 4, 1, 0, 0, 0, 0, -1, 0, -1, 0);
    rectangle_ptr1->set_material(emissive_ptr1);
    rectangle_ptr1->set_sampler(sampler_ptr);
    add_object(rectangle_ptr1);

    AreaLight* area_light_ptr1 = new AreaLight;
    area_light_ptr1->set_object(rectangle_ptr1);
    area_light_ptr1->set_shadows(true);
    add_light(area_light_ptr1);

    RectangleObject* rectangle_ptr2 = new RectangleObject(3, 4.99, 8, 1, 0, 0, 0, 0, -1, 0, -1, 0);
    rectangle_ptr2->set_material(emissive_ptr1);
    rectangle_ptr2->set_sampler(sampler_ptr);
    add_object(rectangle_ptr2);

    AreaLight* area_light_ptr2 = new AreaLight;
    area_light_ptr2->set_object(rectangle_ptr2);
    area_light_ptr2->set_shadows(true);
    add_light(area_light_ptr2);

    RectangleObject* rectangle_ptr3 = new RectangleObject(3, 4.99, 12, 1, 0, 0, 0, 0, -1, 0, -1, 0);
    rectangle_ptr3->set_material(emissive_ptr1);
    rectangle_ptr3->set_sampler(sampler_ptr);
    add_object(rectangle_ptr3);

    AreaLight* area_light_ptr3 = new AreaLight;
    area_light_ptr3->set_object(rectangle_ptr3);
    area_light_ptr3->set_shadows(true);
    add_light(area_light_ptr3);

    RectangleObject* rectangle_ptr4 = new RectangleObject(3, 4.99, 16, 1, 0, 0, 0, 0, -1, 0, -1, 0);
    rectangle_ptr4->set_material(emissive_ptr1);
    rectangle_ptr4->set_sampler(sampler_ptr);
    add_object(rectangle_ptr4);

    AreaLight* area_light_ptr4 = new AreaLight;
    area_light_ptr4->set_object(rectangle_ptr4);
    area_light_ptr4->set_shadows(true);
    add_light(area_light_ptr4);

    /*
    Sphere* sphere_ptr = new Sphere(Point3D(3.5, 4.75, 5.5), .25);
    sphere_ptr->set_material(emissive_ptr1);
    //sphere_ptr->set_sampler(new MultiJittered(512));
    sphere_ptr->set_sampler(sampler_ptr);
    add_object(sphere_ptr);
    */

    

    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(0.25);
    mat->set_kd(1);
    mat->set_cd(1); // white

    Phong2* p_mat = new Phong2();
    p_mat->set_samples(num_samples);
    p_mat->set_ka(.25);
    p_mat->set_kd(.35);
    p_mat->set_c(.47, .54, .86); // blue
    p_mat->set_ks(.65);
    p_mat->set_exp(32);

    //walls:
    
    Phong2* p_mat_white = new Phong2(*p_mat);
    p_mat_white->set_ks(0);
    p_mat_white->set_kd(1);
    p_mat_white->set_c(1.0, 1.0, 1.0);
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(p_mat);
    add_object(floor);

    Plane* ceiling = new Plane(Point3D(0, 5.0, 0), Normal(0.0024, -1, 0.00093));
    ceiling->set_material(mat);
    add_object(ceiling);

    Matte* mat_red = new Matte(*mat);
    mat_red->set_cd(.66, 0.17, 0.14);
    Plane* west = new Plane(Point3D(1, 0, 0), Normal(1, 0, 0));
    west->set_material(mat_red);
    add_object(west);

    Plane* north = new Plane(Point3D(0, 0, 1), Normal(0, 0, 1));
    north->set_material(p_mat_white);
    add_object(north);

    Matte* mat_green = new Matte(*mat);
    mat_green->set_cd(0.18, .48, 0.43);
    Plane* east = new Plane(Point3D(6, 0, 0), Normal(-1, 0, 0));
    east->set_material(mat_green);
    add_object(east);

    //boxes:
    Instance* box1 = new Instance(new Box(-0.75, 0, -0.75, 0.75, 3.0, 0.75));
    box1->set_material(mat);
    box1->rotate_y(15);
    box1->translate(2.5, 0, 2.75);
    add_object(box1);

    Instance* box2 = new Instance(new Box(-0.75, 0, -0.75, 0.75, 1.5, 0.75));
    box2->set_material(mat);
    box2->rotate_y(-15);
    box2->translate(4.5, 0, 3);
    add_object(box2);

    Phong2* p_mat_copper = new Phong2(*p_mat);
    p_mat_copper->set_c(0.72, 0.45, 0.2);

    for (int i = 0; i < 5; i++) {

        float exp = pow(10.0, i);

        Phong2* mat = new Phong2(*p_mat_copper);
        mat->set_exp(exp);

        double radius = 0.4;

        Sphere* sphere = new Sphere(Point3D(i + 1.5, radius, 6.5), radius);
        sphere->set_material(mat);
        add_object(sphere);
    }
}