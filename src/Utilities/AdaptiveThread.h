#pragma once
#include <vector>
#include "RGBColor.h"

class Raymond;
class World;

class AdaptiveThread {

public:

    World* world;
    Raymond* main_window;
    int min_samples, max_samples;
    double variance_tolerance;
    int sample_batch_size;

    AdaptiveThread(World* _world, Raymond* _main_window);

    void SetPixel(const int x, const int y, const RGBColor& col, int num_samples);

    void Render();
};