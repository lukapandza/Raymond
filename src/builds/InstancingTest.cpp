void
World::build(void) {

    vp.set_hres(400);
    vp.set_vres(400);
    vp.set_samples(16);
    tracer_ptr = new RayCast(this);

    Pinhole* camera_ptr = new Pinhole;
    camera_ptr->set_eye(100, 0, 100);
    camera_ptr->set_lookat(0, 1, 0);
    camera_ptr->set_view_distance(8000);
    camera_ptr->compute_uvw();
    set_camera(camera_ptr);

    Ambient* ambient_ptr = new Ambient();
    ambient_ptr->set_intensity(0.1);
    set_ambient_light(ambient_ptr);

    PointLight* light_ptr = new PointLight();
    light_ptr->set_location(50, 50, 1);
    light_ptr->set_intensity(3.0);
    add_light(light_ptr);

    Phong* phong_ptr = new Phong;
    phong_ptr->set_cd(0.75);
    phong_ptr->set_ka(0.25);
    phong_ptr->set_kd(0.8);
    phong_ptr->set_ks(0.15);
    phong_ptr->set_exp(50);

    Instance* ellipsoid_ptr = new Instance(new Sphere);
    ellipsoid_ptr->set_material(phong_ptr);
    ellipsoid_ptr->scale(2, 3, 1);
    ellipsoid_ptr->rotate_x(-45);
    ellipsoid_ptr->translate(0, 1, 0);
    add_object(ellipsoid_ptr);

    Instance* torus_ptr = new Instance(new Torus);
    torus_ptr->set_material(phong_ptr);
    torus_ptr->scale(1.5, 0.2, 1.5);
    torus_ptr->rotate_z(90);
    torus_ptr->rotate_x(45);
    torus_ptr->translate(0, 1, 0);
    add_object(torus_ptr);

}