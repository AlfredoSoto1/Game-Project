#pragma once

typedef int Sampler2D;
typedef int Uniform;

typedef const char* const_string;

#ifdef UR_OPENGL
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#ifdef UR_GLFW
#include <GLFW/glfw3.h>
#endif

#ifdef UR_CONTENT_API

#define UR_API_EX extern

#define UR_link			friend class
#define UR_prototype	class
#define UR_namespace	namespace

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>

#endif
//
//#ifdef UR_MATHS_UTILS
//#include "Uranium/Utils/Maths/vec2.h"
//#include "Uranium/Utils/Maths/vec3.h"
//#include "Uranium/Utils/Maths/vec4.h"
//
//#include "Uranium/Utils/Maths/mat2.h"
//#include "Uranium/Utils/Maths/mat3.h"
//#include "Uranium/Utils/Maths/mat4.h"
//
//#include "Uranium/Utils/Maths/Constants.h"
//#include "Uranium/Utils/Maths/Operation.h"
//#endif 
//
//#ifdef UR_BUFFER_UTILS
//#include "Uranium/Utils/Buffers/IndexBuffer.h"
//#include "Uranium/Utils/Buffers/VertexBuffer.h"
//#include "Uranium/Utils/Buffers/ShaderStorageBuffer.h"
//#endif 
//
//#ifdef UR_GEOMETRY_UTILS
//#include "Uranium/Utils/Geometry/Mesh.h"
//#include "Uranium/Utils/Geometry/Model.h"
//#endif 
//
//#ifdef UR_MATERIALS_UTILS
//#include "Uranium/Utils/Materials/Texture.h"
//#include "Uranium/Utils/Materials/Material.h"
//#endif 
//
//#ifdef UR_SETTINGS
//#include "Uranium/Settings/WindowSettings.h"
//#include "Uranium/Settings/MouseSettings.h"
//#endif 
//
//#ifdef UR_RENDER_ENGINE_GRAPHICS
//#include "Uranium/RenderEngine/Graphics/Renderer.h"
//#endif 
//
//#ifdef UR_RENDER_ENGINE_SCENE
//#include "Uranium/RenderEngine/SceneControl/Scene.h"
//#include "Uranium/RenderEngine/SceneControl/Camera.h"
//#include "Uranium/RenderEngine/SceneControl/SceneManager.h"
//#endif 
//
////#ifdef UR_RENDER_ENGINE_SHADERS
//#include "Uranium/RenderEngine/ShaderControl/Shader.h"
//#include "Uranium/RenderEngine/ShaderControl/ShaderProgram.h"
//#include "Uranium/RenderEngine/ShaderControl/ComputeShader.h"
////#endif 

