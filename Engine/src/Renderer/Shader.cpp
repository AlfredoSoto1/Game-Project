#include "Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>

#define CATCH_OPENGL_ERROR
#include "UraniumApi.h"

#include <fstream>
#include <sstream>
#include <malloc.h>
#include <memory>

using namespace Uranium;

Shader::Shader(const std::string& _path, unsigned int _shaderType) {
	std::string shaderSource; // temp source
	fileToSourceString(_path, &shaderSource);
	shaderId = compile(shaderSource, _shaderType);
}

Shader::~Shader() {
	glDeleteShader(shaderId);
}

Shader::operator unsigned int() {
	return shaderId;
}

unsigned int Shader::getShaderType() {
	return shaderType;
}

void Shader::fileToSourceString(const std::string& _path, std::string* _shaderSource) {
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

unsigned int Shader::compile(const std::string& _shaderSource, unsigned int _shaderType) {
	// create shader
	GLuint shaderId = glCreateShader(_shaderType);
	const char* src = &(_shaderSource.c_str())[0];
	glShaderSource(shaderId, 1, &src, nullptr);

	glCompileShader(shaderId); // compile shader

	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result); // check if shader compiled successfully

	if (result != GL_FALSE)
		return shaderId;

	// Display compilation error of shader type

	GLint messageLength;
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
