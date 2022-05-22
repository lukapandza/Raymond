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

The hyperlinked entries below lead to my documentation of the features which are entirely or partially my creation and differ significantly from the implementation discussed in Suffern's book. All others include minor additions, optimizations or simply an update to the recent style of C++. For more information on those, please refer to Suffern's book, as it provides a much better explanation than I could. 

### Algorithms

* [Multi-threadded CPU execution](https://github.com/lukapandza/Raymond/blob/main/docs/multi-thread.md)
* <details>
    <summary>Ray Tracing</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 1, 3
    </details>
* <details>
    <summary>Whitted-style Ray Tracing</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 24, 25
    </details>
* <details>
    <summary>Ray Tracing with area lights</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 18
    </details>
* <details>
    <summary>Path Tracing</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 26
    </details>
* [Importance sampling of complex materials](https://github.com/lukapandza/Raymond/blob/main/docs/importance_sampling.md)
* [Adaptive Sampling](https://github.com/lukapandza/Raymond/blob/main/docs/adaptive_sampling.md) (priority queue based distribution between all CPU threads)
* [Regular grid acceleration](https://github.com/lukapandza/Raymond/blob/main/docs/acceleration_grid.md)
* <details>
    <summary>Antialiasing</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 4
    </details>
* <details>
    <summary>Pre-computed Sampling</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 5, 6, 7
    </details>

### Geometric

* <details>
    <summary>All Standard Primitives</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 19
    </details>
* <details>
    <summary>Partial Objects</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 19.7
    </details>
* <details>
    <summary>Compound Objects</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 19.8
    </details>
* <details>
    <summary>Instancing</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 21
    </details>
* <details>
    <summary>Affine Transformations</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 20
    </details>
* <details>
    <summary>Orthographic and Perspective projections</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 3, 8, 9
    </details>

### Materials & Lights

* <details>
    <summary>Point, Directional Lights</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 14
    </details>
* <details>
    <summary>Shadows</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 16
    </details>
* <details>
    <summary>Area Lights</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 18
    </details>
* <details>
    <summary>Environment Lights</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 18.10
    </details>
* <details>
    <summary>Emissive Materials</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 18, 26
    </details>
* <details>
    <summary>Phong Model Materials</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 14, 15
    </details>
* <details>
    <summary>Glossy and Perfect Reflection</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 24, 25
    </details>
* <details>
    <summary>Dielectric Transparency</summary> 
        K. Suffern, Ray Tracing from the Ground Up, CH. 28
    </details>

### UI

* Simple GUI built with Qt (primarily there to make test rendering simpler)

## How to build and run

This project was created with Microsoft Visual Studio 2019 Community edition and and the opensource version of the Qt 5.12.12 library for the Visual Studio compiler. 

To build and run the project, [download and install the Qt libraries](https://www.qt.io/offline-installers), or build them from source. Then open the Raymond.sln file using Visual Studio. The Debug and Release buidl settings should import with the Visual Studio configuration file, but there might be some linking that needs to be resolved in the project settings, depending on the location of the Qt binaries. I have not tested this project on any platforms other than Windows 10.

In the `World.cpp` file, there must always be one and only one .cpp file with the `World::build()` function definition. This is how the scenes are made. Use any of the scenes from the `src/builds` folder, or write your own. Writing your own scene might require more extensive study of the existing scenes to familiarize yourself with the process. I recommend making a copy of an existing scene which renders correctly, including it in `World.cpp` and then making modifications. 

## Future Plans

While the idea of simply adding more features to this project seems attractive, I currently plan to return to this project in the near future by reorganizing to keep only the path tracing part of the code, and make it into a CUDA project to move away from the multi-threaded approach and into GPU programming. 

The secondary goal, following the completion of the one above is to explore further academic research in the field, such as photon mapping, directed light transport and neural network denoising.

Lastly, it would be very nice to create a scripting language paired with a more useful GUI and share this as an opensource project for users to actually be able to make some art/simulations with it. This is on the bottom of my list as UI design is not one of my strengths nor high on my list of interests at the moment. 
