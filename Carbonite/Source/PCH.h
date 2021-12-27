#pragma once

#include "Utils/Core.h"

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#if CARBONITE_IS_TOOLSET_MSVC
#pragma warning(push)
#pragma warning(disable : 4201)
#endif

#include <glm/gtx/quaternion.hpp>

#if CARBONITE_IS_TOOLSET_MSVC
#pragma warning(pop)
#endif

#include <spdlog/spdlog.h>
#include <stb_image.h>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan.hpp>

#include <GLFW/glfw3.h>

#include <glslang/Include/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>

#include <cstdint>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <vector>