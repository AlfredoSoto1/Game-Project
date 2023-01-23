#pragma once

#include <string>

namespace Uranium {

	class Shader {
	public:
		Shader(const std::string& _shaderFilePath, unsigned int _shaderType);
		virtual ~Shader();

		operator unsigned int();

		unsigned int getShaderType();

	private:
		std::string filePath;

		unsigned int shaderId;
		unsigned int shaderType;

		void fileToSourceString(const std::string& _path, std::string* _shaderSource);
		unsigned int compile(const std::string& _shaderSource, unsigned int _shaderType);
	};
}
