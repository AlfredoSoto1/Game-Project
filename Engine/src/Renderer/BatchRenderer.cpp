#define GLEW_STATIC
#include <GL/glew.h>

#include "BatchRenderer.h"

#include <vector>
#include <unordered_map>

#include "Scene/Entity.h"
#include "Scene/Camera.h"
#include "Utils/Geometry/Model.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture.h"
#include "Renderer/Material.h"

using namespace Uranium;

BatchRenderer::BatchRenderer(ShaderProgram* _shader)
	: shader(_shader)
{
	isWireframe = false;

	entityBatch.reserve(2);


	texture = new Texture("src/Texture.png");


	shader->bind();
	shader->initStaticUniforms();
	shader->unbind();
}

BatchRenderer::~BatchRenderer() {
	delete texture;

	entityBatch.clear();
}

void BatchRenderer::submit(const Entity&& _entity) {
	entityBatch[_entity.getModel()].emplace_back(_entity);
}

void BatchRenderer::render(Camera* _camera) {
	// bind shader
	shader->bind();
	// iterate per batch instance
	for (std::pair<const std::shared_ptr<Model>&, const std::vector<Entity>&> pair : entityBatch) {


		const Model& model = *pair.first;
		model.bind();
		model.enableAttribs();

		// bind material
		//_material.bind();
		texture->bind(0);

		// draw models
		for (const Entity& entity : pair.second) {

			std::shared_ptr<Material> material = entity.getMaterial();

			material->bind();
			material->updateUniforms(shader);

			glEnable(GL_DEPTH_TEST);

			if (isWireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, nullptr);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, nullptr);
			}

			glDisable(GL_DEPTH_TEST);
		}

		model.unbind();
		model.disableAttribs();
	}
	// unbind shader
	shader->unbind();
}

void BatchRenderer::renderCallstack() {

}
