#pragma once

#include "UraniumApi.h"

namespace Uranium {

	struct vec2;
	struct vec3;
	struct vec4;

	struct mat2;
	struct mat3;
	struct mat4;

	class Camera;

	class ShaderProgram {
	public:
		ShaderProgram(const char* _vertexPath, const char* _fragmentPath);
		virtual ~ShaderProgram();

		operator unsigned int() const;

		void bind() const;
		void unbind() const;

	protected:
		virtual void updateUniforms(Camera* _camera) = 0;
		virtual void initStaticUniforms() = 0;
		
		void dispatchCompute(unsigned int _groupX, unsigned int _groupY, unsigned int _groupZ, unsigned int _barrier) const;

	private:
		friend class ModelRenderer;
		friend class BatchRenderer;

		unsigned int program;
		unsigned int compShader;
		unsigned int vertShader;
		unsigned int fragShader;

		int workGroupInvocations;

		int workGroupMaxSize[3];
		int workGroupMaxCount[3];

		void source_toString(const char* _path, std::string* shaderSource);

		unsigned int compile(unsigned int _shaderType, std::string& _shaderSource);
		unsigned int createShader(unsigned int _shaderType, const char* _path);
	};
}