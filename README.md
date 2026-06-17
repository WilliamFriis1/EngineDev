# EngineDevelopment
## Sideproject aimed to improve my understanding Vulkan and game engine architechture.

I'm a Game Dev bachelor graduate looking to deepen my understanding of game engine architecture through the creation of my own engine.

### Dependecies
- CMake 4.3.3
- Vulcan 1.4.350.0.
- glfw 3.5

### Purpose of development
This engine is solely for educational purposes at the moment, and the read me will act as a journal for my implementation steps.  

### General Description of files (will update continously):
VulkanEngine.h is the driving force and manager for the entire system. This will remain the main manager until other parts of the engine that are not graphics related are implemented.  

Swapchain, renderpass and framebuffer are all part of the initial setup to render a frame. 

Graphicspipeline is responsible for parsing shaders and building the entire graphics pipeline.

DebugMessenger is a utility class for the validation layers.

### Journal
This journal was started a few days into the project, but will from now on get continous updates.

#### ---------------------------------
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
#### 17/06 - 2026
Graphics pipeline coming along. Once finished, command buffers is the next step.

#### Todays implementations
- Implemented dynamic rebuilding of the swapchain incase of changes in framebuffer. It is prepared to run on vulkan failures once relevant.
- Error handling for debug messenger, extensions were not enabled.
- Implemented simple vertex- and frag shaders. 
- File parsing for reading the binary SPIR-V files (.spv) to create shader modules.
- Began working on graphics pipeline. 
#### ---------------------------------