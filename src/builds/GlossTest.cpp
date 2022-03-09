void
World::build() {

    int num_samples = 900;

    vp.set_hres(480);
    vp.set_vres(270);
    vp.set_samples(num_samples);
    vp.set_max_depth(24);

    background_color = black;
    //tracer_ptr = new AreaLighting(this);
    tracer_ptr = new PathTrace(this);

    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(5, 1, 9);
    pinhole_ptr->set_lookat(5, 1, 0);
    pinhole_ptr->set_view_distance(100.0);
    pinhole_ptr->set_zoom(3.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:
    
    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.2);
    set_ambient_light(ambient_ptr);
    

    MultiJittered* light_sampler_ptr = new MultiJittered(num_samples);
    /*
    AmbientOccluder* occluder_ptr = new AmbientOccluder;
    occluder_ptr->set_intensity(0.9);
    occluder_ptr->set_color(white);
    occluder_ptr->set_min(0.00);
    occluder_ptr->set_sampler(light_sampler_ptr);
    set_ambient_light(occluder_ptr);
    */

    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(8.0);
    emissive_ptr1->set_ce(1, 0, 0);

    Emissive* emissive_ptr2 = new Emissive;
    emissive_ptr2->set_ls(8.0);
    emissive_ptr2->set_ce(0, 1, 0);

    Emissive* emissive_ptr3 = new Emissive;
    emissive_ptr3->set_ls(8.0);
    emissive_ptr3->set_ce(0, 0, 1);

    Emissive* emissive_ptr4 = new Emissive;
    emissive_ptr4->set_ls(8.0);
    emissive_ptr4->set_ce(1);

    float height = 6.0;

    RectangleObject* rectangle_ptr1 = new RectangleObject(3, height, 3, 1, 0, -1, -1, 0, -1, 0, -1, 0);
    rectangle_ptr1->set_material(emissive_ptr1);
    rectangle_ptr1->set_sampler(light_sampler_ptr);
    add_object(rectangle_ptr1);

    RectangleObject* rectangle_ptr2 = new RectangleObject(5, height, 5, 1, 0, -1, -1, 0, -1, 0, -1, 0);
    rectangle_ptr2->set_material(emissive_ptr2);
    rectangle_ptr2->set_sampler(light_sampler_ptr);
    add_object(rectangle_ptr2);

    RectangleObject* rectangle_ptr3 = new RectangleObject(7, height, 3, 1, 0, -1, -1, 0, -1, 0, -1, 0);
    rectangle_ptr3->set_material(emissive_ptr3);
    rectangle_ptr3->set_sampler(light_sampler_ptr);
    add_object(rectangle_ptr3);

    RectangleObject* rectangle_ptr4 = new RectangleObject(5, height, 1, 1, 0, -1, -1, 0, -1, 0, -1, 0);
    rectangle_ptr4->set_material(emissive_ptr4);
    rectangle_ptr4->set_sampler(light_sampler_ptr);
    add_object(rectangle_ptr4);

    AreaLight* area_light_ptr1 = new AreaLight;
    area_light_ptr1->set_object(rectangle_ptr1);
    area_light_ptr1->set_shadows(true);
    add_light(area_light_ptr1);

    AreaLight* area_light_ptr2 = new AreaLight;
    area_light_ptr2->set_object(rectangle_ptr2);
    area_light_ptr2->set_shadows(true);
    add_light(area_light_ptr2);

    AreaLight* area_light_ptr3 = new AreaLight;
    area_light_ptr3->set_object(rectangle_ptr3);
    area_light_ptr3->set_shadows(true);
    add_light(area_light_ptr3);

    AreaLight* area_light_ptr4 = new AreaLight;
    area_light_ptr4->set_object(rectangle_ptr4);
    area_light_ptr4->set_shadows(true);
    add_light(area_light_ptr4);

    GlossyReflector* glossy_ptr = new GlossyReflector;
    glossy_ptr->set_samples(num_samples, 16);
    glossy_ptr->set_ka(.6);
    glossy_ptr->set_kd(.3);
    glossy_ptr->set_ks(.1);
    glossy_ptr->set_exp(16);
    //glossy_ptr->set_cd(0.9, 0.89, 0.89); // platinum
    glossy_ptr->set_c(0.72, 0.45, 0.2); // copper
    glossy_ptr->set_kr(.6);
    glossy_ptr->set_exponent(100);
    //glossy_ptr->set_cr(0.9, 0.89, 0.89); // platinum
    glossy_ptr->set_cr(0.72, 0.45, 0.2); // copper

    for (int i = 0; i < 5; i++) {

        double exp = pow(8.0, i);

        GlossyReflector* mat = new GlossyReflector(*glossy_ptr);
        mat->set_samples(num_samples, exp);
        mat->set_exponent(exp);

        double radius = 0.67;

        Sphere* sphere = new Sphere(Point3D(2 * i + 1, radius, 2), radius);
        sphere->set_material(mat);
        add_object(sphere);

    }

    Phong2* phong_ptr1 = new Phong2();
    phong_ptr1->set_samples(num_samples);
    phong_ptr1->set_ka(1);
    phong_ptr1->set_kd(.8);
    phong_ptr1->set_c(1, 1, 1); // white
    phong_ptr1->set_ks(.2);

    //floor plane:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(phong_ptr1);
    add_object(floor);

    Plane* ceiling = new Plane(Point3D(0, 6.01, 0), Normal(0, -1, 0));
    ceiling->set_material(phong_ptr1);
    add_object(ceiling);

    Plane* north = new Plane(Point3D(0, 0, -1), Normal(0, 0, 1));
    north->set_material(phong_ptr1);
    add_object(north);

    Plane* south = new Plane(Point3D(0, 0, 13), Normal(0, 0, -1));
    south->set_material(phong_ptr1);
    add_object(south);

    Plane* west = new Plane(Point3D(-2, 0, 0), Normal(1, 0, 0));
    west->set_material(phong_ptr1);
    add_object(west);

    Plane* east = new Plane(Point3D(12, 0, 0), Normal(-1, 0, 0));
    east->set_material(phong_ptr1);
    add_object(east);
}