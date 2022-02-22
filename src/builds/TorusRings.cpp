void
World::build(void) {

    vp.set_hres(1920);
    vp.set_vres(1080);
    vp.set_samples(49);
    vp.set_max_depth(32);

    tracer_ptr = new Whitted(this);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(17, 6, 17);
    camera_ptr->set_lookat(0, 0, 0);
    camera_ptr->set_view_distance(240);
    camera_ptr->set_zoom(1);
    camera_ptr->compute_uvw();
    set_camera(camera_ptr);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.2);
    set_ambient_light(ambient_ptr);

    PointLight* light_2 = new PointLight();
    light_2->set_location(24, 18, -24);
    light_2->set_intensity(1.2);
    add_light(light_2);

    PointLight* light_4 = new PointLight();
    light_4->set_location(-24, 18, 24);
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

    Reflective* mat_b = new Reflective(*mat_1);
    mat_b->set_kr(0.4);

    //inner ring:
    double floor = 2.0;
    double height = 3.0;
    int ring_elements = 24;

    double ring_radius = (double)ring_elements * 0.5;
    double t_b = ring_radius / ring_elements;
    double t_a = PI * ring_radius / ring_elements + t_b;

    for (int i = 0; i < ring_elements; i++) {

        double wavelength = 380.0 + i * (340.0 / ring_elements);
        RGBColor col = RGBColor::convert_wave_length_nm_to_rgb(wavelength);

        Reflective* mat = new Reflective(*mat_1);
        mat->set_cd(col);
        mat->set_cs(col);

        Instance* torus = new Instance(new Torus(t_a, t_b));
        torus->set_material(mat);

        if(i % 2 == 0)
            torus->rotate_z(90);

        torus->translate(ring_radius, floor + t_a + t_b, 0);
        torus->rotate_y(i * 360 / ring_elements);

        add_object(torus);
    }

    Instance* disk_1 = new Instance(new Disk(0, floor, 0, ring_radius + t_a + 2.0, 0, 1, 0));
    disk_1->set_material(mat_b);
    add_object(disk_1);

    Instance* rim_torus_1 = new Instance(new Torus(ring_radius + t_a + 2.0, height));
    rim_torus_1->set_material(mat_b);
    rim_torus_1->translate(0, floor - height, 0);
    add_object(rim_torus_1);



    //outer ring:
    floor = floor - height;
    height = 4.0;
    ring_elements = 48;

    ring_radius = (double)ring_elements * 0.5;
    t_b = ring_radius / ring_elements;
    t_a = PI * ring_radius / ring_elements + t_b;

    for (int i = 0; i < ring_elements; i++) {

        double wavelength = 380.0 + i * (340.0 / ring_elements);
        RGBColor col = RGBColor::convert_wave_length_nm_to_rgb(wavelength);

        Reflective* mat = new Reflective(*mat_1);
        mat->set_cd(col);
        mat->set_cs(col);

        Instance* torus = new Instance(new Torus(t_a, t_b));
        torus->set_material(mat);

        if (i % 2 == 0)
            torus->rotate_z(90);

        torus->translate(-ring_radius, floor + t_a + t_b, 0);
        torus->rotate_y(i * 360 / ring_elements);

        add_object(torus);
    }

    Instance* disk_2 = new Instance(new Disk(0, floor, 0, ring_radius + t_a + 3.0, 0, 1, 0));
    disk_2->set_material(mat_b);
    add_object(disk_2);

    Instance* rim_torus_2 = new Instance(new Torus(ring_radius + t_a + 3.0, height));
    rim_torus_2->set_material(mat_b);
    rim_torus_2->translate(0, floor - height, 0);
    add_object(rim_torus_2);

    Phong* mat_p = new Phong();
    mat_p->set_ka(0.4);
    mat_p->set_kd(0.8);
    mat_p->set_cd(0.75);
    mat_p->set_ks(0.6);
    mat_p->set_cs(0.75);
    mat_p->set_exp(100);

    Plane* plane = new Plane(Point3D(0, floor - height, 0), Normal(0, 1, 0));
    plane->set_material(mat_p);
    add_object(plane);
}