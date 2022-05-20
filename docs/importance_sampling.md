# Importance Sampling

## The problem
One of the more powerful tools in the ray tracing algorithm is the ability to abstract the behavior of materials with [BRDFs](https://en.wikipedia.org/wiki/Bidirectional_reflectance_distribution_function). They allow us to describe the behaviour of light rays when they interact with a material in a way that is particularly well suited to the object oriented paradigm of this project. 

A significant conceptual leap on this idea is the simulation of more complex materials by combining multiple BRDFs in a single material. [Phong's suggestion of an additive model](https://en.wikipedia.org/wiki/Phong_reflection_model) was a revoltionary piece of work in computer graphics theory. This approach works very well for the ray tracing algorithm as we get to compute the contribution of each BRDF when a ray hits an object and the added complexity is linear and thus relativly cheap for the results the new feature provides. However, when trying to adapt this idea to path tracing we encounter a significant problem. Namely, in path tracing, the contribution of each BRDF must be computed recursively, as that is the way our Monte Carlo estimator discovers paths of light in the scene. When we try to path trace a material with multiple BRDFs, the additive model requires that we recursively compute the value contributed by each BRDF. This results in branching recursion, and thus exponential computational and memory complexity with respect to maximum recursion depth. This is not a feasible approach for any meaningful recursive depth.

## The general idea
The [1994 paper by Lafortune and Willems](https://www.cs.princeton.edu/courses/archive/fall03/cs526/papers/lafortune94.pdf) offers a solution to the exponential complexity. The idea is to use a probabilistic approach to determine the behavior of light for each sample taken and that averaging of these will converge to Phong's additive model with a large enough number of samples, while keeping the complexity with respect to recursive depth linear. The paper discusses in depth how a lambertian and specular BRDFs can be blended to create a material which is diffuse in most places, but still posesses a specular highlight, making it a good candidate for simulating plastic materials. There are some nuanced caveats to be avare of, particularly when it comes to the blending of the probability distribution functions and restricting the intensity modifiers to ensure conservation of energy in the model. 

## My implementation
The simplest case to look at for the explanation of my implementation is the `Phong::path_shade` function. I will write a pseudocode outline here to explain the idea:

```
1. compute the albedo for both the lambertian and specular BRDFs
2. while computing the albedo, save the sampled direction of the reflected ray for each BRDF
3. add the albedos together
4. generate a random number in range [0, diffuse_intensity + specular_intensity], or [0, 1], whichever is higher (see conservation of energy section in paper)
5. the reflected ray will be in the diffuse direction if the random number is less than diffuse_intensity
6. the reflected ray will be in the specular direction if the random number is less than diffuse_intensity + specular_intensity
7. the function will return black is the random number fails the above two conditions, but is less than 1 (light absorbed)
8. The combined albedo values are multiplied by the color returned by the recursively generated reflective ray
```

Note that the actual code is more condensed than this to optimize out any temporary variables and value copying where possible. 

This idea is extended in other materials that inherit from `Phong` and use different or more multiple BRDFs. 

## Results

As expected, the above change reduces the complexity with respect to recursive depth from exponential to linear when rendering specific materials, while maintainig visually comparable results. In practice, we need to use slightly higher numbers of samples for comparable results because of the slower convergence of the probabilistic model, but this is still only a linear complexity and well worth the cost. It is also important to note the added overhead of generating a random number at each shading call. While a generally costly operation, generating a random number is still constant overhead and it is worthwhile over the branching recursion for any number of samples and recursive depth that would generate even barely recognizable images. One of the further steps to optimize this approach would be to use a set of random numbers that are computed when the scene is built before the rendering starts, similar to the approach for super-sampling that Suffern suggests in the book, but I have not found the overhead to be significant enough to justify the development of this for my demonstrative purposes. 
