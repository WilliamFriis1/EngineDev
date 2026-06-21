# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("VulkanEngine")

add_executable (VulkanEngine 
	"src/Sandbox/main.cpp"
	"src/Engine/VulkanEngine.cpp"
	"src/Engine/Rendering/SwapChain.cpp" 
	"src/Engine/Rendering/RenderPass.cpp" 
	"src/Engine/Rendering/FramebufferManager.cpp" 
	"src/Engine/Rendering/GraphicsPipeline.cpp" 
	"src/Engine/Rendering/CommandPool.cpp" 
	"src/Engine/Rendering/CommandBufferManager.cpp" 
	"src/Engine/Rendering/SyncManager.cpp" 
	"src/Utility/DebugMessenger.h"
	"src/Utility/AssetManager.cpp"
	"src/Engine/Resources/VertexBuffer.h")

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

#Definitions
target_compile_definitions(VulkanEngine PRIVATE
    ENGINE_ROOT="${CMAKE_SOURCE_DIR}"
)

#Compilation
find_program(GLSLC_EXECUTABLE glslc REQUIRED)

set(SHADER_SRC_DIR ${CMAKE_SOURCE_DIR}/assets/shaders/src)
set(SHADER_BIN_DIR ${CMAKE_SOURCE_DIR}/assets/shaders/bin)

file(GLOB SHADERS
    ${SHADER_SRC_DIR}/*.vert
    ${SHADER_SRC_DIR}/*.frag
)

set(SPIRV_OUTPUTS)

foreach(SHADER ${SHADERS})
	get_filename_component(FILE_NAME ${SHADER} NAME)
	set(SPIRV_FILE ${SHADER_BIN_DIR}/${FILE_NAME}.spv)

	add_custom_command(
		OUTPUT ${SPIRV_FILE}
		COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADER_BIN_DIR}
		COMMAND ${GLSLC_EXECUTABLE} ${SHADER} -o ${SPIRV_FILE}
		DEPENDS ${SHADER}
		VERBATIM
	)

	list(APPEND SPIRV_OUTPUTS ${SPIRV_FILE})
endforeach()

add_custom_target(Shaders ALL DEPENDS ${SPIRV_OUTPUTS})

add_dependencies(VulkanEngine Shaders)
