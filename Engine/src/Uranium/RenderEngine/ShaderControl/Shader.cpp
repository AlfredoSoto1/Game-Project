#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <malloc.h>
#include <iostream>

using namespace Uranium;

Shader::Shader(unsigned int _shaderType, const_string _path) {
	std::string shaderSourceCode;

	// make source to string
	source_toString(_path, &shaderSourceCode);

	// create and compile
	shaderId = compile(_shaderType, shaderSourceCode);
}

Shader::~Shader() {

}

Shader::operator unsigned int() const {
	return shaderId;
}

void Shader::source_toString(const_string _path, std::string* _shaderSource) {
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

unsigned int Shader::compile(unsigned int _shaderType, std::string& _shaderSource) {

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
	std::cout << "[Failed to compile shader] <type: " << shaderType << ">\n" << message << std::endl;
	glDeleteShader(shaderId);

	return 0; // default shader bound ID (0) error
}