#include <vector>
#include <memory>
#include <string.h>
#include <cstdint>
#include <utility>
#include <functional>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <entt/entt.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <spdlog/spdlog.h>

#include "math/math.h"

#include "core/application.h"
#include "core/event.h"
#include "core/event_type.h"
#include "core/key_event.h"
#include "core/key_code.h"
#include "core/mouse_event.h"
#include "core/mouse_code.h"
#include "core/window_event.h"
#include "core/window.h"
#include "core/layer.h"
#include "core/layer_stack.h"
#include "core/timestep.h"

#include "core/asset_library.h"

#include "graphics/gpu_adapter.h"
#include "graphics/gpu_buffer.h"
#include "graphics/gpu_context.h"
#include "graphics/gpu_device.h"
#include "graphics/gpu_framebuffer.h"
#include "graphics/gpu_pixel_format.h"
#include "graphics/gpu_resource.h"
#include "graphics/gpu_resource_usage.h"
#include "graphics/gpu_shader.h"
#include "graphics/gpu_shader_program.h"
#include "graphics/gpu_shader_program_description.h"
#include "graphics/gpu_shader_program_stage.h"
#include "graphics/gpu_texture.h"
#include "graphics/gpu_texture_description.h"
#include "graphics/gpu_vertex_array.h"
#include "graphics/gpu_shader_uniform.h"

#include "platform/glfw/window_glfw.h"
#include "platform/imgui/layer_imgui.h"

#include "platform/opengl/gpu_buffer_opengl.h"
#include "platform/opengl/gpu_context_opengl.h"
#include "platform/opengl/gpu_device_opengl.h"
#include "platform/opengl/gpu_framebuffer_opengl.h"
#include "platform/opengl/gpu_shader_opengl.h"
#include "platform/opengl/gpu_shader_program_opengl.h"
#include "platform/opengl/gpu_texture_opengl.h"
#include "platform/opengl/gpu_vertex_array_opengl.h"
#include "platform/opengl/gpu_shader_uniform_opengl.h"

#include "render/ortographic_camera.h"
#include "render/material.h"
#include "render/renderer.h"
#include "render/camera.h"
#include "render/light.h"

#include "scene/components.h"
#include "scene/entity.h"
#include "scene/mesh.h"
#include "scene/scene.h"
#include "scene/model.h"
//#include "render/scene_camera.h"
//#include "render/scene_serializer.h"
