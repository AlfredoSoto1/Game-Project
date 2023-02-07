#pragma once

#include "UraniumApi.h"
#include <memory>

namespace Uranium {

	class ShaderProgram;

	interface ShaderProcessor {
	public:
		virtual void processShaderInstructions(std::shared_ptr<ShaderProgram> _shader) = 0;
	};
}