#define GLEW_STATIC
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include <iostream>

#include "ShaderProgram.h"
using namespace Graphics;

ShaderProgram::ShaderProgram() {

}

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) {
	program = glCreateProgram();

	std::string vertSource;
	std::string fragSource;

	uint32_t type = GL_COMPUTE_SHADER; // default shader option TEMP
	toSource(vertexPath, &vertSource, &type);
	vertexId = compile(type, vertSource);
	glAttachShader(program, vertexId);

	toSource(fragmentPath, &fragSource, &type);
	fragmentId = compile(type, fragSource);
	glAttachShader(program, fragmentId);

	glLinkProgram(program);
	glValidateProgram(program);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(program);
}

void ShaderProgram::destroy() {
	glDetachShader(program, vertexId);
	glDetachShader(program, fragmentId);
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);

	glDeleteProgram(program);
}

void ShaderProgram::loadShader(const uint32_t _shaderType, const char* _shaderPath) {
	std::string shaderSourceCode;
	//toSource(_shaderPath, &shaderSourceCode, &_shaderType);
}

uint32_t ShaderProgram::getProgram() {
	return program;
}

void ShaderProgram::bind() const {
	glUseProgram(program);
}

void ShaderProgram::unbind() const {
	glUseProgram(0);
}

void ShaderProgram::toSource(const char* _path, std::string* shaderSource, uint32_t* _shaderType) {
	std::ifstream fileStream;
	fileStream.open(_path, std::ios::in);
	std::stringstream stream;

	//first checks if file can be opened
	if (fileStream.is_open()) {
		bool shaderTypeFound = false;
		std::string line;
		//reads line by line
		while (getline(fileStream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					*_shaderType = GL_VERTEX_SHADER;
				else if (line.find("fragment") != std::string::npos)
					*_shaderType = GL_FRAGMENT_SHADER;
				else if (line.find("geometry") != std::string::npos)
					*_shaderType = GL_GEOMETRY_SHADER;
				else if (line.find("compute") != std::string::npos)
					*_shaderType = GL_COMPUTE_SHADER;
				else
					std::cout << "Shader type " << line << "\nis not defined in: " << _path << std::endl;
				shaderTypeFound = true;
			}
			else {
				if (!shaderTypeFound)
					std::cout << "Shader type is not defined in: " << _path << std::endl;
				stream << line << "\n";
			}
		}
		//it merges the new file in string format to output string
		shaderSource->append(stream.str());
		fileStream.close();
	}
	else {
		std::cout << "File at " << _path << " \nwas not found." << std::endl;
	}
}

uint32_t ShaderProgram::compile(uint32_t _shaderType, std::string& _shaderSource) {
	//Shader source must be a string allocated in the heap
	unsigned int shaderId = glCreateShader(_shaderType);
	const char* src = &(_shaderSource.c_str())[0];
	glShaderSource(shaderId, 1, &src, nullptr);
	glCompileShader(shaderId);

	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int messageLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &messageLength);
		char* message = (char*)alloca(messageLength * sizeof(char));
		glGetShaderInfoLog(shaderId, messageLength, &messageLength, message);

		const char* shaderType = nullptr;
		switch (_shaderType) {
		case GL_VERTEX_SHADER:
			shaderType = "Vertex Shader";
			break;
		case GL_FRAGMENT_SHADER:
			shaderType = "Fragment Shader";
			break;
		case GL_COMPUTE_SHADER:
			shaderType = "Compute Shader";
			break;
		case GL_GEOMETRY_SHADER:
			shaderType = "Geometry Shader";
			break;
		}
		std::cout << "[Failed to compile shader] <type: " << shaderType << ">\n" << message << std::endl;
		glDeleteShader(shaderId);
		return 0;
	}
	return shaderId;
}
