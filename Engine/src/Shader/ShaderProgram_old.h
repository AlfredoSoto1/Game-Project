#pragma once

#include <string>

namespace Graphics {

	class ShaderProgram {
	private:
		unsigned int program;
		unsigned int pathCount;
		unsigned int* shaderIds;

		std::string* shaderSource;

		unsigned int compileShader(unsigned int type, const std::string& source);
		void parseShaderToSource(const char* shaderPath, std::string* shaderSource, unsigned int* type);

	public:
		ShaderProgram(unsigned int pathCount, const char** shaderPaths);
		~ShaderProgram();

		void onProgram();
		void offProgram();

		operator unsigned int();

	};
}