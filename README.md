# EngineDevelopment
## Sideproject aimed to improve my understanding and skills of Vulkan and game engine architechture.

I'm a Game Dev bachelor graduate looking to deepen my understanding of game engine architecture through the creation of my own engine.

### Dependecies
CMake 4.3.3
Vulcan 1.4.350.0.
glfw 3.5

### Purpose of development
This engine is solely for educational purposes at the moment, and the read me will act as a log for my implementation steps.  

### General Description:
VulkanEngine.h is the driving force and manager for the entire system as of yet, while other classes like swapchain and renderpass are only dependent in order of creation and destruction during runtime.

### Log
This log has started a few days into the project, but will from now on get continous updates.

#### 15/6 - 2026
The basic Vulkan setup is getting close to completion, missing a few key components:
- Dynamic creation and destruction of swapchain, framebuffers and imageviews.
- Command buffers
- Graphics pipeline
- Synochronization

##### Todays implementations
- Completed initial render pass implementation
- Added framebuffer for the swapchain
- Implemented debug messenger for validation layer debugging
#### ---------------------------------
