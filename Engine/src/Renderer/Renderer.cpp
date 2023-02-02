#define GLEW_STATIC
#include <GL/glew.h>

#define CATCH_OPENGL_ERROR
#include "UraniumApi.h"
#include "Renderer.h"

#include <vector>
#include <unordered_map>

#include "Utils/Maths/vec2.h"
#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"

#include "Utils/Maths/mat2.h"
#include "Utils/Maths/mat3.h"
#include "Utils/Maths/mat4.h"

#include "Scene/Entity.h"
#include "Scene/Camera.h"
#include "Utils/Geometry/Model.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture.h"
#include "Renderer/Material.h"
#include "Renderer/Asset.h"

using namespace Uranium;

Renderer::Renderer(std::shared_ptr<ShaderProgram> _shader)
	: shader(_shader)
{
	isWireframe = false;

	mappedEntities.reserve(2);
}

Renderer::~Renderer() {
	mappedEntities.clear();
}

void Renderer::push(std::shared_ptr<Entity> _entity) {
	mappedEntities[_entity->getAsset()].push_back(_entity);
}

void Renderer::joinShader() {

}

void Renderer::drawModel(const Model& _model) {

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

void Renderer::render(std::shared_ptr<Camera> _camera) {
	shader->bind();

	// load all camera settings here
	_camera->bindUniforms(shader);

	// iterate per batch instance
	for (const std::pair<std::shared_ptr<Asset>, const std::vector<std::shared_ptr<Entity>>&>& pair : mappedEntities) {
		std::shared_ptr<Asset> entityAsset = pair.first;

		const Model& model = *entityAsset->getModel();
		const Material& material = *entityAsset->getMaterial();

		// bind model and attributes
		model.bind();
		model.enableAttribs();

		// load assets to shader renderer
		// bind material	
		material.bind(shader);

		for (std::shared_ptr<Entity> entity : pair.second) {
			// update transformation matrix here
			entity->getRigidBody().update();
	
			// load entity uniform
			entity->bindUniforms(shader);

			drawModel(model);
		}

		material.unbind();

		// unbind model
		model.disableAttribs();
		model.unbind();
	}
	// unbind shader
	shader->unbind();
}

