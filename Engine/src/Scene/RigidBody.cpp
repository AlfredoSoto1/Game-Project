#include "RigidBody.h"

#include "Utils/Maths/Operation.h"

using namespace Uranium;

RigidBody::RigidBody() {

}

RigidBody::~RigidBody() {

}

void RigidBody::setScale(const vec3& _scale) {
	scale = _scale;
}

void RigidBody::setPosition(const vec3& _position) {
	position = _position;
}

void RigidBody::setRotation(const vec3& _rotation) {
	rotation = _rotation;
}

void RigidBody::setTransformation(const mat4& _transformation) {
	transformationMatrix = _transformation;
}

vec3& RigidBody::getScale() {
	return scale;
}

vec3& RigidBody::getPosition() {
	return position;
}

vec3& RigidBody::getRotation() {
	return rotation;
}

mat4& RigidBody::getTransformation() {
	return transformationMatrix;
}

void RigidBody::update() {
	transform(&transformationMatrix, position, rotation, scale);
}
