# Vulkan-Tutorial
Working through the [Vulkan Tutorial](https://vulkan-tutorial.com/).

## File Structure:
- `tutorials/`: contains the source code as outlined by the Vulkan Tutorial series, with each source file (and compiled binary) being its own separate `cpp` taking on the same name as the tutorial chapter.
- `src/`: contains source code for a final version of viewport preview application
- `lib/`: contains the source code for my own abstraction API of the vulkan tutorial (`libvt`)
- `include/`: contains the headers for my own abstraction API of the vulkan tutorial

## Building Project:
### Requires:
- [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)
- [vcpkg](https://vcpkg.io/en/index.html) (for managing dependencies)
- [CMake](https://cmake.org/)
