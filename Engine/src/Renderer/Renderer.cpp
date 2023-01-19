#define GLEW_STATIC
#include <GL/glew.h>

#define CATCH_OPENGL_ERROR
#include "UraniumApi.h"
#include "Renderer.h"

#include <vector>
#include <unordered_map>

#include "Scene/Entity.h"
#include "Scene/Camera.h"
#include "Utils/Geometry/Model.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture.h"
#include "Renderer/Material.h"
#include "Renderer/Asset.h"

using namespace Uranium;

Renderer::Renderer(ShaderProgram* _shader)
	: defaultShader(_shader)
{
	isWireframe = false;

	mappedEntities.reserve(2);
}

Renderer::~Renderer() {
	mappedEntities.clear();
}

void Renderer::submit(std::shared_ptr<Entity> _entity) {
	mappedEntities[_entity->getAsset()].push_back(_entity);
}

void Renderer::render(Camera* _camera) {
	// bind shader
	defaultShader->bind();

	for (const std::pair<const std::string&, const std::pair<int, unsigned int>&>& samplers : defaultShader->getUniformSamplers()) {
		if (samplers.first == "albedo") {
			glUniform1i(samplers.second.first, 0);
		}
	}

	// set projection and view matrix
	glUniformMatrix4fv(uniformID, 1, GL_TRUE, _camera->getViewMatrix());
	glUniformMatrix4fv(uniformID, 1, GL_TRUE, _camera->getProjectionMatrix());

	// iterate per batch instance
	for (const std::pair<std::shared_ptr<Asset>, const std::vector<std::shared_ptr<Entity>>&>& pair : mappedEntities) {
		// retain Asset
		std::shared_ptr<Asset> entityAsset = pair.first;

		// obtain shader and model from Asset
		const Model& model = *entityAsset->getModel();
		const Material& material = *entityAsset->getMaterial();
		
		model.bind();
		model.enableAttribs();

		// bind material
		material.getAlbedo()->bind(0);
		// set dynamic Samplers
		glUniform1i(samplerId, bindingId); // albedo

		defaultShader->setAlbedoSampler(material.getAlbedo());

		// draw models
		for (std::shared_ptr<Entity> entity : pair.second) {

			// update transformation matrix here
			entity->getRigidBody().update();


			// set transformation matrix
			glUniformMatrix4fv(uniformID, 1, GL_TRUE, entity->getRigidBody().getTransformation());


			for (const std::pair<const std::string&, const std::pair<int, unsigned int>&>& uniformFlags : defaultShader->getUniformFlags()) {
				if (uniformFlags.first == "projectionMatrix") {
					glUniformMatrix4fv(uniformFlags.second.first, 1, GL_TRUE, _camera->getProjectionMatrix());

				}
				else if (uniformFlags.first == "viewMatrix") {
					glUniformMatrix4fv(uniformFlags.second.first, 1, GL_TRUE, _camera->getViewMatrix());

				}
				else if (uniformFlags.first == "transformationMatrix") {
					glUniformMatrix4fv(uniformFlags.second.first, 1, GL_TRUE, entity->getRigidBody().getTransformation());
				}
				else if (uniformFlags.first == "u_Color") {
					glUniform4f(uniformFlags.second.first, 1.0, 1.0, 1.0, 1.0);
				}
			}

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

		// unbind material
		material.getAlbedo()->unbind();

		// unbind model
		model.unbind();
		model.disableAttribs();
	}
	// unbind shader
	defaultShader->unbind();
}
