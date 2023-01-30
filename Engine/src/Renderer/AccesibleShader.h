#pragma once

#include <memory>
#include "UraniumApi.h"

namespace Uranium { 

	class ShaderProgram;

	interface AccesibleShader {
	protected:
		virtual void bindToShader(std::shared_ptr<ShaderProgram> _shader) = 0;

	};
}