void
World::build()
{
    int num_samples = 25;
    //int scale_factor = 32;
    int scale_factor = 240; // 4K resolution

    vp.set_hres(16 * scale_factor);
    vp.set_vres(16 * scale_factor);
    vp.set_samples(num_samples);
    vp.set_max_depth(64);

    tracer_ptr = new Whitted(this);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(0, 10, 0);
    camera_ptr->set_lookat(0, 0, 0);
    camera_ptr->set_view_distance(5);
    camera_ptr->set_zoom(1 * scale_factor);
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

    Reflective* mat_2 = new Reflective(*mat_1);
    mat_2->set_cd(1, 1, 1);

    double radius = 1.0;

    // bounding planes:
    /*
    Cylinder* cyl = new Cylinder(-12, 12, 3 * radius);
    cyl->set_material(mat_1);
    add_object(cyl);
    */
    Plane* plane = new Plane(Point3D(0, 0, 0), Normal(-1, 0, 0));
    plane->set_material(mat_1);

    for (int i(0); i < 6; i++) {
    
        Instance* p_ins = new Instance(plane);
        p_ins->rotate_y(30);
        p_ins->translate(3 * radius, 0, 0);
        p_ins->rotate_y(i * 60);
        add_object(p_ins);
    }
    
    
    Plane* m_p_b = new Plane(Point3D(0, 12, 0), Normal(0, -1, 0));
    m_p_b->set_material(mat_1);
    add_object(m_p_b);
    
    Plane* m_p_f = new Plane(Point3D(0, -12, 0), Normal(0, 1, 0));
    m_p_f->set_material(mat_1);
    add_object(m_p_f);
    
    
    //spheres:

    Sphere* s = new Sphere(Point3D(0, 0, 0), radius);
    s->set_material(mat_1);
    add_object(s);

    // 1
    for (int i(0); i < 6; i++) {
        
        Instance* s_ins = new Instance(s);
        s_ins->translate(2 * radius, 0, 0);
        s_ins->rotate_y(i * 60);
        s_ins->set_material(i % 3 == 0 ? mat_r : (i % 3 == 1 ? mat_b : mat_g));
        add_object(s_ins);
    }

    // 2

    // 3

    // 4

    // 5
    
}