void
World::build() 
{
    int num_samples = 36;
    //int scale_factor = 64;
    int scale_factor = 240; // 4K resolution

    vp.set_hres(16 * scale_factor);
    vp.set_vres(9 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(64);

    tracer_ptr = new Whitted(this);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(0, 4, 0);
    camera_ptr->set_lookat(0, -1, 0);
    camera_ptr->set_view_distance(2.99);
    camera_ptr->set_zoom(12 * scale_factor);
    camera_ptr->compute_uvw();
    set_camera(camera_ptr);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(1);
    set_ambient_light(ambient_ptr);

    //materials:
    Reflective* mat_1 = new Reflective;
    mat_1->set_samples(num_samples);
    mat_1->set_ka(.05);
    mat_1->set_kd(0);
    mat_1->set_cd(0.0, 0.0, 0.0);
    mat_1->set_ks(0);
    mat_1->set_exp(100);
    mat_1->set_kr(1);
    mat_1->set_cr(white);

    Reflective* mat_r = new Reflective(*mat_1);
    mat_r->set_cd(.66, .17, .14);

    Reflective* mat_g = new Reflective(*mat_1);
    mat_g->set_cd(.18, .58, .43);

    Reflective* mat_b = new Reflective(*mat_1);
    mat_b->set_cd(.12, .36, .64);

    //spheres:
    Point3D p1(-1, 0, -1);
    Point3D p2(1, 0, 1);
    Point3D p3(1, 0, -1);
    Point3D p4(-1, 0, 1);
    Point3D p5(0, -sqrt(3.0), 0);

    Sphere* s1 = new Sphere(p1, 1.0);
    s1->set_material(mat_r);
    add_object(s1);

    Sphere* s2 = new Sphere(p2, 1.0);
    s2->set_material(mat_r);
    add_object(s2);

    Sphere* s3 = new Sphere(p3, 1.0);
    s3->set_material(mat_1);
    add_object(s3);

    Sphere* s4 = new Sphere(p4, 1.0);
    s4->set_material(mat_1);
    add_object(s4);

    Sphere* s5 = new Sphere(p5, 1.0);
    s5->set_material(mat_1);
    add_object(s5);

    double small_radius = .18;
    double h = -sqrt(3.0) + 1.0 + small_radius;

    for (int i(0); i < 10; i++) {

        Sphere* s = new Sphere(Point3D(0, h, 0), small_radius);
        s->set_material(mat_1);
        add_object(s);
        h += small_radius;
        small_radius *= .5;
        h += small_radius;
    }
}