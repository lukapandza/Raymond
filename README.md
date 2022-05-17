# Raymond
This is physically based rendering engine implementing a number of rendering algorithms. 

The entire engine is written in C++. The project started by following Kevin Suffern's book Ray Tracing From the Ground Up, but diverged significantly in later stages. Many improvements are adapted from contemporary research and the adaptive sampling scheme is my original approach to the problem of wasted oversampling.

I chose to forgo some standard features like texture mapping and noise generation that are common in other similar projects and instead focused on the more mathematically and algorithmically interesting ideas. Below is a showcase of some renders and a list of notable features.

<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/wide_4096_spp.png" width="99%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/matte_only_16384_6.png" width="26%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/fun%202.png" width="46%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/fun.png" width="26%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/10000_8_3_36_57.png" width="49.33%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/10000_8_4_12_51.png" width="49.33%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/16384_1080p.png" width="63%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/owl_16384.png" width="35.5%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/stacked_r.png" width="32.67%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/stacked_rg.png" width="32.67%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/stacked_rgb.png" width="32.67%"></img>

## Notable Features

### Algorithms

* Multi-threadded CPU execution
* Ray Tracing
* Whitted-style Ray Tracing
* Ray Tracing with area lights 
* Path Tracing
* Importance sampling of complex materials
* [Adaptive Sampling](https://github.com/lukapandza/Raymond/blob/main/docs/adaptive_sampling.md) (priority queue based distribution between all CPU threads)
* Regular grid acceleration
* Pre-computed sampling

### Geometric

* All standard primitives
* Partial objects
* Compound objects
* Instancing
* Affine Transformation
* Orthographic and Perspective projections

### Materials & Lights

* Point, Directional Lights
* Area lights
* Environment ligths
* Emissive materials
* Phong model materials
* Glossy and Perfect reflections
* Dielectric transparency

### UI

* Simple GUI built with Qt (primarily there to make test rendering simpler)
