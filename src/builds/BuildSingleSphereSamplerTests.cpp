void 												
World::build(void) {

    int num_samples = 256;

   	vp.set_hres(128);
	vp.set_vres(128);
	vp.set_pixel_size(0.0625);
	vp.set_gamma(1.0);
    vp.set_sampler(new Hammersley(num_samples));
	
	background_color = white;
	tracer_ptr = new SingleSphere(this); 
	
	sphere.set_center(10.0, -38.0, 0.0);
	sphere.set_radius(40);
}
