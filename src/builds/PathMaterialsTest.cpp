void
World::build() {

	int num_samples = 256;

	//double scale_factor = 16
	double scale_factor = 32;

	vp.set_hres(16 * scale_factor);
	//vp.set_vres(16 * scale_factor);
	vp.set_vres(9 * scale_factor);
	vp.set_samples(num_samples);
	vp.set_max_depth(8);

	background_color = black;

	tracer_ptr = new PathTrace(this);

	Ambient* ambient_ptr = new Ambient();
	ambient_ptr->set_intensity(0.0);
	set_ambient_light(ambient_ptr);

	//camera:
	Pinhole* pinhole_ptr = new Pinhole();
	pinhole_ptr->set_eye(2.5, 2.5, 4.95);
	//pinhole_ptr->set_lookat(2.5, 2.5, 0);
	pinhole_ptr->set_lookat(2.5, .25, 1.8);
	pinhole_ptr->set_view_distance(10.0);
	//pinhole_ptr->set_zoom(1 * scale_factor);
	pinhole_ptr->set_zoom(1.8 * scale_factor);
	pinhole_ptr->compute_uvw();
	camera_ptr = pinhole_ptr;

	Sampler* sampler_ptr = new MultiJittered(num_samples);

	// materials:

	Emissive* emissive_ptr1 = new Emissive;
	emissive_ptr1->set_ls(8.0);
	//emissive_ptr1->set_ce(.77, 0.73, 0.94);
	emissive_ptr1->set_ce(.95, .86, .68);

	Matte* mat = new Matte();
	mat->set_samples(num_samples);
	mat->set_ka(0.25);
	mat->set_kd(1);
	mat->set_cd(1); // white

	Matte* mat_red = new Matte(*mat);
	mat_red->set_cd(.66, 0.17, 0.14);

	Matte* mat_green = new Matte(*mat);
	mat_green->set_cd(0.18, .58, 0.43);

	Phong* p_mat = new Phong;
	p_mat->set_samples(num_samples);
	p_mat->set_exp(64);
	//p_mat->set_cd(.12, .34, .58);
	p_mat->set_cd(1, 1, 1);
	p_mat->set_kd(.65);
	p_mat->set_cs(1, 1, 1);
	p_mat->set_ks(.35);

	Reflective* r_mat = new Reflective;
	r_mat->set_samples(num_samples);
	r_mat->set_exp(64);
	r_mat->set_cd(1, 1, 1);
	r_mat->set_kd(.75);
	r_mat->set_cs(1, 1, 1);
	r_mat->set_ks(.25);
	r_mat->set_cr(1, 1, 1);
	r_mat->set_kr(0);

	// objects:

	Plane* floor = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
	floor->set_material(mat);
	add_object(floor);

	Plane* ceiling = new Plane(Point3D(0, 5, 0), Normal(0, -1, 0));
	ceiling->set_material(mat);
	add_object(ceiling);

	Plane* north = new Plane(Point3D(0, 0, 0), Normal(0, 0, 1));
	north->set_material(mat);
	add_object(north);

	Plane* south = new Plane(Point3D(0, 0, 5), Normal(0, 0, -1));
	south->set_material(mat);
	add_object(south);

	Plane* west = new Plane(Point3D(0, 0, 0), Normal(1, 0, 0));
	west->set_material(mat_red);
	add_object(west);

	Plane* east = new Plane(Point3D(5, 0, 0), Normal(-1, 0, 0));
	east->set_material(mat_green);
	add_object(east);

	double l_l = 1.5;
	RectangleObject* light = new RectangleObject(2.5 - .5 * l_l, 4.95, 2.0 - .5 * l_l, l_l, 0, 0, 0, 0, l_l, 0, -1, 0);
	light->set_material(emissive_ptr1);
	add_object(light);

	
	Box* box = new Box(-.5, 0, -.5, .5, 1, .5);

	Instance* tall_box = new Instance(box);
	tall_box->set_material(mat);
	tall_box->scale(1, 3, 1);
	tall_box->rotate_y(30);
	tall_box->translate(1.5, 0, 1);
	add_object(tall_box);

	Instance* short_box = new Instance(box);
	short_box->set_material(mat);
	short_box->scale(1, 1.5, 1);
	short_box->rotate_y(-30);
	short_box->translate(3.5, 0, 1);
	add_object(short_box);

	/*
	Cylinder* cyl = new Cylinder(-.5, .5, .125);

	Instance* pipe_h = new Instance(cyl);
	pipe_h->set_material(p_mat);
	pipe_h->scale(1, 5, 1);
	pipe_h->rotate_z(90);
	pipe_h->translate(2.5, 4.5, .5);
	add_object(pipe_h);

	Instance* pipe_v = new Instance(cyl);
	pipe_v->set_material(p_mat);
	pipe_v->scale(1, 5, 1);
	pipe_v->translate(4.5, 2.5, 1);
	add_object(pipe_v);
	*/

	double r = .25;
	double gap = .05;
	double start_x = 2.5 - 5 * r - 2.5 * gap;

	for (int i(0); i < 6; i++) {
		
		Reflective* r_mat_i = new Reflective(*r_mat);
		r_mat_i->set_kd(.75 - i * .15);
		r_mat_i->set_ks(.25 - i * .05);
		r_mat_i->set_kr(i * .2);

		Sphere* s = new Sphere(Point3D(start_x + i * (2 * r + gap), r, 1.8), r);
		s->set_material(p_mat);
		add_object(s);
	}


}