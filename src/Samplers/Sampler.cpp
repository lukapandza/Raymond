#include "../Utilities/Constants.h"
#include "Sampler.h"
#include <algorithm>   // for random_shuffle in Sampler::setup_shuffled_indices

//default constructor:
Sampler::Sampler(void)
	: num_samples(1),
	num_sets(23),
	count(0),
	jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

//constructor 1:
Sampler::Sampler(const int num)
	: num_samples(num),
	num_sets(23),
	count(0),
	jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

//constructor 2:
Sampler::Sampler(const int num, const int num_sets)
	: num_samples(num),
	num_sets(num_sets),
	count(0),
	jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

//copy constructor:
Sampler::Sampler(const Sampler& s)
	: num_samples(s.num_samples),
	num_sets(s.num_sets),
	samples(s.samples),
	disk_samples(s.disk_samples),
	hemisphere_samples(s.hemisphere_samples),
	shuffled_indices(s.shuffled_indices),
	count(s.count),
	jump(s.jump)
{}

//assignment operator:
Sampler&
Sampler::operator= (const Sampler& rhs) {

	if (this == &rhs) return *this;

	num_samples = rhs.num_samples;
	num_sets = rhs.num_sets;
	samples = rhs.samples;
	disk_samples = rhs.disk_samples;
	hemisphere_samples = rhs.hemisphere_samples;
	shuffled_indices = rhs.shuffled_indices;
	count = rhs.count;
	jump = rhs.jump;

	return *this;
}

//destructor:
Sampler::~Sampler(void) {}

void
Sampler::set_num_sets(const int np) {
	num_sets = np;
}

int
Sampler::get_num_samples(void) {
	return num_samples;
}

void // sets up randomly shuffled indices for the samples array
Sampler::setup_shuffled_indices(void) {
	shuffled_indices.reserve(num_samples * num_sets);
	std::vector<int> indices;

	for (int i = 0; i < num_samples; i++) 
		indices.push_back(i);

	for (int i = 0; i < num_sets; i++) {
		std::random_shuffle(indices.begin(), indices.end());

		for (int ii = 0; ii < num_samples; ii++)
			shuffled_indices.push_back(indices[ii]);
	}
}

Point2D //get next sample of unit square
Sampler::sample_unit_square(void) {
	if (count % num_samples == 0) // start of a new pixel
		jump = (rand_int() % num_sets) * num_samples;
	return samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

Point2D //get next sample of unit disc
Sampler::sample_unit_disk(void) {
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;
	return disk_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

Point3D //get next sample of hemisphere
Sampler::sample_hemisphere(void) {
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;
	return hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

Point3D
Sampler::sample_torus(void) {
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;
	return torus_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

Point3D
Sampler::sample_unit_sphere(void) {
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;
	return sphere_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

void
Sampler::map_samples_to_unit_disk(void) {
	
	int size = samples.size();

	double r, phi;
	Point2D sample;

	disk_samples.reserve(size);

	for (int i = 0; i < size; i++) {
		//convert sample to range [-1, 1]^2:
		sample.x = samples[i].x * 2.0 - 1.0;
		sample.y = samples[i].y * 2.0 - 1.0;

		double quarter_pi = PI / 4;

		//compute r and phi:
		if (sample.x > sample.y && sample.x > -sample.y) { //quarter 1
			r = sample.x;
			phi = quarter_pi * sample.y / sample.x;
		}
		else if (sample.x <= sample.y && sample.x > -sample.y) { //quarter 2
			r = sample.y;
			phi = quarter_pi * (2.0 - sample.x / sample.y);
		}
		else if (sample.x < sample.y && sample.x <= -sample.y) { //quarter 3
			r = (-sample.x);
			phi = quarter_pi * (4 + sample.y / sample.x);
		}
		else { //quarter 4
			r = (-sample.y);
			//check for division by 0 at origin:
			if (sample.y != 0.0)
				phi = quarter_pi * (6 - sample.x / sample.y);
			else
				phi = 0.0;
		}

		//convert back to cartesian coords:
		disk_samples[i].x = r * cos(phi);
		disk_samples[i].y = r * sin(phi);
	}

	samples.erase(samples.begin(), samples.end());
}

void
Sampler::map_samples_to_hemisphere(const double e) {
	int size = samples.size();
	hemisphere_samples.clear();
	hemisphere_samples.reserve(num_samples * num_sets);

	for (int i = 0; i < size; i++) {
		
		double cos_phi = cos(2.0 * PI * samples[i].x);
		double sin_phi = sin(2.0 * PI * samples[i].x);
		double cos_theta = pow((1.0 - samples[i].y), 1.0 / (e + 1.0));
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		double u_coord = sin_theta * cos_phi;
		double v_coord = sin_theta * sin_phi;
		double w_coord = cos_theta;

		hemisphere_samples.push_back(Point3D(u_coord, v_coord, w_coord));
	}
}

void
Sampler::map_samples_to_torus(double a, double b) {

	int size = samples.size();
	torus_samples.reserve(size);

	for (int i = 0; i < size; i++) {
		
		double cos_alpha = cos(2.0 * PI * samples[i].x);
		double sin_alpha = sin(2.0 * PI * samples[i].x);
		double cos_beta = cos(2.0 * PI * samples[i].y);
		double sin_beta = cos(2.0 * PI * samples[i].y);

		Vector3D v_a = Vector3D(cos_alpha * a, 0, sin_alpha * a);
		Vector3D v_a_n = v_a;
		v_a_n.normalize();
		Vector3D v_b = cos_beta * v_a_n + sin_beta * Vector3D(0, 1, 0);

		Point3D p(0, 0, 0);
		torus_samples.push_back(p + v_a + v_b);
	}
}

void
Sampler::map_samples_to_unit_sphere(void) {
	
	int size = samples.size();
	sphere_samples.reserve(size);

	for (int i = 0; i < size; i++) {

		double cos_phi = cos(2.0 * PI * samples[i].x);
		double sin_phi = sin(2.0 * PI * samples[i].x);
		double cos_theta = cos(2.0 * PI * samples[i].y);
		double sin_theta = sin(2.0 * PI * samples[i].y);

		double x = sin_phi * cos_theta;
		double y = sin_phi * sin_theta;
		double z = cos_phi;

		sphere_samples.push_back(Point3D(x, y, z));
	}
}