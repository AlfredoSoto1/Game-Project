#pragma once

#define UR_CONTENT_API
#include "Engine.h"

namespace Uranium {

	class Shader;
	class Renderer;

	class ShaderProgram { 
	private:
		friend class Renderer;

		unsigned int program;
		unsigned int compShader;
		unsigned int vertShader;
		unsigned int fragShader;

		int workGroupInvocations;

		int workGroupMaxSize[3];
		int workGroupMaxCount[3];

	public:
		ShaderProgram(const Shader& _compShader);
		ShaderProgram(const Shader& _vertShader, const Shader& _fragShader);

		virtual ~ShaderProgram();

		operator unsigned int() const;

		void bind() const;
		void unbind() const;

		void dispatchCompute(unsigned int _groupX, unsigned int _groupY, unsigned int _groupZ, unsigned int _barrier) const;
	};
}