void
World::build(void) {

    vp.set_hres(256);
    vp.set_vres(256);
    vp.set_pixel_size(1);
    vp.set_samples(16);

    background_color = black;
    tracer_ptr = new RayCast(this);

    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(0, 45, 250);
    pinhole_ptr->set_lookat(0, 10, 0);
    pinhole_ptr->set_view_distance(200.0);
    pinhole_ptr->set_zoom(3.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:
    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.2);
    set_ambient_light(ambient_ptr);

    /*
    PointLight* light_ptr1 = new PointLight();
    light_ptr1->set_location(100, 50, 150);
    light_ptr1->set_intensity(3.0);
    light_ptr1->set_da_power(1.0);
    add_light(light_ptr1);
    */

    // point light:
    PointLight* light_ptr2 = new PointLight();
    light_ptr2->set_location(-30, 45, 40);
    light_ptr2->set_intensity(5.0);
    light_ptr2->set_da_power(1.1);
    add_light(light_ptr2);
    

    //sphere 1:
    Matte* matte_ptr1 = new Matte();
    matte_ptr1->set_ka(0.85);
    matte_ptr1->set_kd(0.65);
    matte_ptr1->set_cd(0.8, 0.8, 0.4); // yellow
    Sphere* sphere_ptr1 = new Sphere(Point3D(10, 13, 0), 13);
    sphere_ptr1->set_material(matte_ptr1);
    add_object(sphere_ptr1);


    //sphere 2:
    Matte* matte_ptr2 = new Matte();
    matte_ptr2->set_ka(0.75);
    matte_ptr2->set_kd(0.75);
    matte_ptr2->set_cd(0.2, 0.8, 0.4);
    Sphere* sphere_ptr2 = new Sphere(Point3D(-10, 17, -36), 17);
    sphere_ptr2->set_material(matte_ptr2);
    add_object(sphere_ptr2);

    //floor plane:
    Matte* matte_ptr3 = new Matte();
    matte_ptr3->set_ka(0.65);
    matte_ptr3->set_kd(0.45);
    matte_ptr3->set_cd(0.8, 0.8, 0.8);
    Plane* plane_ptr1 = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    plane_ptr1->set_material(matte_ptr3);
    add_object(plane_ptr1);  
}