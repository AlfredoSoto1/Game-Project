#pragma once

#include <string>
#include <cstdint>

namespace Graphics {

	class ShaderProgram { 
	private:
		uint32_t program;

		uint32_t compShader;
		uint32_t vertShader;
		uint32_t fragShader;
		uint32_t geomShader;

		void source_toString(const char* _path, std::string* shaderSource);

		uint32_t compile(uint32_t _shaderType, std::string& _shaderSource);
		uint32_t loadShader(const uint32_t _shaderType, const char* _shaderPath);

	protected:
		virtual void init() = 0;
		virtual void load() = 0;
		virtual void dispose() = 0;

	public:
		ShaderProgram(const char* _computePath);
		ShaderProgram(const char* _vertexPath, const char* _fragmentPath);
		ShaderProgram(const char* _vertexPath, const char* _geometryPath, const char* fragmentPath);

		virtual ~ShaderProgram();

		operator uint32_t();

		void bind() const;
		void unbind() const;

	};
}