## Problem:
How to fill/shade a circle only with rectangles?  
Here we use SDL library. The SDL library is made to draw rectangles/lines using hardware acceleration. So I had an idea to draw a circle using only rectangles.

*Rendering it using lines will be faster.*

## Solution:
Draw a diagram and try it yourself to understand it.

we will fill the circle by finding the rectangle with the maximum area in each iteration.<br/>
How to find the maximum area. ?

We will be using ternary search. Since the derivatives i calculated resulted in unsolvable non-polynomial equations.
The width of the rectangle with the maximum area is a Unimodal function(I couldn't find a solid proof). But there has to be a single(atleast not atmost) rectangle  
with a maximum area.

## Results:

We have to transform and copy to get the full circle.
for simplicity i have done only the octant.
![result](https://user-images.githubusercontent.com/74656297/127368787-cf2eb63c-63a3-4715-9b84-857263a668bf.png)





