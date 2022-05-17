# Adaptive Sampling

## The problem

When an algorithm like path tracing relies on Monte Carlo sampling to compute the integral of the rendering equation, there are cases in which a lot of the samples are wasted. Suppose that we are sending a fixed number of samples through random points in each pixel on our canvas. Suppose further that we are rendeing a pixel that happens to have no objects behind it. In this case we will repeatedly compute the color by sending additional samples, but they will always be black as no intersection happens with the rays that we are casting. We are clearly wasting samples. 

## The general idea

The idea behing adaptive sampling is to address the problem outlined above, by only sending further samples through a pixel until the data we are getting converges to some minimal allowed variance. 

This approach is old and well explored in ray tracing algorithms. Consider the following diagram:

<img src="https://web.cs.wpi.edu/~matt/courses/cs563/talks/antialiasing/aliasing4.gif"></img>

The big idea is to start sampling each pixel by sampling the extreme corners and to only take further samples that recursively subdivide the pixel area if the variance between of the colors returned by the 4 main rays is higher than some threshold.

This approach works well for ray tracing since an identical ray will in general return an identical color every time it is cast into the scene. This is not the case with path tracing, since the rays recursively generate rays when hitting any material except for ones that emit light. The most frequent modern approach to this problem in path tracing is adding a de-noising step after the render, usually based on a pre-trained neural network.

A further difficulty in path tracing is that in scenes where light sources are relatively small, most rays will not hit a light source before reaching their recursive depth limit and they will return black. In terms of sampling distribution, this means that for a lot of pixels, we will have a bimodal distribution, where there is a distinct large group of samples that have no color, and the second, usually smaller group of samples where the hitpoint is actually illuminated.

## My approach 

In my implementation of this idea, I try to leverage the fact that variance tells us some useful information about the difficulty of rendering a specific pixel. While this algorithm is powerful when it is done pixel by pixel, we can't do much more than simply keep sampling until we hit the low threshold or reach some maximum number of samples for a given pixel. I would like my renderer to make decisions based on how the variances of the different pixels relate to each other. Thus I came up with the following solution:

* Do a first pass of a minimum number of samples for each pixel in the image (usually 10% of maximum unmber of samples)
* Compute the variance of each pixel after the first pass
* Put the pixels back into a priority queue, using the comparison of variance as the prioritization criteria
* Have each available thread pop the highest variance pixels from the queue, take additional samples and push it back into the queue
* Pixels are not put back into the queue if we reached the threshold variance for the pixel, or we used the maximum number of samples
* Continue until the queue is empty

This approach grants some additional perks as well. As the information about variance is stored for each pixel, we can simply render this information into a separate image at the end to see the variance map. These can reveal some useful information.

### Math


