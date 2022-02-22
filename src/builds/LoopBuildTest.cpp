void
World::build() {

    int num_samples = 512;

    vp.set_hres(1080);
    vp.set_vres(720);
    vp.set_pixel_size(1);
    vp.set_samples(num_samples);

    background_color = black;
    tracer_ptr = new AreaLighting(this);

    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(7, 3, 17);
    pinhole_ptr->set_lookat(0, -7.5, 0);
    pinhole_ptr->set_view_distance(100.0);
    pinhole_ptr->set_zoom(5.0);
    //pinhole_ptr->set_eye(1.5, -12, -5.5);
    //pinhole_ptr->set_lookat(-1.5, -1, -2.5);
    //pinhole_ptr->set_view_distance(100.0);
    //pinhole_ptr->set_zoom(4.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:
    
    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.05);
    set_ambient_light(ambient_ptr);
    
    /*
    AmbientOccluder* occluder_ptr = new AmbientOccluder;
    occluder_ptr->set_intensity(0.9);
    occluder_ptr->set_color(white);
    occluder_ptr->set_min(0.05);
    occluder_ptr->set_sampler(sampler_ptr);
    set_ambient_light(occluder_ptr);
    */

    /*
    // point light 1:
    PointLight* light_ptr1 = new PointLight();
    light_ptr1->set_location(-12, 16, 14);
    light_ptr1->set_intensity(0.7);
    light_ptr1->set_color(1);
    add_light(light_ptr1);

    // point light 2:
    PointLight* light_ptr2 = new PointLight();
    light_ptr2->set_location(10, 12, 12);
    light_ptr2->set_intensity(0.8);
    light_ptr2->set_color(1);
    add_light(light_ptr2);
    */

    //material 1:
    Phong* phong_ptr1 = new Phong();
    phong_ptr1->set_ka(0.8);
    phong_ptr1->set_kd(0.7);
    phong_ptr1->set_cd(.9, .6, .6);
    phong_ptr1->set_ks(0.4);

    //material 2:
    Phong* phong_ptr2 = new Phong();
    phong_ptr2->set_ka(0.4);
    phong_ptr2->set_kd(0.9);
    phong_ptr2->set_cd(1); // white
    phong_ptr2->set_ks(0.2);

    //material 3:
    Phong* phong_ptr3 = new Phong();
    phong_ptr3->set_ka(0.6);
    phong_ptr3->set_kd(0.8);
    phong_ptr3->set_cd(.5, .9, .9);
    phong_ptr3->set_ks(0.6);

    int stack_height = 12;
    double base = -stack_height - 4;

    for (int i = 0; i < stack_height / 2; i++) {

        Box* box1 = new Box(-4.5, base + 2 * i, -2.5, 4.5, base + 1 + 2 * i, -1.5);
        box1->set_material(phong_ptr1);
        add_object(box1);

        Box* box2 = new Box(-4.5, base + 2 * i, 1.5, 4.5, base + 1 + 2 * i, 2.5);
        box2->set_material(phong_ptr3);
        add_object(box2);

        Box* box3 = new Box(-2.5, base + 1 + 2 * i, -4.5, -1.5, base + 2 + 2 * i, 4.5);
        box3->set_material(phong_ptr1);
        add_object(box3);

        Box* box4 = new Box(1.5, base + 1 + 2 * i, -4.5, 2.5, base + 2 + 2 * i, 4.5);
        box4->set_material(phong_ptr3);
        add_object(box4);
    }

    MultiJittered* sampler_ptr = new MultiJittered(num_samples);

    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(1024.0);
    emissive_ptr1->set_ce(1);

    // torus:

    Torus* torus_ptr1 = new Torus(6, .5);
    torus_ptr1->set_material(emissive_ptr1);
    torus_ptr1->set_sampler(sampler_ptr);
    add_object(torus_ptr1);

    /*
    Rect* rect_ptr1 = new Rect(-1, 0, -1, 2, 0, 0, 0, 0, 2, 0, -1, 0);
    rect_ptr1->set_material(emissive_ptr1);
    rect_ptr1->set_sampler(sampler_ptr);
    add_object(rect_ptr1);
    */

    AreaLight* area_light_ptr1 = new AreaLight;
    area_light_ptr1->set_object(torus_ptr1);
    area_light_ptr1->set_shadows(true);
    add_light(area_light_ptr1);

    //floor plane:
    Plane* plane_ptr1 = new Plane(Point3D(0, base, 0), Normal(0, 1, 0));
    plane_ptr1->set_material(phong_ptr2);
    add_object(plane_ptr1);
}