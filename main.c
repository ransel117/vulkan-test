#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

#include <vulkan/vulkan.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

static inline const char* string_VkResult(VkResult input_value) {
    switch (input_value) {
        case VK_SUCCESS:
            return "VK_SUCCESS";
        case VK_NOT_READY:
            return "VK_NOT_READY";
        case VK_TIMEOUT:
            return "VK_TIMEOUT";
        case VK_EVENT_SET:
            return "VK_EVENT_SET";
        case VK_EVENT_RESET:
            return "VK_EVENT_RESET";
        case VK_INCOMPLETE:
            return "VK_INCOMPLETE";
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return "VK_ERROR_OUT_OF_HOST_MEMORY";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
        case VK_ERROR_INITIALIZATION_FAILED:
            return "VK_ERROR_INITIALIZATION_FAILED";
        case VK_ERROR_DEVICE_LOST:
            return "VK_ERROR_DEVICE_LOST";
        case VK_ERROR_MEMORY_MAP_FAILED:
            return "VK_ERROR_MEMORY_MAP_FAILED";
        case VK_ERROR_LAYER_NOT_PRESENT:
            return "VK_ERROR_LAYER_NOT_PRESENT";
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            return "VK_ERROR_EXTENSION_NOT_PRESENT";
        case VK_ERROR_FEATURE_NOT_PRESENT:
            return "VK_ERROR_FEATURE_NOT_PRESENT";
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            return "VK_ERROR_INCOMPATIBLE_DRIVER";
        case VK_ERROR_TOO_MANY_OBJECTS:
            return "VK_ERROR_TOO_MANY_OBJECTS";
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
            return "VK_ERROR_FORMAT_NOT_SUPPORTED";
        case VK_ERROR_FRAGMENTED_POOL:
            return "VK_ERROR_FRAGMENTED_POOL";
        case VK_ERROR_UNKNOWN:
            return "VK_ERROR_UNKNOWN";
        case VK_ERROR_OUT_OF_POOL_MEMORY:
            return "VK_ERROR_OUT_OF_POOL_MEMORY";
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
            return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
        case VK_ERROR_FRAGMENTATION:
            return "VK_ERROR_FRAGMENTATION";
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
            return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
        case VK_PIPELINE_COMPILE_REQUIRED:
            return "VK_PIPELINE_COMPILE_REQUIRED";
        case VK_ERROR_SURFACE_LOST_KHR:
            return "VK_ERROR_SURFACE_LOST_KHR";
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
        case VK_SUBOPTIMAL_KHR:
            return "VK_SUBOPTIMAL_KHR";
        case VK_ERROR_OUT_OF_DATE_KHR:
            return "VK_ERROR_OUT_OF_DATE_KHR";
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
        case VK_ERROR_VALIDATION_FAILED_EXT:
            return "VK_ERROR_VALIDATION_FAILED_EXT";
        case VK_ERROR_INVALID_SHADER_NV:
            return "VK_ERROR_INVALID_SHADER_NV";
        case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:
            return "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR";
        case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:
            return "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR";
        case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:
            return "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR";
        case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:
            return "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR";
        case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:
            return "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR";
        case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:
            return "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR";
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
            return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
        case VK_ERROR_NOT_PERMITTED_KHR:
            return "VK_ERROR_NOT_PERMITTED_KHR";
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
            return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
        case VK_THREAD_IDLE_KHR:
            return "VK_THREAD_IDLE_KHR";
        case VK_THREAD_DONE_KHR:
            return "VK_THREAD_DONE_KHR";
        case VK_OPERATION_DEFERRED_KHR:
            return "VK_OPERATION_DEFERRED_KHR";
        case VK_OPERATION_NOT_DEFERRED_KHR:
            return "VK_OPERATION_NOT_DEFERRED_KHR";
#ifdef VK_ENABLE_BETA_EXTENSIONS
        case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:
            return "VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR";
#endif //VK_ENABLE_BETA_EXTENSIONS
        case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
            return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
        case VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT:
            return "VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT";
        default:
            return "Unhandled VkResult";
    }
}

typedef struct app_info_t app_info;

struct app_info_t {
    SDL_Window *window;

    VkInstance instance;
    bool use_validation_layer;

    VkDebugUtilsMessengerEXT dbg_msger;

    char *title;
    uint32_t width, height;
};

#define APP_ERR_EXIT(...) do {fprintf(stderr, __VA_ARGS__); exit(1);} while (0);
#define APP_ERR_RET(R, ...) do {fprintf(stderr, __VA_ARGS__); return (R);} while (0);

static bool quit = false;

VkResult app_create_dbg_utils_msger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* info, const VkAllocationCallbacks* allocator, VkDebugUtilsMessengerEXT* dbg_msger) {
    PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    return (func) ? func(instance, info, allocator, dbg_msger) : VK_ERROR_EXTENSION_NOT_PRESENT;

}

