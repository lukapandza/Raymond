void
World::build(void) {

    vp.set_hres(1920);
    vp.set_vres(1080);
    vp.set_samples(36);
    vp.set_max_depth(64);

    tracer_ptr = new Whitted(this);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(18, 9, 18);
    camera_ptr->set_lookat(0, 0, 0);
    camera_ptr->set_view_distance(240);
    camera_ptr->set_zoom(6);
    camera_ptr->compute_uvw();
    set_camera(camera_ptr);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.2);
    set_ambient_light(ambient_ptr);
    /*
    PointLight* light_1 = new PointLight();
    light_1->set_location(12, 9, 12);
    light_1->set_intensity(0.9);
    add_light(light_1);
    */
    PointLight* light_2 = new PointLight();
    light_2->set_location(12, 15, -12);
    light_2->set_intensity(1.2);
    add_light(light_2);
    /*
    PointLight* light_3 = new PointLight();
    light_3->set_location(-12, 9, -12);
    light_3->set_intensity(0.9);
    add_light(light_3);
    */
    PointLight* light_4 = new PointLight();
    light_4->set_location(-12, 15, 12);
    light_4->set_intensity(1.2);
    add_light(light_4);

    //materials:
    Reflective* mat_1 = new Reflective;
    mat_1->set_ka(0.4);
    mat_1->set_kd(0.8);
    mat_1->set_cd(0.1);
    mat_1->set_ks(0.6);
    mat_1->set_cs(0.1);
    mat_1->set_exp(100);
    mat_1->set_kr(1);
    mat_1->set_cr(white);

    Reflective* mat_2 = new Reflective(*mat_1);
    mat_2->set_cd(0.5, 0.0, 0.5);
    mat_2->set_cs(0.5, 0.0, 0.5);

    Reflective* mat_3 = new Reflective(*mat_1);
    mat_3->set_cd(0.0, 0.0, 0.5);
    mat_3->set_cs(0.0, 0.0, 0.5);

    Reflective* mat_4 = new Reflective(*mat_1);
    mat_4->set_cd(0.0, 0.5, 0.5);
    mat_4->set_cs(0.0, 0.5, 0.5);

    Reflective* mat_5 = new Reflective(*mat_1);
    mat_5->set_cd(0.0, 0.5, 0.0);
    mat_5->set_cs(0.0, 0.5, 0.0);

    Reflective* mat_6 = new Reflective(*mat_1);
    mat_6->set_cd(0.5, 0.5, 0.0);
    mat_6->set_cs(0.5, 0.5, 0.0);

    Reflective* mat_7 = new Reflective(*mat_1);
    mat_7->set_cd(0.5, 0.0, 0.0);
    mat_7->set_cs(0.5, 0.0, 0.0);

    Reflective* mat_8 = new Reflective(*mat_1);
    mat_8->set_cd(1, 1, 1);
    mat_8->set_cs(1, 1, 1);

    Phong* mat_9 = new Phong();
    mat_9->set_ka(0.1);
    mat_9->set_kd(0.8);
    mat_9->set_cd(0.75);
    mat_9->set_ks(0.8);
    mat_9->set_cs(0.75);
    mat_9->set_exp(100);


    //spheres:
    Instance* torus_1 = new Instance(new Torus(3, 0.5));
    torus_1->set_material(mat_1);
    add_object(torus_1);

    Instance* torus_2 = new Instance(new Torus(3, 0.5));
    torus_2->set_material(mat_2);
    torus_2->translate(4, 0, 0);
    torus_2->rotate_x(90);
    torus_2->rotate_y(2 * 60);
    add_object(torus_2);

    Instance* torus_3 = new Instance(new Torus(3, 0.5));
    torus_3->set_material(mat_3);
    torus_3->translate(4, 0, 0);
    torus_3->rotate_x(90);
    torus_3->rotate_y(3 * 60);
    add_object(torus_3);

    Instance* torus_4 = new Instance(new Torus(3, 0.5));
    torus_4->set_material(mat_4);
    torus_4->translate(4, 0, 0);
    torus_4->rotate_x(90);
    torus_4->rotate_y(4 * 60);
    add_object(torus_4);

    Instance* torus_5 = new Instance(new Torus(3, 0.5));
    torus_5->set_material(mat_5);
    torus_5->translate(4, 0, 0);
    torus_5->rotate_x(90);
    torus_5->rotate_y(5 * 60);
    add_object(torus_5);

    Instance* torus_6 = new Instance(new Torus(3, 0.5));
    torus_6->set_material(mat_6);
    torus_6->translate(4, 0, 0);
    torus_6->rotate_x(90);
    torus_6->rotate_y(6 * 60);
    add_object(torus_6);

    Instance* torus_7 = new Instance(new Torus(3, 0.5));
    torus_7->set_material(mat_7);
    torus_7->translate(4, 0, 0);
    torus_7->rotate_x(90);
    torus_7->rotate_y(7 * 60);
    add_object(torus_7);

    Instance* sphere = new Instance(new Sphere(Point3D(0, 0, 0), 0.5));
    sphere->set_material(mat_8);
    add_object(sphere);

    Instance* floor = new Instance(new Plane(Point3D(0, -3.5, 0), Normal(0, 1, 0)));
    floor->set_material(mat_9);
    add_object(floor);
}