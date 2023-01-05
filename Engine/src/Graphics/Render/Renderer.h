#pragma once

#define UR_CONTENT_API
#include "Engine.h"

namespace Uranium {
	struct vec2;
	struct vec3;
	struct vec4;

	struct mat2;
	struct mat3;
	struct mat4;

	class Model;
	class Shader;
	class Material;
	class ShaderProgram;

	class Renderer {
	private:
		ShaderProgram* shader;

		bool isWireframe;

	protected:
		virtual void updateModifierUniforms() = 0;
		virtual void processShader(const Model& _model, const Material& _material) = 0;

		virtual void preProcessShader();

		void draw(const Model& _model);

		void showWireframe();
		void hideWireframe();

		Uniform getUniform(const_string _name) const;
		Sampler2D getSampler2D(const_string _name) const;

		void bindSampler2D(const Sampler2D& _sampler, uint32 _samplerId) const;

		void setVec2(Uniform _uniform, const vec2& _vec2) const;
		void setVec3(Uniform _uniform, const vec3& _vec3) const;
		void setVec4(Uniform _uniform, const vec4& _vec4) const;

		void setMat2(Uniform _uniform, mat2& _mat2) const;
		void setMat3(Uniform _uniform, mat3& _mat3) const;
		void setMat4(Uniform _uniform, mat4& _mat4) const;

	public:
		Renderer(const Shader& _vert, const Shader& _frag);
		virtual ~Renderer();

		void render(const Model& _model, const Material& _material);
	};
}
