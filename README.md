# EngineDevelopment
## Sideproject aimed to improve my understanding Vulkan and game engine architechture.

I'm a Game Dev bachelor graduate looking to deepen my understanding of game engine architecture through the creation of my own engine. 
The development speed of this project will be slow, as the major goal of this project is not a finished product, rather making sure that I gain understanding of the subject.

### Dependecies
- CMake 4.3.3
- Vulcan 1.4.350.0.
- glfw 3.5

### Purpose of development
This engine is solely for educational purposes at the moment, and the read me will act as a journal for my implementation steps.  

### General Description of files (will update continously):

#### Managers
VulkanEngine.h is the driving force and manager for the entire system. This will remain the main manager until other parts of the engine that are not graphics related are implemented.  

#### Rendering
Swapchain, renderpass and framebuffer are all part of the initial setup to render a frame.

Graphicspipeline is responsible for parsing shaders and building the entire graphics pipeline.

CommandPool and CommandBuffer is for passing GPU commands.

SyncManager is responsible for the synochronization of frames and swapchain images. 

TransferManager is currently only responsible for the uploading of buffers to the GPU. This class will be extended later on.

ResourceManager will be responsible for GPU resources, however, currently instantiates meshes.

#### Utility
AssetManager is a utility class for correct filepath usage.

DebugMessenger is a utility class for the validation layers.

#### Resources
The buffer class is simply an interface for subsequent buffers to utilize, to avoid code repetition.

Staging buffer uploads data to index or vertex buffer allocated memory.

Other buffer classes are simple wrappers from usage- and memory flags.

Mesh class currently contains GPU resources associated with meshes. Will most likely simply store a reference to relevant resources in the future.


### Journal
This journal was started a few days into the project, but will from now on get continous updates.

#### ---------------------------------
#### 15/6 - 2026
The basic Vulkan setup is getting close to completion, missing a few key components:
- Dynamic creation and destruction of swapchain, framebuffers and imageviews.
- Command buffers
- Graphics pipeline
- Synochronization

##### Todays work
- Completed initial render pass implementation
- Added framebuffer for the swapchain
- Implemented debug messenger for validation layer debugging
#### ---------------------------------
#### 17/06 - 2026
Graphics pipeline coming along. Once finished, command buffers is the next step.

#### Todays work
- Implemented dynamic rebuilding of the swapchain incase of changes in framebuffer. It is prepared to run on vulkan failures once relevant.
- Error handling for debug messenger, extensions were not enabled.
- Implemented simple vertex- and frag shaders. 
- File parsing for reading the binary SPIR-V files (.spv) to create shader modules.
- Began working on graphics pipeline. 
#### ---------------------------------
#### 19/06 - 2026
CMake and filepath errors fixed. Graphics pipeline done.

##### Todays work
- Graphics pipeline finished
- Added AssetManager class for path convenience
- Removed redudant subfolder
- Implemented CommandPools and CommandBuffer
#### ---------------------------------
#### 20/06 - 2026
The triangle is finally rendered.
##### Todays work
- Singular semaphores implemented for the entire commandbuffer. Will improve this for further synchornization safety.
- drawFrame function implemented, and recreation of swapchain handling extended with checks during drawframe in case of error handles during image aquiring and presentation.
#### ---------------------------------
#### 21/06 - 2026
Synchronization improved and finished (for now). Started moving away from hardcoded vertices now that everything works, and started implementing the vertex buffer.

#### Todays work
- Synochronization complete
- Auto compiling shaders on rebuilds
- Began working on vertex buffer.
#### ---------------------------------
#### 14/07 - 2026
Back after a few weeks. Decided to go with a generic buffer class instead of repeating code in all buffers. Uploading responsibility has been put in a transfer manager class.

#### Todays work
- Buffer class implementation
- Transfer manager implementation
#### ---------------------------------
#### 19/07 - 2026
Some architectural changes made, and I'm getting close a full resource pipeline.

#### Todays work
- Rudimentary resource manager implementation
- Staging buffer
- Finished transfer manager
- Vertex buffer
#### ---------------------------------
#### 20/07 - 2026
No longer a hardcoded triangle, but some temp solutions added until assets and mesh classes are in place.

#### Todays work
- Removed previous hardcoded instructions
- Fixed compilation errors for shaders
- Added a temp common.h for vertex struct, will later live in Mesh
- Temp solutions to bind vert buffer to command buffers, will be changed later on
#### ---------------------------------- 
#### 21/07 - 2026
Implemented index buffers and mesh class. Resource manager currently instantiates the meshes, but this will change later on. Command buffer manager now accepts a vector of meshes, which also feels like a great milestone.
Asset loading seems like the next step.

#### Todays work
- Index buffer
- Mesh class
- adjusted class files to a more typical c++ naming convention
#### ---------------------------------- 