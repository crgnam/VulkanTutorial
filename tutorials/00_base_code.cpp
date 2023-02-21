#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream> // Provides I/O
#include <stdexcept> // Provides exceptions for reporting and propagating errors
#include <cstdlib> // Provides EXIT_SUCCESS and EXIT_FAILURE macros
#include <cstddef>
#include <string>

class HelloTriangleApplication {
public:
    GLFWwindow* window;
    const uint32_t width;
    const uint32_t height;
    const std::string name;

    HelloTriangleApplication() : name{ "Vulkan Tutorial" }, width{ 800 }, height{ 600 } {};
    HelloTriangleApplication(std::string name) : name{ name }, width { 800 }, height{ 600 } {};
    HelloTriangleApplication(std::string name, uint32_t width, uint32_t height) : name{ name }, width { width }, height{ height } {};

    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow() {
        glfwInit(); // Initialize GLFW
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Do not use OpenGL
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Make window sized fixed

        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    }

    void initVulkan() {

    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}