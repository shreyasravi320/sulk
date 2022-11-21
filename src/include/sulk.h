#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>

const uint32_t WIDTH = 1920;
const uint32_t HEIGHT = 1080;

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#if NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

class Sulk
{
public:
    Sulk();
    ~Sulk();

private:
    void init();
    void loop();
    void cleanup();

    void createInstance();
    std::vector<const char *> getRequiredExtensions();
    bool checkValidationLayerSupport();

    GLFWwindow *win;
    VkInstance instance;
};
