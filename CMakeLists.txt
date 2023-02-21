cmake_minimum_required(VERSION 3.9)
project(VulkanTutorial LANGUAGES CXX VERSION 0.9)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) 
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

option(BUILD_TUTORIALS "Build the explicit vulkan-tutorial projects" TRUE)

# Uncomment these lines to compile for debugging:
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Check the OS:
if(MSVC OR MINGW)
  # If on Windows:

elseif(UNIX AND NOT APPLE)
  # If on Linux:
  set(CMAKE_CXX_FLAGS "-Wall -mtune=native -march=native -g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fno-math-errno -fno-signed-zeros -fno-trapping-math -freciprocal-math -fno-rounding-math -fno-signaling-nans -fexcess-precision=fast")

elseif(APPLE)
  # In on Apple:

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the included directories:
include_directories(include)

# Add project subdirectories:
if (BUILD_TUTORIALS)
	add_subdirectory(tutorials)
endif()
add_subdirectory(lib)
add_subdirectory(src)