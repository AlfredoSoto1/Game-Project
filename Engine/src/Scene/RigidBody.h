#pragma once

#include "Utils/Maths/vec3.h"
#include "Utils/Maths/mat4.h"

namespace Uranium {

	class RigidBody {
	public:
		RigidBody();
		virtual ~RigidBody();

		vec3& getScale();
		vec3& getPosition();
		vec3& getRotation();

		mat4& getTransformation();

		void update();

	private:
		vec3 scale;
		vec3 position;
		vec3 rotation;

		mat4 transformationMatrix;
	};
}