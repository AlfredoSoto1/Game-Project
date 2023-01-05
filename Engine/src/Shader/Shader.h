#pragma once

#define UR_CONTENT_API
#include "Engine.h"

#include <string>

namespace Uranium {
	class Shader {
	private:
		uint32 shaderId;

		void source_toString(const_string _path, std::string* shaderSource);

		uint32 compile(uint32 _shaderType, std::string& _shaderSource);

	public:
		Shader(uint32 _shaderType, const_string _path);
		virtual ~Shader();

		operator uint32() const;
	};
}