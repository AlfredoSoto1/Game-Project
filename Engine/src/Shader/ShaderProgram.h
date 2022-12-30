#pragma once

#include <cstdint>
#include <string>

namespace Graphics {

	class ShaderProgram {
	private:
		uint32_t vertexId;
		uint32_t fragmentId;

		uint32_t program;

		void toSource(const char* _path, std::string* shaderSource, uint32_t* _shaderType);

		uint32_t compile(uint32_t _shaderType, std::string& _shaderSource);

	protected:
		virtual void init() = 0;
		virtual void load() = 0;
		virtual void dispose() = 0;

	public:
		ShaderProgram(const char* vertexPath, const char* fragmentPath);
		~ShaderProgram();

		uint32_t getProgram();

		void bind();
		void unbind();

		void destroy();
	};
}