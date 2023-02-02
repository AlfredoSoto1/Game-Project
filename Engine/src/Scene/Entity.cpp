#include "Entity.h"

#include "UraniumApi.h"
#include "Renderer/Asset.h"
#include "Renderer/ShaderProgram.h"

using namespace Uranium;

unsigned int Entity::universal_entity_id_counter = 0;

Entity::Entity(Entity&& _move) noexcept {
	name = _move.name;
	asset = _move.asset;
	id = _move.id;
	print_status("Moved Entity");
}

Entity::Entity(const Entity& _copy) {
	name = _copy.name;
	asset = _copy.asset;
	id = universal_entity_id_counter++;
	print_status("Copied Entity");
}

Entity::Entity(const std::shared_ptr<Asset>& _asset, const std::string& _name)
{
	name = _name;
	asset = _asset;
	id = universal_entity_id_counter++;
	print_status("Created Entity");
}

Entity::~Entity() {

}

unsigned int Entity::getId() const {
	return id;
}

std::string Entity::getName() const {
	return name;
}

RigidBody& Entity::getRigidBody() {
	return rigidBody;
}

std::shared_ptr<Asset>& Entity::getAsset() {
	return asset;
}

void Entity::setName(const std::string& _name) {
	name = _name;
}

void Entity::setRigidBody(const RigidBody& _rigidBody) {
	rigidBody = _rigidBody;
}
void Entity::setAsset(const std::shared_ptr<Asset>& _asset) {
	asset = _asset;
}

void Entity::bindUniforms(std::shared_ptr<ShaderProgram> _shader) {
	if (_shader->hasTransformationMatrix()) {
		_shader->setTransformationMatrix(getRigidBody().getTransformation());
	}
}

void Entity::preBindUniforms(std::shared_ptr<ShaderProgram> _shader) {

}


