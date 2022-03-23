# Raymond
A physically based rendering engine implementing a number of rendering algorithms


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


