# Raymond
This is physically based rendering engine implementing a number of rendering algorithms. 

The entire engine is written in C++. The project started by following Kevin Suffern's book Ray Tracing From the Ground Up, but diverged significantly in later stages. Many improvements are adapted from contemporary research and the adaptive sampling scheme is my original approach to the problem of wasted oversampling.

I chose to forgo some standard features like texture mapping and noise generation that are common in other similar projects and instead focused on the more mathematically and algorithmically interesting ideas. Below is a showcase of some renders and a list of notable features.

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
* Adaptive sampling (priority queue based distribution between all CPU threads)
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


# Code Review Section

## How to build and run

I don't have an easy answer here. This is a big project built in Visual Studio and later connected with the Qt library. This took me a couple of days to set up. 
If one is still inclined to play with this, you would have to:

* Install the appropriate [Open Source version of Qt](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5) or build it from source.
* The appropirate installation method will vary based on your compiler of choice.
* Clone the c++ files found in src/
* Modify the qmake file to fit your library version / target platform / compiler and ensure that everything is linked correctly
* Select a build file from the .cpp files in src/builds/ or write your own scene
* Uncomment or Add the desired build file in World.cpp
* Build and run

The project is modular enough that one does not need to be able to build and run to effectively review the code, so any feedback is appreciated even if you can't get it working!

## Why the code is the way it is

Some things to keep in mind when looking over the code:

* The primary concern behind most decisions in the code is speed of execution. This means in some cases the program is absurdly wasteful with memory (like each thread keeping a separatecopy of the world), but most often these are done to increase the execution speed. That said, I'm always lokoing for ideas to better manage memory without sacrificing speed.
* Excessive comments in class header files are there to use the Visual Studio's extra info on hover feature.

## Which Code to review

### If you like geometry

Each class that inherits from `GeometricObject` implements a `hit()` function that takes in a ray and the current minimum scalar `t` and detemrines if the ray intersects the object in question. These range from very simple ones like the plane to complex ones like the Torus. Any feedback on the understandability / corectness / efficiency of these is appreciated. 

### If you like obscure ways of optimizing C++

The classes in `Utilities/` do the bulk of the work when rednering an image. As a consequence these are meant to be lightweight and fast. Shaving off nanoseconds here makes all the difference for execution speed. Any feedback to make these run faster or eliminate unnecessery steps is appreciated.

### If you like OOP

The project's architecture is pretty complex but it was also built piece by piece over a longer time period. Any feedback on better ways of designing the architecture or simplifying the inheritance scheme is appreciated. 


