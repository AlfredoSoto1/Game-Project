#include "RigidBody.h"

#include "Utils/Maths/Operation.h"

using namespace Uranium;

RigidBody::RigidBody() 
	: scale(1.0), position(0.0), rotation(0.0)
{

}

RigidBody::~RigidBody() {

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

void RigidBody::updateTransformationMatrix() {
	transform(&transformationMatrix, position, rotation, scale);
}
