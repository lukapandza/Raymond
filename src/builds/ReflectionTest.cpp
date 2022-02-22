void
World::build(void) {

    vp.set_hres(800);
    vp.set_vres(600);
    vp.set_samples(36);
    vp.set_max_depth(24);

    tracer_ptr = new Whitted(this);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(2.2, 1.8, -2.2);
    camera_ptr->set_lookat(0, 1.0, 0);
    camera_ptr->set_view_distance(400);
    camera_ptr->set_zoom(1);
    camera_ptr->compute_uvw();
    set_camera(camera_ptr);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.1);
    set_ambient_light(ambient_ptr);

    // lights:
    PointLight* light_1 = new PointLight();
    light_1->set_location(-2.5, 2.9, 0);
    light_1->set_intensity(1.0);
    add_light(light_1);

    PointLight* light_2 = new PointLight();
    light_2->set_location(0, 2.9, 2.5);
    light_2->set_intensity(1.0);
    add_light(light_2);

    PointLight* light_3 = new PointLight();
    light_3->set_location(2.5, 2.9, 0);
    light_3->set_intensity(1.0);
    add_light(light_3);

    PointLight* light_4 = new PointLight();
    light_4->set_location(0, 2.9, -2.5);
    light_4->set_intensity(1.0);
    add_light(light_4);

    //materials:
    Phong* wall_1 = new Phong;
    wall_1->set_ka(1);
    wall_1->set_kd(0.6);
    wall_1->set_ks(0.6);
    wall_1->set_exp(50);
    wall_1->set_cd(0.2, 0.7, 0.7);

    Phong* wall_2 = new Phong;
    wall_2->set_ka(1);
    wall_2->set_kd(0.6);
    wall_2->set_ks(0.6);
    wall_2->set_exp(50);
    wall_2->set_cd(0.8, 0.4, 0.0);

    Phong* wall_3 = new Phong;
    wall_3->set_ka(1);
    wall_3->set_kd(0.6);
    wall_3->set_ks(0.6);
    wall_3->set_exp(50);
    wall_3->set_cd(0.4);

    Reflective* reflective_ptr1 = new Reflective;
    reflective_ptr1->set_ka(0.2);
    reflective_ptr1->set_kd(0.5);
    reflective_ptr1->set_cd(0.6, 0.2, 0.2);
    reflective_ptr1->set_ks(0.15);
    reflective_ptr1->set_exp(100);
    reflective_ptr1->set_kr(0.45);
    reflective_ptr1->set_cr(white);

    Reflective* reflective_ptr2 = new Reflective;
    reflective_ptr2->set_ka(0);
    reflective_ptr2->set_kd(0);
    reflective_ptr2->set_ks(0);
    reflective_ptr2->set_kr(1);
    reflective_ptr2->set_cr(0.9, 1, 0.9);

    //walls:
    Point3D p_bottom(0, -1.5, 0);
    Normal n_bottom(0, 1, 0);
    Instance* wall_bottom = new Instance(new Plane(p_bottom, n_bottom));
    wall_bottom->set_material(wall_3);
    add_object(wall_bottom);

    Point3D p_top(0, 3.5, 0);
    Normal n_top(0, -1, 0);
    Instance* wall_top = new Instance(new Plane(p_top, n_top));
    wall_top->set_material(wall_3);
    add_object(wall_top);

    Point3D p_west(-3, 0, 0);
    Normal n_west(1, 0, 0);
    Instance* wall_west = new Instance(new Plane(p_west, n_west));
    wall_west->set_material(wall_2);
    add_object(wall_west);

    Point3D p_north(0, 0, 3);
    Normal n_north(0, 0, -1);
    Instance* wall_north = new Instance(new Plane(p_north, n_north));
    wall_north->set_material(wall_1);
    add_object(wall_north);

    Point3D p_east(3, 0, 0);
    Normal n_east(-1, 0, 0);
    Instance* wall_east = new Instance(new Plane(p_east, n_east));
    wall_east->set_material(wall_2);
    add_object(wall_east);

    Point3D p_south(0, 0, -3);
    Normal n_south(0, 0, 1);
    Instance* wall_south = new Instance(new Plane(p_south, n_south));
    wall_south->set_material(wall_1);
    add_object(wall_south);

    //mirrors:
    Instance* mirror_bottom = new Instance(new Rect(-2, 0, -2, 4, 0, 0, 0, 0, 4, 0, 1, 0));
    mirror_bottom->set_material(reflective_ptr2);
    add_object(mirror_bottom);

    Instance* mirror_west = new Instance(new Rect(-2.5, 0, -2, 0, 0, 4, 0, 3, 0, 1, 0, 0));
    mirror_west->set_material(reflective_ptr2);
    add_object(mirror_west);

    Instance* mirror_north = new Instance(new Rect(-2, 0, 2.5, 4, 0, 0, 0, 3, 0, 0, 0, -1));
    mirror_north->set_material(reflective_ptr2);
    add_object(mirror_north);

    Instance* mirror_east = new Instance(new Rect(2.5, 0, 2, 0, 0, -4, 0, 3, 0, -1, 0, 0));
    mirror_east->set_material(reflective_ptr2);
    add_object(mirror_east);

    Instance* mirror_south = new Instance(new Rect(2, 0, -2.5, -4, 0, 0, 0, 3, 0, 0, 0, 1));
    mirror_south->set_material(reflective_ptr2);
    add_object(mirror_south);

    Instance* sphere = new Instance(new Sphere(Point3D(0, 1, 0), 1.0));
    sphere->set_material(reflective_ptr1);
    add_object(sphere);
}