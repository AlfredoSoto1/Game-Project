#define GLEW_STATIC
#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <malloc.h>
#include <memory>

#include "Utils/Maths/vec2.h"
#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"

#include "Utils/Maths/mat2.h"
#include "Utils/Maths/mat3.h"
#include "Utils/Maths/mat4.h"

#define CATCH_OPENGL_ERROR
#include "UraniumApi.h"
#include "ShaderProgram.h"
#include "Texture.h"

using namespace Uranium;

//ShaderProgram::ShaderProgram(const Shader& _compShader) 
//	: vertShader(0), fragShader(0)
//{
//	program = glCreateProgram();
//	
//	glAttachShader(program, _compShader);
//	compShader = _compShader;
//
//	glLinkProgram(program);
//	glValidateProgram(program);
//
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workGroupMaxCount[0]);
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workGroupMaxCount[1]);
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workGroupMaxCount[2]);
//
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workGroupMaxSize[0]);
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workGroupMaxSize[1]);
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workGroupMaxSize[2]);
//
//	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workGroupInvocations);
//}

ShaderProgram::ShaderProgram(const char* _vertexPath, const char* _fragmentPath)
	: compShader(0)
{
	// create shader program
	program = glCreateProgram();

	// create individual shaders
	vertShader = createShader(GL_VERTEX_SHADER, _vertexPath);
	fragShader = createShader(GL_FRAGMENT_SHADER, _fragmentPath);

	// link and validate program
	glLinkProgram(program);
	glValidateProgram(program);

	// get uniform name and Id
	retrieveUniforms();
}

ShaderProgram::~ShaderProgram() {
	// detach /delete shaders
	if (compShader != 0) {
		glDetachShader(program, compShader);
		glDeleteShader(compShader);
	}
	if (vertShader != 0) {
		glDetachShader(program, vertShader);
		glDeleteShader(vertShader);
	}
	if (fragShader != 0) {
		glDetachShader(program, fragShader);
		glDeleteShader(fragShader);
	}

	// delete shader program
	glDeleteProgram(program);
}

ShaderProgram::operator unsigned int() const {
	return program;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getUniformFlags() {
	return uniformFlags;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getUniformSamplers() {
	return uniformSamplers;
}

void ShaderProgram::bind() const {
	glUseProgram(program);
}

void ShaderProgram::unbind() const {
	glUseProgram(0);
}
//
//void ShaderProgram::dispatchCompute(unsigned int _groupX, unsigned int _groupY, unsigned int _groupZ, unsigned int _barrier) const {
//	//GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT <-- barrier
//	bind();
//	glDispatchCompute(
//		_groupX > workGroupMaxCount[0] ? workGroupMaxCount[0] : _groupX,
//		_groupY > workGroupMaxCount[1] ? workGroupMaxCount[1] : _groupY,
//		_groupZ > workGroupMaxCount[2] ? workGroupMaxCount[2] : _groupZ);
//	glMemoryBarrier(_barrier);
//	unbind();
//}

unsigned int ShaderProgram::createShader(unsigned int _shaderType, const char* _path) {
	std::string shaderSourceCode;
	sourceToString(_path, &shaderSourceCode);
	unsigned int shaderId = compile(_shaderType, shaderSourceCode);
	glAttachShader(program, shaderId);
	return shaderId;
}

void ShaderProgram::sourceToString(const char* _path, std::string* _shaderSource) {
	std::ifstream file;
	file.open(_path, std::ios::in);

	if (!file.is_open()) {
		print_status("File at \"" << _path << "\" \nwas not found.");
		return;
	}

	std::string line;
	std::stringstream stream;
	while (getline(file, line))
		stream << line << "\n";

	_shaderSource->append(stream.str());
	file.close();
}

unsigned int ShaderProgram::compile(unsigned int _shaderType, std::string& _shaderSource) {

	// Create shader
	unsigned int shaderId = glCreateShader(_shaderType);
	const char* src = &(_shaderSource.c_str())[0];
	glShaderSource(shaderId, 1, &src, nullptr);

	// Compile shader
	glCompileShader(shaderId);

	// Check shader compile error
	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (result != GL_FALSE)
		return shaderId;

	// Display compilation error of shader type

	int messageLength;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &messageLength);

	char* message = (char*)alloca(messageLength * sizeof(char));
	glGetShaderInfoLog(shaderId, messageLength, &messageLength, message);

	const char* shaderType = nullptr;
	switch (_shaderType) {
	case GL_VERTEX_SHADER:
		shaderType = "Vertex Shader";	break;
	case GL_FRAGMENT_SHADER:
		shaderType = "Fragment Shader";	break;
	case GL_COMPUTE_SHADER:
		shaderType = "Compute Shader";	break;
	case GL_GEOMETRY_SHADER:
		shaderType = "Geometry Shader";	break;
	}
	throw_error(true, "[Failed to compile shader] <type: " << shaderType << ">\n" << message);
	glDeleteShader(shaderId);

	return 0; // default shader bound ID (0) error
}

void ShaderProgram::retrieveUniforms() {

	// get current active uniforms
	int uniformCount;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount);

	// gets max length of uniform name in program
	int maxCharLength;
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxCharLength);

	char* name = (char*)alloca(maxCharLength * sizeof(char));
	int size;
	int length;
	unsigned int type;

	bind();
	// get uniform location, uniform name and type
	for (int i = 0; i < uniformCount; i++) {
		glGetActiveUniform(program, (unsigned int)i, maxCharLength, &length, &size, &type, name);
		if (type == GL_SAMPLER_2D) {
			uniformSamplers[name] = { glGetUniformLocation(program, name), type };
		}
		else {
			uniformFlags[name] = { glGetUniformLocation(program, name), type };
		}
	}
	unbind();
}

void ShaderProgram::setAlbedoSampler(std::shared_ptr<Texture> _texture) {

}

void ShaderProgram::setSampler(const Sampler& _sampler, unsigned int _samplerId) const {
	glUniform1i(_sampler, _samplerId);
}

void ShaderProgram::setVec2(Uniform _uniform, const vec2& _vec2) const {
	glUniform2f(_uniform, _vec2.x, _vec2.y);
}

void ShaderProgram::setVec3(Uniform _uniform, const vec3& _vec3) const {
	glUniform3f(_uniform, _vec3.x, _vec3.y, _vec3.z);
}

void ShaderProgram::setVec4(Uniform _uniform, const vec4& _vec4) const {
	glUniform4f(_uniform, _vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void ShaderProgram::setMat2(Uniform _uniform, mat2& _mat2) const {
	glUniformMatrix2fv(_uniform, 1, GL_TRUE, _mat2);
}

void ShaderProgram::setMat3(Uniform _uniform, mat3& _mat3) const {
	glUniformMatrix3fv(_uniform, 1, GL_TRUE, _mat3);
}

void ShaderProgram::setMat4(Uniform _uniform, mat4& _mat4) const {
	glUniformMatrix4fv(_uniform, 1, GL_TRUE, _mat4);
}
