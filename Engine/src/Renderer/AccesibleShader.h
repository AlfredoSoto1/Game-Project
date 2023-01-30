#pragma once

#include <memory>
#include "UraniumApi.h"

namespace Uranium { 

	class ShaderProgram;

	interface AccesibleShader {
	protected:
		virtual void bindUniforms(std::shared_ptr<ShaderProgram> _shader) = 0;
		virtual void preBindUniforms(std::shared_ptr<ShaderProgram> _shader) = 0;
	};
}