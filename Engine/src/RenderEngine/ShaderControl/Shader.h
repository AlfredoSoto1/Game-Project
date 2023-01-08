#pragma once

#define UR_CONTENT_API
#include "Engine.h"

#include <string>

namespace Uranium {
	class Shader {
	private:
		unsigned int shaderId;

		void source_toString(const_string _path, std::string* shaderSource);

		unsigned int compile(unsigned int _shaderType, std::string& _shaderSource);

	public:
		Shader(unsigned int _shaderType, const_string _path);
		virtual ~Shader();

		operator unsigned int() const;
	};
}