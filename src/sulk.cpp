#include "include/sulk.h"

Sulk::Sulk()
{
    init();
    loop();
}

Sulk::~Sulk()
{
    cleanup();
}

bool Sulk::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, &availableLayers[0]);

    for (const char *layerName : validationLayers)
    {
        for (const auto &layerProp : availableLayers)
        {
            if (strcmp(layerName, layerProp.layerName) == 0) return true;
        }

        return false;
    }

    return true;
}

std::vector<const char *> Sulk::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void Sulk::createInstance()
{
    if (enableValidationLayers && !checkValidationLayerSupport())
    {
        throw std::runtime_error("Validation layers requested but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Sulk";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount = (uint32_t)(validationLayers.size());
        createInfo.ppEnabledLayerNames = &validationLayers[0];
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions = glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = (uint32_t)(extensions.size());
    createInfo.ppEnabledExtensionNames = &extensions[0];

    std::cout << "required extensions:\n";
    for (auto x : extensions)
    {
        std::cout << "\t" << x << "\n";
    }
}

void Sulk::init()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    win = glfwCreateWindow(WIDTH, HEIGHT, "Sulk", nullptr, nullptr);
    createInstance();
}

void Sulk::loop()
{
    while (!glfwWindowShouldClose(win))
    {
        glfwPollEvents();
    }
}

void Sulk::cleanup()
{
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(win);
    glfwTerminate();
}
