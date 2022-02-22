void
World::build() {

    vp.set_hres(512);
    vp.set_vres(512);
    vp.set_pixel_size(1);
    vp.set_samples(25);

    background_color = black;
    tracer_ptr = new RayCast(this);

    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(7, 6, 10);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_view_distance(100.0);
    pinhole_ptr->set_zoom(4.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:
    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.8);
    set_ambient_light(ambient_ptr);

    // point light 1:
    PointLight* light_ptr1 = new PointLight();
    light_ptr1->set_location(-2, 8, 7);
    light_ptr1->set_intensity(2.0);
    light_ptr1->set_color(1);
    add_light(light_ptr1);

    // point light 2:
    PointLight* light_ptr2 = new PointLight();
    light_ptr2->set_location(1, 7, 1);
    light_ptr2->set_intensity(1.5);
    light_ptr2->set_color(1);
    add_light(light_ptr2);

    //material 1:
    Phong* phong_ptr1 = new Phong();
    phong_ptr1->set_ka(0.6);
    phong_ptr1->set_kd(0.8);
    phong_ptr1->set_cd(.9, .6, .6);
    phong_ptr1->set_ks(1.0);

    //material 2:
    Phong* phong_ptr2 = new Phong();
    phong_ptr2->set_ka(0.4);
    phong_ptr2->set_kd(0.6);
    phong_ptr2->set_cd(1); // white
    phong_ptr2->set_ks(0.2);

    // triangles:
    Triangle* tri_ptr1 = new Triangle(2, 0, 3, 2, 0, 5, 2, 4, 4);
    tri_ptr1->set_material(phong_ptr1);
    add_object(tri_ptr1);

    Triangle* tri_ptr2 = new Triangle(5, 4, 2, 3, 4, 2, 4, 0, 2);
    tri_ptr2->set_material(phong_ptr1);
    add_object(tri_ptr2);

    Triangle* tri_ptr3 = new Triangle(6, 0, 5, 6, 0, 3, 6, 4, 4);
    tri_ptr3->set_material(phong_ptr1);
    add_object(tri_ptr3);

    Triangle* tri_ptr4 = new Triangle(5, 4, 6, 3, 4, 6, 4, 0, 6);
    tri_ptr4->set_material(phong_ptr1);
    add_object(tri_ptr4);

    //floor plane:
    Plane* plane_ptr1 = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    plane_ptr1->set_material(phong_ptr2);
    add_object(plane_ptr1);

}