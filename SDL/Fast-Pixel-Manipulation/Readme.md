
we modify the entire pixels in the screen using surface and texture API in SDL.
<br/>

## Results
In our code both the surface and texture gives the same performance(6-7ms) since we programmed for the CPU. There is no inherent parallelization. For futher performance we need to use some graphics API openGL/Vulkan.

## Hints
Texture is beneficial when it is used with Render API provided. Especially when it is staic.

## Credits
[Pixel Pusher](https://github.com/DOOMReboot/PixelPusher)
