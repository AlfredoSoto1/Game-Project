#define GLEW_STATIC
#include <GL/glew.h>

#include "Renderer.h"
using namespace Render;

#include "Shader/ShaderProgram.h"
using namespace Graphics;

#include "Utils/Geometry/Model.h"
using namespace GeometryUtils;

#include "Textures/Texture.h"
using namespace Graphics;

Texture* texture;

Renderer::Renderer() {
	isWireframe = false;

	texture = new Texture("src/Texture.png");
}

Renderer::~Renderer() {
	delete texture;
}

void Renderer::showWireframe() {
	isWireframe = true;
}

void Renderer::hideWireframe() {
	isWireframe = false;
}

void Renderer::render(const Model& _model, const ShaderProgram& _shader) {
	_shader.bind();
	_shader.update();
	_model.bind();
	_model.enableAttribs();

	texture->bind(0);

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
	
	texture->unbind();

	_model.disableAttribs();
	_model.unbind();
	_shader.unbind();
}