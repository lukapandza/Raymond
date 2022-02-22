void
World::build(void) {

    vp.set_hres(7680);
    vp.set_vres(4320);
    vp.set_samples(1);
    vp.set_max_depth(12);

    tracer_ptr = new Whitted(this);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(-1, -1, -1);
    camera_ptr->set_lookat(1, 1, 1);
    camera_ptr->set_view_distance(360);
    camera_ptr->set_zoom(32);
    camera_ptr->compute_uvw();
    set_camera(camera_ptr);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(1);
    set_ambient_light(ambient_ptr);

    //materials:
    Reflective* mat_1 = new Reflective;
    mat_1->set_ka(1);
    mat_1->set_kd(0);
    mat_1->set_cd(0.0, 0.0, 0.0);
    mat_1->set_ks(0);
    mat_1->set_exp(100);
    mat_1->set_kr(1);
    mat_1->set_cr(white);

    Reflective* mat_2 = new Reflective(*mat_1);
    mat_2->set_cd(0.05, 0.0, 0.0);

    Reflective* mat_3 = new Reflective(*mat_1);
    mat_3->set_cd(0.0, 0.05, 0.0);

    Reflective* mat_4 = new Reflective(*mat_1);
    mat_4->set_cd(0.0, 0.0, 0.05);

    //spheres:
    Point3D p1(1, 1, 1);
    Point3D p2(-1, -1, 1);
    Point3D p3(-1, 1, -1);
    Point3D p4(1, -1, -1);

    double radius = p1.distance(p2) * 0.5;

    Instance* sphere_1 = new Instance(new Sphere(p1, radius));
    sphere_1->set_material(mat_1);
    add_object(sphere_1);

    Instance* sphere_2 = new Instance(new Sphere(p2, radius));
    sphere_2->set_material(mat_2);
    add_object(sphere_2);

    Instance* sphere_3 = new Instance(new Sphere(p3, radius));
    sphere_3->set_material(mat_3);
    add_object(sphere_3);

    Instance* sphere_4 = new Instance(new Sphere(p4, radius));
    sphere_4->set_material(mat_4);
    add_object(sphere_4);
}