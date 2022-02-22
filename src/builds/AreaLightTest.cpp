void
World::build() {

    int num_samples = 400;

    vp.set_hres(1080);
    vp.set_vres(720);
    vp.set_pixel_size(1);
    vp.set_samples(num_samples);

    background_color = black;
    tracer_ptr = new RayCast(this);

    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(15, 6, 23);
    pinhole_ptr->set_lookat(6, -1, 9);
    pinhole_ptr->set_view_distance(100.0);
    pinhole_ptr->set_zoom(4.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:
    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.4);
    set_ambient_light(ambient_ptr);
    
    MultiJittered* sampler_ptr = new MultiJittered(num_samples);

    //material 1:
    Matte* matte_ptr = new Matte();
    matte_ptr->set_ka(0.4);
    matte_ptr->set_kd(0.8);
    matte_ptr->set_cd(1.0);

    //material 2:
    Phong* phong_ptr2 = new Phong();
    phong_ptr2->set_ka(0.0);
    phong_ptr2->set_kd(0.9);
    phong_ptr2->set_cd(1); // white
    phong_ptr2->set_ks(0.6);

    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(2.0);
    emissive_ptr1->set_ce(0, 0, 1);

    Emissive* emissive_ptr2 = new Emissive;
    emissive_ptr2->set_ls(2.0);
    emissive_ptr2->set_ce(0, 1, 0);

    Emissive* emissive_ptr3 = new Emissive;
    emissive_ptr3->set_ls(2.0);
    emissive_ptr3->set_ce(1, 0, 0);

    Rect* rectangle_ptr1 = new Rect(-2, 0, 4, 0, 0, 2, 0, 6, 0, 1, 0, 0);
    rectangle_ptr1->set_material(emissive_ptr1);
    rectangle_ptr1->set_sampler(sampler_ptr);
    add_object(rectangle_ptr1);

    Rect* rectangle_ptr2 = new Rect(-2, 0, 8, 0, 0, 2, 0, 6, 0, 1, 0, 0);
    rectangle_ptr2->set_material(emissive_ptr2);
    rectangle_ptr2->set_sampler(sampler_ptr);
    add_object(rectangle_ptr2);

    Rect* rectangle_ptr3 = new Rect(-2, 0, 12, 0, 0, 2, 0, 6, 0, 1, 0, 0);
    rectangle_ptr3->set_material(emissive_ptr3);
    rectangle_ptr3->set_sampler(sampler_ptr);
    add_object(rectangle_ptr3);

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

    for (int i = 0; i < 8; i++) {

        Box* box = new Box(5, 0, 3 * i - 2, 6, 5, 3 * i - 1);
        box->set_material(phong_ptr2);
        add_object(box);
    }

    //floor plane:
    Plane* plane_ptr1 = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    plane_ptr1->set_material(phong_ptr2);
    add_object(plane_ptr1);
}