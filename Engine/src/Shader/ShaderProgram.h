#pragma once

#define UR_CONTENT_API
#include "Engine.h"

namespace Uranium {

	class Shader;
	class Renderer;

	class ShaderProgram { 
	private:
		friend class Renderer;

		uint32 program;
		uint32 compShader;
		uint32 vertShader;
		uint32 fragShader;

		int32 workGroupInvocations;

		int32 workGroupMaxSize[3];
		int32 workGroupMaxCount[3];

	public:
		ShaderProgram(const Shader& _compShader);
		ShaderProgram(const Shader& _vertShader, const Shader& _fragShader);

		virtual ~ShaderProgram();

		operator uint32() const;

		void bind() const;
		void unbind() const;

		void dispatchCompute(uint32 groupX, uint32 groupY, uint32 groupZ, uint32 barrier) const;
	};
}