#pragma once

#include "RGBColor.h"
#include <vector>

class QueuedPixel
{
public:

	QueuedPixel(int h, int v);

	double get_variance() const;

	void add_sample(const RGBColor& sample);

	void update(const std::vector<RGBColor>& samples);

	int h, v;
	int num_hits, num_samples;
	bool finished_first_pass;
	RGBColor M_prev, M_curr;
	RGBColor S_prev, S_curr;
	double variance;
};

inline bool
operator<(const QueuedPixel& lhs, const QueuedPixel& rhs)
{
	if (lhs.finished_first_pass && !rhs.finished_first_pass)
		return true;
	else if (!lhs.finished_first_pass && rhs.finished_first_pass)
		return false;
	else 
		return lhs.get_variance() < rhs.get_variance();
}

inline double
QueuedPixel::get_variance() const
{
	//return this->num_hits > 1 ? sqrt((this->S_curr / (this->num_hits - 1)).average()) : 0.0;
	return this->num_hits > 1 ? this->S_curr.magnitude() / (this->num_hits - 1) : 0.0;
	//return this->variance;
}

struct ComparePointers {
	bool operator()(const QueuedPixel* lhs, const QueuedPixel* rhs)
	{
		return *lhs < *rhs;
	}
};
