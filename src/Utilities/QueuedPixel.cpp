#include "QueuedPixel.h"
#include "Constants.h"

QueuedPixel::QueuedPixel(int h, int v)
	: h(h), v(v),
	num_hits(0), num_samples(0),
	finished_first_pass(false),
	avg_color(0),
	M_prev(0), M_curr(0), 
	S_prev(0), S_curr(0),
	variance(0)
{}

void
QueuedPixel::add_sample(const RGBColor& sample) 
{
	// for explanation of following code, see Knuth's The Art of Computer Programming,
	// vol. 2, 3rd ed, p 232.
	// the idea is to express variance formula as a recurrence relation so that
	// samples can be added on the fly
	
	this->num_samples++;

	if (sample != black) {// sample hit a light source

		this->num_hits++;
		this->avg_color += (sample - this->avg_color) / num_hits;

		if (this->num_hits == 1) {
			this->M_prev = this->M_curr = sample.magnitude();
			this->S_prev = 0.0;
		}
		else {
			double sample_luminosity = sample.magnitude();
			// update M and S
			M_curr = M_prev + (sample_luminosity - M_prev) / num_hits;
			S_curr = S_prev + (sample_luminosity - M_prev) * (sample_luminosity - M_curr);

			// set up for next iteration
			this->M_prev = this->M_curr;
			this->S_prev = this->S_curr;
		}
	}
}

void
QueuedPixel::update(const std::vector<RGBColor>& samples)
{
	for (int i(0); i < samples.size(); i++)
		this->add_sample(samples[i]);
}
