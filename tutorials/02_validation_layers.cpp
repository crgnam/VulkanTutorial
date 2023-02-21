#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream> // Provides I/O
#include <stdexcept> // Provides exceptions for reporting and propagating errors
#include <cstdlib> // Provides EXIT_SUCCESS and EXIT_FAILURE macros
#include <cstddef>
#include <string>
#include <vector>

class HelloTriangleApplication {
public:
    GLFWwindow* window;
    const uint32_t width;
    const uint32_t height;
    const std::string name;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif

    HelloTriangleApplication() : name{ "Vulkan Tutorial" }, width{ 800 }, height{ 600 } {};
    HelloTriangleApplication(std::string name) : name{ name }, width{ 800 }, height{ 600 } {};
    HelloTriangleApplication(std::string name, uint32_t width, uint32_t height) : name{ name }, width{ width }, height{ height } {};

    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    VkInstance instance;

    void initWindow() {
        glfwInit(); // Initialize GLFW
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Do not use OpenGL
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Make window sized fixed

        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    }

    void createInstance() {
        // Creates and sets members of VkApplicationInfo struct:
        VkApplicationInfo appInfo{};

        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;


        // Creates and sets members of VkInstanceCreateInfo strucT:
        VkInstanceCreateInfo createInfo{};

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        // object creation function parameters in Vulkan follow is:
        //  - Pointer to struct with creation info
        //  - Pointer to custom allocator callbacks, always nullptr in this tutorial
        //  - Pointer to the variable that stores the handle to the new object
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    }

    void initVulkan() {
        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);

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