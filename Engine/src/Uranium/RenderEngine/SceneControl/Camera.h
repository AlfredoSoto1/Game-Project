#pragma once

#include "Uranium/Utils/Maths/vec2.h"
#include "Uranium/Utils/Maths/vec3.h"
#include "Uranium/Utils/Maths/vec4.h"

#include "Uranium/Utils/Maths/mat2.h"
#include "Uranium/Utils/Maths/mat3.h"
#include "Uranium/Utils/Maths/mat4.h"

namespace Uranium {

	class Camera {
	private:
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

		bool isCameraLocked;

		void updateViewMatrix();
		void updateProjectionMatrix();

		void calc_camera_rotation(const double& milisecDif);
		void calcMovementDirection(const double& milisecDif);

		float getDirectionFromKey(unsigned int key1, unsigned int key2);

	public:
		Camera();
		~Camera();
	
		void update() {}
		
	};
}