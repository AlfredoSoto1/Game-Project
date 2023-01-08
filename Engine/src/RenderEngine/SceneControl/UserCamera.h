#pragma once

#include "Utils/Maths/vec2.h"
#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"

#include "Utils/Maths/mat2.h"
#include "Utils/Maths/mat3.h"
#include "Utils/Maths/mat4.h"

namespace Uranium {

	class UserCamera {
	private:
		bool isCameraLocked;

	protected:
		vec3 position;
		vec3 rotation;
		vec3 direction;

		mat4 viewMatrix;
		mat4 projectionMatrix;

		double fov;
		double nearPlane;
		double farPlane;

		double xSensitivity;
		double ySensitivity;

		virtual void update() = 0;
		
		void updateViewMatrix();
		void updateProjectionMatrix();

	public:
		UserCamera();
		virtual ~UserCamera();

	};
}