
Since SDL provides API for modifying the pixels using CPU and GPU, We will perform some benchmarks regarding various API and methods to update the pixels in screen.
<br/>


SDL provides only a few features. In our code both the surface and texture gives the same performance since we programmed for the CPU. There is no inherent parallelization.

Using a Texture is beneficial when it is static.
