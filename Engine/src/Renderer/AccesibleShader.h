#pragma once

#include "UraniumApi.h"

namespace Uranium {

	struct mat2;
	struct mat3;
	struct mat4;

	struct vec2;
	struct vec3;
	struct vec4;

	class AccesibleShader {
	protected:
		virtual void staticUniforms(unsigned int _program) = 0;
		virtual void updateUniforms(unsigned int _program) = 0;

		Uniform getUniform(unsigned int _program, const char* _name) const;
		Sampler getSampler(unsigned int _program, const char* _name) const;

		void setSampler(const Sampler& _sampler, unsigned int _samplerId) const;

		void setMat2(Uniform _uniform, mat2& _mat2) const;
		void setMat3(Uniform _uniform, mat3& _mat3) const;
		void setMat4(Uniform _uniform, mat4& _mat4) const;

		void setVec2(Uniform _uniform, const vec2& _vec2) const;
		void setVec3(Uniform _uniform, const vec3& _vec3) const;
		void setVec4(Uniform _uniform, const vec4& _vec4) const;
	};
}