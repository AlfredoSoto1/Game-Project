#define GLEW_STATIC
#include <GL/glew.h>

#include "ModelRenderer.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "Scene/Camera.h"
#include "Utils/Geometry/Model.h"

using namespace Uranium;

ModelRenderer::ModelRenderer(ShaderProgram* _shader)
	: shader(_shader)
{
	isWireframe = false;

	shader->bind();
	shader->initStaticUniforms();
	shader->unbind();
}

ModelRenderer::~ModelRenderer() {

}

void ModelRenderer::showWireframe() {
	isWireframe = true;
}

void ModelRenderer::hideWireframe() {
	isWireframe = false;
}

void ModelRenderer::technicalRender(const Model& _model, const Material& _material) {
	_model.bind();
	_model.enableAttribs();

	_material.bind();

	glEnable(GL_DEPTH_TEST);

	draw(_model.getIndexCount(), GL_UNSIGNED_INT);

	glDisable(GL_DEPTH_TEST);

	_model.unbind();
	_model.disableAttribs();
}

void ModelRenderer::draw(unsigned int _indexCount, unsigned int _indexType) {
	if (isWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, _indexCount, _indexType, nullptr);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glDrawElements(GL_TRIANGLES, _indexCount, _indexType, nullptr);
	}
}

void ModelRenderer::render(Camera* _camera, const Model& _model, const Material& _material) {
	shader->bind();
	shader->updateUniforms(_camera);
	technicalRender(_model, _material);
	shader->unbind();
}