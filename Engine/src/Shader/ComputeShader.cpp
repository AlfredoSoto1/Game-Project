#define GLEW_STATIC
#include <GL/glew.h>

#include "Shader.h"
#include "ComputeShader.h"

using namespace Uranium;

ComputeShader::ComputeShader(const char* _path) 
	: Shader(GL_COMPUTE_SHADER, _path)
{

}

ComputeShader::~ComputeShader() {

}