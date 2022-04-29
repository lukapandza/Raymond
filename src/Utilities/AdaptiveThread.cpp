#include "AdaptiveThread.h"

#include "../../../raymond.h"
#include "../World/World.h"
#include "QueuedPixel.h"

AdaptiveThread::AdaptiveThread(World* _world, Raymond* _main_window)
    : world(_world), main_window(_main_window),
    min_samples(max(1, _world->max_samples / 10)), 
    max_samples(_world->max_samples),
    variance_tolerance(_world->variance_tolerance),
    sample_batch_size(_world->sample_batch_size)
{}

void
AdaptiveThread::SetPixel(const int x, const int y, const RGBColor& col, int num_samples)
{
    RGBColor out_col = col.max_to_one();
    int r = (int)(out_col.r * 255);
    int g = (int)(out_col.g * 255);
    int b = (int)(out_col.b * 255);

    this->main_window->mtx.lock();
    this->main_window->canvas.setPixelColor(x, y, QColor(r, g, b));
    this->main_window->mtx.unlock();
}

void 
AdaptiveThread::Render() 
{
    bool done = false;

    while (!done) {
        
        this->main_window->mtx.lock();

        if (this->main_window->queue.empty()) {
            done = true;
            this->main_window->mtx.unlock();
            break;
        }

        QueuedPixel* pixel = this->main_window->queue.top();
        this->main_window->queue.pop();
        this->main_window->mtx.unlock();

        int num_samples = sample_batch_size;

        if (!pixel->finished_first_pass) {
            num_samples = min_samples;
            pixel->finished_first_pass = true;
        }

        if (num_samples > (this->max_samples - pixel->num_samples))
            num_samples = this->max_samples - pixel->num_samples;

        std::vector<RGBColor> samples;

        for (int i(0); i < num_samples; i++)
            samples.push_back(this->world->camera_ptr->sample_pixel(this->world, pixel->h, pixel->v));
        
        pixel->update(samples);

        this->SetPixel(pixel->h, this->world->vp.vres - pixel->v - 1, pixel->avg_color * pixel->num_hits / pixel->num_samples, num_samples);

        //if ((pixel->get_variance() < this->variance_tolerance && pixel->num_hits > pixel->num_samples / 20) || pixel->num_samples >= this->max_samples) {
        if (pixel->get_variance() < this->variance_tolerance || pixel->num_samples >= this->max_samples) {
        
            this->main_window->mtx.lock();

            this->main_window->pixels_rendered++;
            this->main_window->samples_skipped += (this->max_samples - pixel->num_samples);

            this->main_window->sample_density_map[pix_coord(pixel->h, this->world->vp.vres - pixel->v - 1)] = pixel->num_samples;
            this->main_window->variance_density_map[pix_coord(pixel->h, this->world->vp.vres - pixel->v - 1)] = pixel->get_variance();

            this->main_window->mtx.unlock();

            delete pixel;
        }

        else {
            this->main_window->mtx.lock();
            this->main_window->queue.push(pixel);
            this->main_window->mtx.unlock();
        }
    }
}
