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
    pinhole_ptr->set_eye(0, 6, 5);
    pinhole_ptr->set_lookat(0, 0.5, 0);
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
    light_ptr1->set_location(0, 8, -2);
    light_ptr1->set_intensity(4.0);
    light_ptr1->set_color(1, 0, 0);
    add_light(light_ptr1);

    // point light 2:
    PointLight* light_ptr2 = new PointLight();
    light_ptr2->set_location(-1.732, 8, 1);
    light_ptr2->set_intensity(4.0);
    light_ptr2->set_color(0, 1, 0);
    add_light(light_ptr2);

    // point light 3:
    PointLight* light_ptr3 = new PointLight();
    light_ptr3->set_location(1.732, 8, 1);
    light_ptr3->set_intensity(4.0);
    light_ptr3->set_color(0, 0, 1);
    add_light(light_ptr3);

    //material 1:
    Phong* phong_ptr1 = new Phong();
    phong_ptr1->set_ka(0.0);
    phong_ptr1->set_kd(0.4);
    phong_ptr1->set_cd(1); // white
    phong_ptr1->set_ks(0.0);

    //sphere 1:
    Sphere* sphere_ptr1 = new Sphere(Point3D(0, 3, 0), 1);
    sphere_ptr1->set_material(phong_ptr1);
    add_object(sphere_ptr1);

    //floor plane:
    Plane* plane_ptr1 = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    plane_ptr1->set_material(phong_ptr1);
    add_object(plane_ptr1);

}