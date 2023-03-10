# Move all of this to the libvt abstraction:
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


function (add_tutorial TUTORIAL_NAME)
	add_executable(${TUTORIAL_NAME} ${TUTORIAL_NAME}.cpp)
	#target_link_libraries(00_base_code PUBLIC libvt)  # Redo everything by abstracting to libvt library
	set_target_properties (${TUTORIAL_NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tutorials/${TUTORIAL_NAME})

	target_link_libraries(${TUTORIAL_NAME} glfw glm::glm Vulkan::Vulkan)
	target_include_directories (${TUTORIAL_NAME} PRIVATE ${STB_INCLUDEDIR})
endfunction()


## Add each tutorial series:
add_tutorial(00_base_code)
add_tutorial(01_instance)
add_tutorial(02_validation_layers)
add_tutorial(03_physical_devices)
add_tutorial(04_logical_device)
add_tutorial(05_window_surface)