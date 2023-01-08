#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"
#include "UraniumApi.h"

#include "Utils/Maths/vec2.h"
#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"

#include "Utils/Maths/mat2.h"
#include "Utils/Maths/mat3.h"
#include "Utils/Maths/mat4.h"

#include "Renderer.h"
#include "Utils/Geometry/Model.h"
#include "Utils/Materials/Material.h"
#include "RenderEngine/ShaderControl/Shader.h"
#include "RenderEngine/ShaderControl/ShaderProgram.h"
using namespace Uranium;

Renderer::Renderer(const Shader& _vert, const Shader& _frag) {
	isWireframe = false;

	shader = new ShaderProgram(_vert, _frag);

	shader->bind();
	preProcessShader();
	shader->unbind();
}

Renderer::~Renderer() {
	delete shader;
}

void Renderer::showWireframe() {
	isWireframe = true;
}

void Renderer::hideWireframe() {
	isWireframe = false;
}

void Renderer::preProcessShader() {

}

void Renderer::draw(const Model& _model) {
	glEnable(GL_DEPTH_TEST);

	if (isWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, _model.getIndexCount(), GL_UNSIGNED_INT, nullptr);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glDrawElements(GL_TRIANGLES, _model.getIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

	glDisable(GL_DEPTH_TEST);
}

void Renderer::render(const Model& _model, const Material& _material) {
	// bind Shader Program
	glUseProgram(*shader);
	
	// update uniforms
	updateModifierUniforms();

	// render
	processShader(_model, _material);
}

Sampler2D Renderer::getSampler2D(const_string _name) const {
	return glGetUniformLocation(*shader, _name);
}

Uniform Renderer::getUniform(const_string _name) const {
	return glGetUniformLocation(*shader, _name);
}

void Renderer::bindSampler2D(const Sampler2D& _sampler, unsigned int _samplerId) const {
	if (_sampler < 0)
		return;
	glUniform1i(_sampler, _samplerId);
}

void Renderer::setVec2(Uniform _uniform, const vec2& _vec2) const {
	if (_uniform < 0)
		return;
	glUniform2f(_uniform, _vec2.x, _vec2.y);
}

void Renderer::setVec3(Uniform _uniform, const vec3& _vec3) const {
	if (_uniform < 0)
		return;
	glUniform3f(_uniform, _vec3.x, _vec3.y, _vec3.z);
}

void Renderer::setVec4(Uniform _uniform, const vec4& _vec4) const {
	if (_uniform < 0)
		return;
	glUniform4f(_uniform, _vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void Renderer::setMat2(Uniform _uniform, mat2& _mat2) const {
	if (_uniform < 0)
		return;
	glUniformMatrix2fv(_uniform, 1, GL_TRUE, _mat2);
}

void Renderer::setMat3(Uniform _uniform, mat3& _mat3) const {
	if (_uniform < 0)
		return;
	glUniformMatrix3fv(_uniform, 1, GL_TRUE, _mat3);
}

void Renderer::setMat4(Uniform _uniform, mat4& _mat4) const {
	if (_uniform < 0)
		return;
	glUniformMatrix4fv(_uniform, 1, GL_TRUE, _mat4);
}