void app_destroy_dbg_utils_msger(VkInstance instance, VkDebugUtilsMessengerEXT dbg_msger, const VkAllocationCallbacks* allocator) {
    PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func) {
        func(instance, dbg_msger, allocator);
    }
}

static VKAPI_ATTR VkBool32 VKAPI_CALL app_dbg_callback(VkDebugUtilsMessageSeverityFlagBitsEXT mgs_sev, VkDebugUtilsMessageTypeFlagsEXT msg_type, const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data) {
    APP_ERR_RET(VK_FALSE, "validation layer: %s\n", callback_data->pMessage);
}

void app_populate_dbg_msger(VkDebugUtilsMessengerCreateInfoEXT *info) {
    info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    info->pNext = NULL;
    info->flags = 0;
    info->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    info->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    info->pfnUserCallback = app_dbg_callback;
    info->pUserData = NULL;
}

void app_init_window(app_info *ai) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        APP_ERR_EXIT("could not init SDL: %s\n", SDL_GetError());
    }

    ai->window = SDL_CreateWindow(ai->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  ai->width, ai->height, SDL_WINDOW_VULKAN);
    if (!ai->window) {
        APP_ERR_EXIT("could not create window: %s\n", SDL_GetError());
    }
}
void app_init_vulkan(app_info *ai) {
    uint32_t layer_count, extensions_count;
    const char *validation_layers_name;

    validation_layers_name = "VK_LAYER_KHRONOS_validation";

    vkEnumerateInstanceLayerProperties(&layer_count, NULL);

    VkLayerProperties available_layers[layer_count];
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers);

    ai->use_validation_layer = false;
    for (size_t i = 0; i < layer_count; ++i) {
        if (strcmp(validation_layers_name, available_layers[i].layerName) == 0) {
            ai->use_validation_layer = true;
            break;
        }
    }

    if (!SDL_Vulkan_GetInstanceExtensions(ai->window, &extensions_count, NULL)) {
        APP_ERR_EXIT("could not get required extension count: %s\n", SDL_GetError());
    }

    const char* required_extensions[extensions_count + 1];
    if (!SDL_Vulkan_GetInstanceExtensions(ai->window, &extensions_count, (const char**)required_extensions)) {
        APP_ERR_EXIT("could not get required extensions: %s\n", SDL_GetError());
    }

    if (ai->use_validation_layer) {
        required_extensions[extensions_count++] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    }

    VkApplicationInfo vk_app_info;
    vk_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vk_app_info.pNext = NULL;
    vk_app_info.pApplicationName = ai->title;
    vk_app_info.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
    vk_app_info.pEngineName = "no engine";
    vk_app_info.engineVersion = VK_MAKE_VERSION(0, 0, 0);
    vk_app_info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo vk_create_info;
    vk_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vk_create_info.flags = 0;
    vk_create_info.pApplicationInfo = &vk_app_info;

    VkDebugUtilsMessengerCreateInfoEXT vk_dbg_info;
    if (ai->use_validation_layer) {
        app_populate_dbg_msger(&vk_dbg_info);
        vk_create_info.pNext = &vk_dbg_info;
        vk_create_info.enabledLayerCount = 1;
        vk_create_info.ppEnabledLayerNames = &validation_layers_name;
    } else {
        vk_create_info.pNext = NULL;
        vk_create_info.enabledLayerCount = 0;
        vk_create_info.ppEnabledLayerNames = NULL;
    }

    vk_create_info.enabledExtensionCount = extensions_count;
    vk_create_info.ppEnabledExtensionNames = required_extensions;

    VkResult result;
    result = vkCreateInstance(&vk_create_info, NULL, &ai->instance);

    if (result != VK_SUCCESS) {
        APP_ERR_EXIT("could not create vulkan instance: result: %d -> %s\n", result, string_VkResult(result));
    }
    if (ai->use_validation_layer) {
        app_populate_dbg_msger(&vk_dbg_info);

        result = app_create_dbg_utils_msger(ai->instance, &vk_dbg_info, NULL, &ai->dbg_msger);

        if (result != VK_SUCCESS) {
            APP_ERR_EXIT("could setup debug msger: result: %d -> %s\n", result, string_VkResult(result));
        }
    }
}

void app_init_graphics(app_info *ai) {
    app_init_window(ai);
    app_init_vulkan(ai);
}

void app_quit(app_info *ai) {
    if (ai->use_validation_layer) {
        app_destroy_dbg_utils_msger(ai->instance, ai->dbg_msger, NULL);
    }
    vkDestroyInstance(ai->instance, NULL);

    SDL_DestroyWindow(ai->window);
    SDL_Quit();
}

int main(void) {
    app_info app;

    app.width = 800;
    app.height = 600;
    app.title = "test";

    app_init_graphics(&app);

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
            }
        }
    }

    app_quit(&app);

    return 0;
}
