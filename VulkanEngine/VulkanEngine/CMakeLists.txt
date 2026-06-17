# CMakeList.txt : CMake project for VulkanEngine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (VulkanEngine 
	"src/Sandbox/main.cpp"
	"src/Engine/VulkanEngine.cpp"
	"src/Engine/Rendering/SwapChain.cpp" 
	"src/Engine/Rendering/RenderPass.cpp" 
	"src/Engine/Rendering/FramebufferManager.cpp" 
	"src/Utility/DebugMessenger.h" 
	"src/Engine/Rendering/GraphicsPipeline.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET VulkanEngine PROPERTY CXX_STANDARD 20)
endif()

#Libraries
find_package(Vulkan REQUIRED)

target_link_libraries(VulkanEngine PRIVATE Vulkan::Vulkan)

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)

FetchContent_MakeAvailable(glfw)

target_link_libraries(VulkanEngine PRIVATE glfw)

target_include_directories(VulkanEngine PRIVATE src)
