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

Renderer::Renderer(ShaderProgram* _shader)
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

void Renderer::bindModel(std::shared_ptr<Asset>& _asset) {
	// bind model and attributes
	_asset->getModel()->bind();
	_asset->getModel()->enableAttribs();
}

void Renderer::unbindModel(std::shared_ptr<Asset>& _asset) {

	// unbind model
	_asset->getModel()->disableAttribs();
	_asset->getModel()->unbind();
}

void Renderer::bindMaterial() {

}
void Renderer::unbindMaterial() {
	// unbind material
	_asset->getMaterial()->getAlbedo()->unbind();
}

void Renderer::loadCameraSettings(std::shared_ptr<Camera> _camera) {
	// load all camera settings here
	if (shaderHas_ViewMatrix) {
		setMat4(shader->getViewU(), _camera->getViewMatrix());
	}
	if (shaderHas_ProjectionMatrix) {
		setMat4(shader->getProjectionU(), _camera->getProjectionMatrix());
	}
}

void Renderer::loadAssets(std::shared_ptr<Asset> _asset) {

	// bind material	
	if (shaderHas_albedo && _asset->getMaterial()->getAlbedo() != nullptr) {
		_asset->getMaterial()->getAlbedo()->bind(0);
		setSampler(shader->getAlbedoU(), 0);
	}

	if (shaderHas_color) {
		setVec4(shader->getColorU(), material.getColor());
	}
}

void Renderer::flushAssets(std::shared_ptr<Asset> _asset) {
	
}

void Renderer::loadEntityAsset(std::shared_ptr<Entity> _entity) {
	if (shaderHas_TransformationMatrix) {
		setMat4(shader->getTransformationU(), _entity->getRigidBody().getTransformation());
	}
}

void Renderer::enableRendererAttribs() {
	glEnable(GL_DEPTH_TEST);
}

void Renderer::disableRendererAttribs() {
	glDisable(GL_DEPTH_TEST);
}

void Renderer::drawModel(const Model& _model) {

	enableRendererAttribs();

	if (isWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, _model.getIndexCount(), GL_UNSIGNED_INT, nullptr);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glDrawElements(GL_TRIANGLES, _model.getIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

	disableRendererAttribs();
}

void Renderer::render(std::shared_ptr<Camera> _camera) {
	shader->bind();

	loadCameraSettings(_camera);

	// iterate per batch instance
	for (const std::pair<std::shared_ptr<Asset>, const std::vector<std::shared_ptr<Entity>>&>& pair : mappedEntities) {
		std::shared_ptr<Asset> entityAsset = pair.first;

		const Model& model = *entityAsset->getModel();

		bindModel();

		// load assets to shader renderer
		loadAssets(entityAsset);

		for (std::shared_ptr<Entity> entity : pair.second) {
			// update transformation matrix here
			entity->getRigidBody().update();

			loadEntityAsset(entity);

			drawModel(model);
		}

		unbindModel();
		flushAssets(entityAsset);
	}
	// unbind shader
	shader->unbind();
}

void Renderer::setSampler(const Sampler& _sampler, unsigned int _samplerId) const {
	glUniform1i(_sampler, _samplerId);
}

void Renderer::setVec2(Uniform _uniform, const vec2& _vec2) const {
	glUniform2f(_uniform, _vec2.x, _vec2.y);
}

void Renderer::setVec3(Uniform _uniform, const vec3& _vec3) const {
	glUniform3f(_uniform, _vec3.x, _vec3.y, _vec3.z);
}

void Renderer::setVec4(Uniform _uniform, const vec4& _vec4) const {
	glUniform4f(_uniform, _vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void Renderer::setMat2(Uniform _uniform, mat2& _mat2) const {
	glUniformMatrix2fv(_uniform, 1, GL_TRUE, _mat2);
}

void Renderer::setMat3(Uniform _uniform, mat3& _mat3) const {
	glUniformMatrix3fv(_uniform, 1, GL_TRUE, _mat3);
}

void Renderer::setMat4(Uniform _uniform, mat4& _mat4) const {
	glUniformMatrix4fv(_uniform, 1, GL_TRUE, _mat4);
}
