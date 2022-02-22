void
World::build(void) {

    int num_samples = 256;

    vp.set_hres(400);
    vp.set_vres(400);
    vp.set_samples(num_samples);

    tracer_ptr = new RayCast(this);

    MultiJittered* sampler_ptr = new MultiJittered(num_samples);

    AmbientOccluder* occluder_ptr = new AmbientOccluder;
    occluder_ptr->set_intensity(1.0);
    occluder_ptr->set_color(white);
    occluder_ptr->set_min(0.0);
    occluder_ptr->set_sampler(sampler_ptr);
    set_ambient_light(occluder_ptr);

    Pinhole* pinhole_ptr = new Pinhole;
    pinhole_ptr->set_eye(25, 20, 45);
    pinhole_ptr->set_lookat(0, 1, 0);
    pinhole_ptr->set_view_distance(5000);
    pinhole_ptr->compute_uvw();
    camera_ptr = pinhole_ptr;

    Matte* matte_ptr1 = new Matte;
    matte_ptr1->set_ka(0.75);
    matte_ptr1->set_kd(0);
    matte_ptr1->set_cd(1, 1, 0); // yellow

    Sphere* sphere_ptr1 = new Sphere (Point3D(0, 1, 0), 1);
    sphere_ptr1->set_material(matte_ptr1);
    add_object(sphere_ptr1);

    Matte* matte_ptr2 = new Matte;
    matte_ptr2->set_ka(0.75);
    matte_ptr2->set_kd(0);
    matte_ptr2->set_cd(1); // white

    Plane* plane_ptr1 = new Plane(Point3D(0), Normal(0, 1, 0));
    plane_ptr1->set_material(matte_ptr2);
    add_object(plane_ptr1);
}