void
World::build(void) {

    int num_samples = 36;

    vp.set_hres(480);
    vp.set_vres(270);
    vp.set_samples(num_samples);
    vp.set_max_depth(12);

    tracer_ptr = new AreaLighting(this);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(24, 21, 24);
    camera_ptr->set_lookat(0, -4, 0);
    camera_ptr->set_view_distance(240);
    camera_ptr->set_zoom(0.5);
    camera_ptr->compute_uvw();
    set_camera(camera_ptr);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.0);
    set_ambient_light(ambient_ptr);

    MultiJittered* sampler_ptr = new MultiJittered(num_samples);

    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(8192.0);
    emissive_ptr1->set_ce(1);

    Sphere* light_sphere = new Sphere(Point3D(0, 12, 0), 4.0);
    //Rect* light_sphere = new Rect(-1, 9, -1, 2, 0, 0, 0, 0, 2, 0, -1, 0);
    light_sphere->set_material(emissive_ptr1);
    light_sphere->set_sampler(sampler_ptr);
    add_object(light_sphere);

    AreaLight* area_light_ptr1 = new AreaLight;
    area_light_ptr1->set_object(light_sphere);
    area_light_ptr1->set_shadows(true);
    add_light(area_light_ptr1);

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

    Phong* mat_1_p = new Phong;
    mat_1_p->set_ka(0.4);
    mat_1_p->set_kd(0.9);
    mat_1_p->set_cd(0.1);
    mat_1_p->set_ks(0.6);
    mat_1_p->set_cs(0.1);
    mat_1_p->set_exp(100);

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

        Phong* mat = new Phong(*mat_1_p);
        mat->set_cd(col);
        mat->set_cs(col);

        Instance* torus = new Instance(new Torus(t_a, t_b));
        torus->set_material(mat);

        if (i % 2 == 0)
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

        Phong* mat = new Phong(*mat_1_p);
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