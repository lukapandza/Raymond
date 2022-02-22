void
World::build(void) {

    vp.set_hres(700);
    vp.set_vres(350);
    vp.set_pixel_size(1);
    vp.set_samples(16);

    background_color = black;
    tracer_ptr = new RayCast(this);

    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(0, 35, 250);
    pinhole_ptr->set_lookat(0, 15, 0);
    pinhole_ptr->set_view_distance(200.0);
    pinhole_ptr->set_zoom(8.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:
    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.2);
    set_ambient_light(ambient_ptr);

    // point light 1:
    /*
    PointLight* light_ptr1 = new PointLight();
    light_ptr1->set_location(50, 50, 0.0);
    light_ptr1->set_intensity(2.0);
    light_ptr1->set_da_power(1.05);
    add_light(light_ptr1);
    */


    // point light 2:
    PointLight* light_ptr2 = new PointLight();
    light_ptr2->set_location(-30, 45, 20);
    light_ptr2->set_intensity(4.0);
    //light_ptr2->set_da_power(1.05);
    add_light(light_ptr2);
    
    //material 1:
    Phong* phong_ptr1 = new Phong();
    phong_ptr1->set_ka(0.8);
    phong_ptr1->set_kd(0.8);
    phong_ptr1->set_cd(0.8, 0.8, 0.4); // yellow
    phong_ptr1->set_ks(0.1);

    //material 2:
    Phong* phong_ptr2 = new Phong();
    phong_ptr2->set_ka(0.8);
    phong_ptr2->set_kd(0.8);
    phong_ptr2->set_cd(0.2, 0.8, 0.4); // green
    phong_ptr2->set_exp(512.0);

    //material 3:
    Phong* phong_ptr3 = new Phong();
    phong_ptr3->set_ka(0.95);
    phong_ptr3->set_kd(0.45);
    phong_ptr3->set_cd(0.8); // gray
    phong_ptr3->set_ks(0.2);


    //sphere 1:
    Sphere* sphere_ptr1 = new Sphere(Point3D(10, 13, 0), 13);
    sphere_ptr1->set_material(phong_ptr1);
    add_object(sphere_ptr1);


    //sphere 2:
    Sphere* sphere_ptr2 = new Sphere(Point3D(-10, 17, -36), 17);
    sphere_ptr2->set_material(phong_ptr2);
    add_object(sphere_ptr2);

    //floor plane:
    Plane* plane_ptr1 = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    plane_ptr1->set_material(phong_ptr3);
    add_object(plane_ptr1);  
}