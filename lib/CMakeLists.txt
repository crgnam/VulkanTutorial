# Build the vulkan extension library:
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

find_package (PkgConfig)
pkg_get_variable (STB_INCLUDEDIR stb includedir)
if (NOT STB_INCLUDEDIR)
  unset (STB_INCLUDEDIR)
  find_path (STB_INCLUDEDIR stb_image.h PATH_SUFFIXES stb)
endif ()
if (NOT STB_INCLUDEDIR)
  message (FATAL_ERROR "stb_image.h not found")
endif ()

add_library(libvt STATIC
	hello.cpp
)

target_link_libraries(libvt glfw glm::glm Vulkan::Vulkan)
target_include_directories(libvt PRIVATE ${STB_INCLUDEDIR})


# include(GenerateExportHeader)
# generate_export_header(libvira 
#     EXPORT_FILE_NAME ${CMAKE_SOURCE_DIR}/include/vira/utils/libvira_export.hpp
# )


# Compile Shader code:
# This is taken directly from evilactually's GitHub Gist: 
# https://gist.github.com/evilactually/a0d191701cb48f157b05be7f74d79396'

if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
	set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
else()
	set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin32/glslangValidator.exe")
endif()

file(GLOB_RECURSE GLSL_SOURCE_FILES
	"${CMAKE_SOURCE_DIR}/shaders/vertex/*.vert"
	"${CMAKE_SOURCE_DIR}/shaders/fragment/*.frag"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
	get_filename_component(FILE_NAME ${GLSL} NAME)
	set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
	add_custom_command(
		OUTPUT ${SPIRV}
		COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
		COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
		DEPENDS ${GLSL})
	list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach()

add_custom_target(
	shaders
	DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(libvt shaders)
