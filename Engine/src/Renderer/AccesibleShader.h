#pragma once

#include <memory>
#include "UraniumApi.h"

namespace Uranium { 

	class ShaderProgram;

	interface AccesibleShader {
	protected:
		virtual void updateUniforms(std::shared_ptr<ShaderProgram> _shaderProgram) = 0;
	};
}