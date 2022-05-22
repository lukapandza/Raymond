# Multi-Threaded architecture

Multi-threading was the first major modification I made to Suffern's architecture. Namely, this project uses the STL `thread` library to allow execution on any number of available cores of the CPU. By default, I have elected to use `max_concurrency - 1` cores, so that one CPU core remains available to ensure general functionality of my computer, as some of the renders can take hours and it is convenient to just let them run in the background. Since the addition of the adaptive sampling algorithm for path tracing, there are two distinct implementations of multi-treading described below:

## Supersampling Architecture

The `Render > Start` button in the GUI is tied to the first approach which uses traditional supersampling. When the rendering starts, a specified number of `Thread` objects are created. They each hold a pointer to the main `Raymond` which holds the canvas, and they all run the `World::build()` function, saving an identical copy of the scene for themselves. This is inefficient in terms of memory, but much faster than the earlier approach I had of putting a mutex lock on any object which might be accessed by multiple threads, which resulted in a lot of frequent wait conditions. The optimal approach probably lies somewhere between these two extremes and further experimentation would be required to find the sweetspot.

Once the threads are created, the set of pixels that need to be rednered is split into distinct chunks which are then assigned to the threads at random. This is an unnecessary step, but it provided with a more satisfying tiled rendering visualization as opposed to the simple top to bottom filling in order.

The threads are then detached and the simply loop over each of the pixels they were assigned until all the pixels are rendered. When each pixel is rendered, they write it to the main canvas held in the main window object. The main canvas is protected with a mutex lock, but the writing is very fast compared to the actual rendering of a pixel, so there are no significant cottlenecks here.

The main window runs a `QTimer` which displays the current state of the canvas to the main window at set intervals. A value of 16ms gives a smooth painting process of above 60Hz. 

Once all the threads are complete, a `RenderEnd` signal is passed and some new information replaces the usual timer and progress bar and the option to save the image becomes available.


## Adaptive Sampling Architecture

The adaptive sampling architecture was created to leverage multi-threading with the adaptive sampling approach described in a separate documentation file. In some ways it is simple than the above approach.

There are now two objects which are shared between the threads, the canvas as before as well as the priority queue of `QueuedPixel` objects. These are both protected by a mutex lock.

The option that invokes the use of this architecture is the `Render > Start (Adaptive)` GUI button. When the rendering starts, a specified number of `AdaptiveThread` objects are created. After their intialization, they all get a distinct, yet identical copy of the scene through `World::build()` as was the case before. A pripority queue is then created and all of the pixels are initialized with the values of the checkered background placeholder, along with other information required by the `QueuedPixel` class. The threads are then detached, and they simply run in a loop until the shared priority queue is empty. When the queue is empty, the `RenderEnd` signal is sent to the main window and the information bar is updated, which now also includes a percentage of samples that were not needed under the new architecture. See the Adaptive Sampling document for more details on this. 

## Notes

This design varies slightly from the style of the rest of the objects, as the threads would ideally inherit from an abstract thread class that implements the significant part of the shared functionality, but this seemed unnecessary as I only planned to have these two options added to the project. In the future, if more multi-threading architectures are added to the object, the first step would be refactoring this into an inheritance scheme.
