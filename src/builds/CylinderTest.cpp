void
World::build() {

    int num_samples = 2500;

    vp.set_hres(512);
    vp.set_vres(288);
    vp.set_samples(num_samples);
    vp.set_max_depth(6);

    background_color = black;

    //tracer_ptr = new RayCast(this);
    //tracer_ptr = new AreaLighting(this);
    //tracer_ptr = new PathTrace(this);
    tracer_ptr = new GlobalTrace(this);


    //camera:
    Pinhole* pinhole_ptr = new Pinhole();
    pinhole_ptr->set_eye(0, 12.5, 7);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_view_distance(2.0);
    pinhole_ptr->set_zoom(256.0);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    // ambient:

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.4);
    set_ambient_light(ambient_ptr);

    //light: 
    
    Emissive* emissive_ptr1 = new Emissive;
    emissive_ptr1->set_ls(32);
    emissive_ptr1->set_ce(1.0, 0.83, 0.6);
    

    Sampler* sampler_ptr = new MultiJittered(num_samples);

    /*
    // point light 1:
    PointLight* light_ptr1 = new PointLight();
    light_ptr1->set_location(-2, 4, 2);
    light_ptr1->set_intensity(4.0);
    light_ptr1->set_color(1, 1, 1);
    add_light(light_ptr1);

    // point light 1:
    PointLight* light_ptr2 = new PointLight();
    light_ptr2->set_location(-6, 4, 2);
    light_ptr2->set_intensity(4.0);
    light_ptr2->set_color(1, 1, 1);
    add_light(light_ptr2);
    */

    Sphere* glowglobe = new Sphere(Point3D(-2, 4, 2), .5);
    glowglobe->set_material(emissive_ptr1);
    glowglobe->set_sampler(sampler_ptr);
    add_object(glowglobe);

    
    AreaLight* area_light_ptr1 = new AreaLight;
    area_light_ptr1->set_object(glowglobe);
    area_light_ptr1->set_shadows(true);
    add_light(area_light_ptr1);
    

    Matte* mat = new Matte();
    mat->set_samples(num_samples);
    mat->set_ka(0.25);
    mat->set_kd(.95);
    mat->set_cd(1); // white

    Phong* p_mat = new Phong();
    p_mat->set_samples(num_samples);
    p_mat->set_ka(.25);
    p_mat->set_kd(.4);
    p_mat->set_cd(.47, .54, .86); // blue
    p_mat->set_ks(.6);
    p_mat->set_exp(16);

    //walls:
    Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
    floor->set_material(mat);
    add_object(floor);

    Cylinder* cyl = new Cylinder;
    cyl->set_material(p_mat);
    add_object(cyl);

    Instance* cyl2 = new Instance(cyl);
    cyl2->scale(3, .5, 1);
    cyl2->translate(3.5, 0, 0);
    add_object(cyl2);

    Instance* cyl3 = new Instance(cyl);
    cyl3->scale(3, .5, 1);
    cyl3->translate(3.5, 0, 0);
    cyl3->rotate_y(90);
    add_object(cyl3);

    Instance* cyl4 = new Instance(cyl);
    cyl4->scale(3, .5, 1);
    cyl4->translate(3.5, 0, 0);
    cyl4->rotate_y(180);
    add_object(cyl4);

    Instance* cyl5 = new Instance(cyl);
    cyl5->scale(3, .5, 1);
    cyl5->translate(3.5, 0, 0);
    cyl5->rotate_y(270);
    add_object(cyl5);
}