#include "ShaderProgram.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include <iostream>

using namespace Graphics;

ShaderProgram::ShaderProgram(unsigned int pathCount, const char** shaderPaths)
	: pathCount(pathCount)
{
	program = glCreateProgram();

	shaderIds = new unsigned int[pathCount];
	shaderSource = new std::string[pathCount];

	unsigned int type = GL_COMPUTE_SHADER;
	for (int i = 0; i < pathCount; i++) {
		parseShaderToSource(shaderPaths[i], &shaderSource[i], &type);
		if (shaderSource[i].length() != 0) {
			shaderIds[i] = compileShader(type, shaderSource[i]);
			glAttachShader(program, shaderIds[i]);
		}
	}

	if (pathCount == 0)
		return;

	glLinkProgram(program);
	glValidateProgram(program);
}

ShaderProgram::~ShaderProgram() {
	for (int i = 0; i < pathCount; i++) {
		if (shaderSource[i].length() != 0) {
			glDetachShader(program, shaderIds[i]);
			glDeleteShader(shaderIds[i]);
		}
	}
	glDeleteProgram(program);

	delete[] shaderIds;
	delete[] shaderSource;
}

void ShaderProgram::onProgram() {
	glUseProgram(program);
}

void ShaderProgram::offProgram() {
	glUseProgram(0);
}

ShaderProgram::operator unsigned int() {
	return program;
}

void ShaderProgram::parseShaderToSource(const char* shaderPath, std::string* shaderSource, unsigned int* type) {
	if (shaderPath == nullptr)
		return;//return if no other shader is being parsed

	std::ifstream fileStream;
	fileStream.open(shaderPath, std::ios::in);
	std::stringstream stream;

	//first checks if file can be opened
	if (fileStream.is_open()) {
		bool shaderTypeFound = false;
		std::string line;
		//reads line by line
		while (getline(fileStream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					*type = GL_VERTEX_SHADER;
				else if (line.find("fragment") != std::string::npos)
					*type = GL_FRAGMENT_SHADER;
				else if (line.find("geometry") != std::string::npos)
					*type = GL_GEOMETRY_SHADER;
				else if (line.find("compute") != std::string::npos)
					*type = GL_COMPUTE_SHADER;
				else
					std::cout << "Shader type " << line << "\nis not defined in: " << shaderPath << std::endl;
				shaderTypeFound = true;
			}
			else {
				if (!shaderTypeFound)
					std::cout << "Shader type is not defined in: " << shaderPath << std::endl;
				stream << line << "\n";
			}
		}
		//it merges the new file in string format to output string
		shaderSource->append(stream.str());
		fileStream.close();
	}
	else {
		std::cout << "File at " << shaderPath << " \nwas not found." << std::endl;
	}
}

unsigned int ShaderProgram::compileShader(unsigned int type, const std::string& shaderSource) {
	//Shader source must be a string allocated in the heap
	unsigned int shaderId = glCreateShader(type);
	const char* src = &(shaderSource.c_str())[0];
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
		switch (type) {
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