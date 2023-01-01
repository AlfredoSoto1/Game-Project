#define GLEW_STATIC
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include <iostream>

#include "ShaderProgram.h"
using namespace Graphics;

ShaderProgram::ShaderProgram(const char* _computePath) 
	: vertShader(0), fragShader(0), geomShader(0)
{
	program = glCreateProgram();

	compShader = loadShader(GL_COMPUTE_SHADER, _computePath);

	glLinkProgram(program);
	glValidateProgram(program);
}

ShaderProgram::ShaderProgram(const char* _vertexPath, const char* _fragmentPath) 
	: compShader(0), geomShader(0)
{
	program = glCreateProgram();

	vertShader = loadShader(GL_VERTEX_SHADER, _vertexPath);
	fragShader = loadShader(GL_FRAGMENT_SHADER, _fragmentPath);

	glLinkProgram(program);
	glValidateProgram(program);
}

ShaderProgram::ShaderProgram(const char* _vertexPath, const char* _geometryPath, const char* _fragmentPath) 
	: compShader(0)
{
	program = glCreateProgram();

	vertShader = loadShader(GL_VERTEX_SHADER, _vertexPath);
	geomShader = loadShader(GL_GEOMETRY_SHADER, _geometryPath);
	fragShader = loadShader(GL_FRAGMENT_SHADER, _fragmentPath);

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
	if (fragShader != 0) {
		glDetachShader(program, fragShader);
		glDeleteShader(fragShader);
	}
	if (geomShader != 0) {
		glDetachShader(program, geomShader);
		glDeleteShader(geomShader);
	}
	glDeleteProgram(program);
}

uint32_t ShaderProgram::loadShader(const uint32_t _shaderType, const char* _shaderPath) {
	std::string shaderSourceCode;								// Shader source code
	source_toString(_shaderPath, &shaderSourceCode);			// Get shader source code from path
	uint32_t shaderId = compile(_shaderType, shaderSourceCode); // Compile shader to get and ID
	glAttachShader(program, shaderId);							// Attaches shader to program
	return shaderId;
}

ShaderProgram::operator uint32_t() {
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

void ShaderProgram::source_toString(const char* _path, std::string* shaderSource) {
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

	shaderSource->append(stream.str());
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

	return 0; // default shader bound ID (0)
}
