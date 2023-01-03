#define GLEW_STATIC
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include <iostream>

#include "Utils/Maths/vec2.h"
#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"

#include "Utils/Maths/mat2.h"
#include "Utils/Maths/mat3.h"
#include "Utils/Maths/mat4.h"
using namespace MathsUtils;

#include "ShaderProgram.h"
using namespace Graphics;

ShaderProgram::ShaderProgram(const char* _computeShader_path) {
	program = glCreateProgram();

	compShader = createShader(GL_COMPUTE_SHADER, _computeShader_path);
	glLinkProgram(program);
	glValidateProgram(program);

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workGroupMaxCount[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workGroupMaxCount[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workGroupMaxCount[2]);

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workGroupMaxSize[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workGroupMaxSize[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workGroupMaxSize[2]);

	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workGroupInvocations);
}

ShaderProgram::ShaderProgram(const char* _vertexShader_path, const char* _fragmentShader_path) {
	program = glCreateProgram();

	vertShader = createShader(GL_VERTEX_SHADER, _vertexShader_path);
	fragShader = createShader(GL_FRAGMENT_SHADER, _fragmentShader_path);
	glLinkProgram(program);
	glValidateProgram(program);
}

ShaderProgram::ShaderProgram(const char* _geometryShader_path, const char* _vertexShader_path, const char* _fragmentShader_path) {
	program = glCreateProgram();
	
	vertShader = createShader(GL_VERTEX_SHADER, _vertexShader_path);
	geomShader = createShader(GL_GEOMETRY_SHADER, _geometryShader_path);
	fragShader = createShader(GL_FRAGMENT_SHADER, _fragmentShader_path);
	glLinkProgram(program);
	glValidateProgram(program);
}

ShaderProgram::~ShaderProgram() {
	if (compShader != 0) {
		glDetachShader(program, compShader);
		glDeleteShader(compShader);
	}
	if (vertShader != 0) {
		glDetachShader(program, vertShader);
		glDeleteShader(vertShader);
	}
	if (geomShader != 0) {
		glDetachShader(program, geomShader);
		glDeleteShader(geomShader);
	}
	if (fragShader != 0) {
		glDetachShader(program, fragShader);
		glDeleteShader(fragShader);
	}
	glDeleteProgram(program);

	uniformLocations.clear();
}

uint32_t ShaderProgram::createShader(uint32_t _shaderType, const char* _path) {
	uint32_t shaderId;
	std::string shaderSourceCode;
	source_toString(_path, &shaderSourceCode);
	shaderId = compile(_shaderType, shaderSourceCode);
	glAttachShader(program, shaderId);
	return shaderId;
} 

ShaderProgram::operator uint32_t() const {
	return program;
}

void ShaderProgram::bind() const {
	// start shader
	glUseProgram(program);
}

void ShaderProgram::unbind() const {
	// stop shader
	glUseProgram(0);
}

void ShaderProgram::dispatchCompute(uint32_t groupX, uint32_t groupY, uint32_t groupZ, uint32_t barrier) const {
	//GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT <-- barrier
	bind();
	glDispatchCompute(
		groupX > workGroupMaxCount[0] ? workGroupMaxCount[0] : groupX,
		groupY > workGroupMaxCount[1] ? workGroupMaxCount[1] : groupY,
		groupZ > workGroupMaxCount[2] ? workGroupMaxCount[2] : groupZ);
	glMemoryBarrier(barrier);
	unbind();
}

void ShaderProgram::source_toString(const char* _path, std::string* _shaderSource) {
	std::ifstream file;
	file.open(_path, std::ios::in);

	if (!file.is_open()) {
		std::cout << "File at \"" << _path << "\" \nwas not found." << std::endl;
		return;
	}

	std::string line;
	std::stringstream stream;
	while (getline(file, line))
		stream << line << "\n";

	_shaderSource->append(stream.str());
	file.close();
}

uint32_t ShaderProgram::compile(uint32_t _shaderType, std::string& _shaderSource) {

	// Create shader
	uint32_t shaderId = glCreateShader(_shaderType);
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
	std::cout << "[Failed to compile shader] <type: " << shaderType << ">\n" << message << std::endl;
	glDeleteShader(shaderId);

	return 0; // default shader bound ID (0) error
}

int32_t ShaderProgram::getUniformLocation(const std::string& _name) const {
	if (uniformLocations.find(_name) != uniformLocations.end())
		return uniformLocations[_name];
	int32_t location = glGetUniformLocation(program, _name.c_str());
	uniformLocations[_name] = location;
	return location;
}

void ShaderProgram::setFloat(const char* _name, const float& _value) const {
	glUniform1f(uniformLocations[_name], _value);
}

void ShaderProgram::setVec2(const char* _name, const MathsUtils::vec2& _vec2) const {
	glUniform2f(uniformLocations[_name], _vec2.x, _vec2.y);
}

void ShaderProgram::setVec3(const char* _name, const MathsUtils::vec3& _vec3) const {
	glUniform3f(uniformLocations[_name], _vec3.x, _vec3.y, _vec3.z);
}

void ShaderProgram::setVec4(const char* _name, const MathsUtils::vec4& _vec4) const {
	glUniform4f(uniformLocations[_name], _vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void ShaderProgram::setInt1(const char* _name, const int32_t& _value) const {
	glUniform1i(uniformLocations[_name], _value);
}

void ShaderProgram::setInt2(const char* _name, const int32_t& x, const int32_t& y) const {
	glUniform2i(uniformLocations[_name], x, y);
}

void ShaderProgram::setInt3(const char* _name, const int32_t& x, const int32_t& y, const uint32_t& z) const {
	glUniform3i(uniformLocations[_name], x, y, z);
}

void ShaderProgram::setInt4(const char* _name, const int32_t& x, const int32_t& y, const uint32_t& z, const uint32_t& w) const {
	glUniform4i(uniformLocations[_name], x, y, z, w);
}

void ShaderProgram::setMat2(const char* _name, mat2& _mat2) const {
	glUniformMatrix2fv(uniformLocations[_name], 1, GL_TRUE, _mat2);
}

void ShaderProgram::setMat3(const char* _name, mat3& _mat3) const {
	glUniformMatrix3fv(uniformLocations[_name], 1, GL_TRUE, _mat3);
}

void ShaderProgram::setMat4(const char* _name, mat4& _mat4) const {
	glUniformMatrix4fv(uniformLocations[_name], 1, GL_TRUE, _mat4);
}

void ShaderProgram::setFloat(int32_t _location, const float& _value) const {
	glUniform1f(_location, _value);
}

void ShaderProgram::setVec2(int32_t _location, const MathsUtils::vec2& _vec2) const {
	glUniform2f(_location, _vec2.x, _vec2.y);
}

void ShaderProgram::setVec3(int32_t _location, const MathsUtils::vec3& _vec3) const {
	glUniform3f(_location, _vec3.x, _vec3.y, _vec3.z);
}

void ShaderProgram::setVec4(int32_t _location, const MathsUtils::vec4& _vec4) const {
	glUniform4f(_location, _vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void ShaderProgram::setInt1(int32_t _location, const int32_t& _value) const {
	glUniform1i(_location, _value);
}

void ShaderProgram::setInt2(int32_t _location, const int32_t& x, const int32_t& y) const {
	glUniform2i(_location, x, y);
}

void ShaderProgram::setInt3(int32_t _location, const int32_t& x, const int32_t& y, const uint32_t& z) const {
	glUniform3i(_location, x, y, z);
}

void ShaderProgram::setInt4(int32_t _location, const int32_t& x, const int32_t& y, const uint32_t& z, const uint32_t& w) const {
	glUniform4i(_location, x, y, z, w);
}

void ShaderProgram::setMat2(int32_t _location, mat2& _mat2) const {
	glUniformMatrix2fv(_location, 1, GL_TRUE, _mat2);
}

void ShaderProgram::setMat3(int32_t _location, mat3& _mat3) const {
	glUniformMatrix3fv(_location, 1, GL_TRUE, _mat3);
}

void ShaderProgram::setMat4(int32_t _location, mat4& _mat4) const {
	glUniformMatrix4fv(_location, 1, GL_TRUE, _mat4);
}
