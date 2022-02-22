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
    pinhole_ptr->set_zoom(8.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:
    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.8);
    set_ambient_light(ambient_ptr);

    // point light 1:
    PointLight* light_ptr1 = new PointLight();
    light_ptr1->set_location(-6, 8, 7);
    light_ptr1->set_intensity(0.7);
    light_ptr1->set_color(1);
    add_light(light_ptr1);

    // point light 2:
    PointLight* light_ptr2 = new PointLight();
    light_ptr2->set_location(4, 6, 1);
    light_ptr2->set_intensity(0.8);
    light_ptr2->set_color(1);
    add_light(light_ptr2);

    //material 1:
    Phong* phong_ptr1 = new Phong();
    phong_ptr1->set_ka(0.6);
    phong_ptr1->set_kd(0.8);
    phong_ptr1->set_cd(.9, .6, .6);
    phong_ptr1->set_ks(0.4);

    //material 2:
    Phong* phong_ptr2 = new Phong();
    phong_ptr2->set_ka(0.4);
    phong_ptr2->set_kd(0.6);
    phong_ptr2->set_cd(1); // white
    phong_ptr2->set_ks(0.2);

    // triangles:
    Torus* torus_ptr1 = new Torus(2, 0.5);
    torus_ptr1->set_material(phong_ptr1);
    add_object(torus_ptr1);

    //floor plane:
    Plane* plane_ptr1 = new Plane(Point3D(0, -1.5, 0), Normal(0, 1, 0));
    plane_ptr1->set_material(phong_ptr2);
    add_object(plane_ptr1);
}