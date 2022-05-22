# Regular Acceleration Grid

## The problem

The basic algorithm used for finding a hitpoint in both ray and path tracing is the following:

```
1. cast a ray from the viewpoint
2. intersect the ray with all objects in the scene
3. compute the distance of the hitpoint from the origin of the ray for each object that was hit
4. return the hitpoint that is closest to the ray origin
```

This method clearly implies a linear computational complexity with respect to the number of objects in a scene. In practical applications, this is a drawback for many non-physically based rendering methods, usually when the objects in question are specifically large clusters of triangles. A powerful optimization that can be made for ray/path tracing is the avoidance of the necessity to intersect all objects for each sample. 


## The general idea

There are two categories of approaches to solving this problem. [Bounding Volume Hierarchies](https://en.wikipedia.org/wiki/Bounding_volume_hierarchy) and [Binary Space Partitioning](https://en.wikipedia.org/wiki/Binary_space_partitioning) fall under the tree-based approaches, while Uniform Grids and [Octrees](https://en.wikipedia.org/wiki/Octree) fall under the axis-aligned grid approaches. 

The idea behind all of these approaches is to change the method of searching for the closest intersection from an exhaustive one to one where we get to discard large sections of the search space at once. The specific acceleration scheme that I have implemented is the Uniform Grid, as it's the one that Kevin Suffern goes on in the book in great detail. For more information about the concept, see chapter 22 of Suffern's book. In this specific case, the conceptual diea is not challenging, but the trick lies in all the specific edge cases that could happen with computing bounding boxes, dealing with transformed objects and instancing and cases where an object might be assigned to multiple cells within a grid. 


## My implementation

I consider this an experimental feature within this project, because while it does closely follow Suffern's implementation, I have not exhaustively tested the feature to ensure correctness in all the edge cases. The general tests, however, seem successful. 

There are some prerequisities to note before the implementation is outlined:
1. All objects that are to be added into an acceleration grid must have a bounding box described. Stylistically, it made the most sense to do this at the construction of the objects. Good examples are the sphere and the torus.
2. If an instance of an object is created, and the affine transformations applied to it, the bounding box will also effectively be transformed, and thus no longer function correctly within the acceleration grid as it might not be axis aligned. Suffern suggests that the simplest, if not most efficient, solution to this is computing a bounding box of a bounding box after all the transformations are complete. 
3. The acceleration grid holds a list of object and it inherits from `GeometricObject`. This is important because it allows to impose a recursive structure on the acceleration grid, so that it may store sub-grids.

Process outline:

```
1. Create an empty grid using the default constructor
2. Add objects to the grid instead of to the world
3. Create a bounding box for the grid that contains all the bounding boxes of the objects in the list
4. Split the grid into equal cells (Suffern suggests about 8 times more cells than objects; still have to test performance with other values)
5. Allocate the appropriate amount of memory to hold the cells
6. Assign each object from the objects list to the appropriate cells
7. Delete the objects list to free up memory
```

This is a rather expensive setup procedure, but it only occurs once at time of building. The real benefits come from the effifiency of the `hit` function. Once we determine where the origin of the ray is in relation to the grid and which cell is hit first, it is easy to compute which cell will be hit next, due to the constant angle and regular spacing of the cells. We then continue and only intersect the objects that happen to belong to the cell we just intersected. 

Suffern provides a very good explanation of this with supporting diagrams in chapter 22 of his book. The conclusion is that the complexity is reduced from liner to cube root of number of object in the worst case where we always have to traverse the whole grid to reach the first object, and constant in the best case, where the object is always at the closest edge of the grid. Suffern notes that in practice, this approach yields logarithmic complexity in the average case. 


## Results

<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/grid/2^3spheres.png" width = "24%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/grid/8^3.png" width = "24%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/grid/16^3.png" width = "24%"></img>
<img src="https://github.com/lukapandza/Raymond/blob/main/Renders/Gallery/grid/100^3spheres.png" width = "24%"></img>

The only testing I have done is creating a grid in space that gets filled with an ever increasing number of spheres, which allowed me to test the efficiency upgrade. The left-most picture contains only 8 spheres, with a render time of .4s (including build time). The rightmost picture includes a million spheres and the render time was 45 seconds including the build time, noting that the build time took the vast majority of this. This seems to be one of the more favorable cases, as the gaps are relatively small and most rays will encounter a sphere near the start of the traversal. In any case, this would be something that is entirely impossible to render in the previous configuration.

