#pragma once

#include "Utils/Maths/vec3.h"
#include "Utils/Maths/mat4.h"

namespace Uranium {

	class Scene;

	class Camera {
	public:
		Camera(Scene* _currentScene);
		virtual ~Camera();

		virtual void update() = 0;

		mat4& getViewMatrix();
		mat4& getProjectionMatrix();

		vec3& getPosition();
		vec3& getRotation();

		void setViewMatrix(const mat4& _matrix);
		void setProjectionMatrix(const mat4& _matrix);

		void setPosition(const vec3& _position);
		void setRotation(const vec3& _rotation);
	
	protected:
		vec3 position;
		vec3 rotation;
		vec3 direction;

		mat4 viewMatrix;
		mat4 projectionMatrix;

		Scene* currentScene;

		double fov;
		double nearPlane;
		double farPlane;

		double xSensitivity;
		double ySensitivity;

		void updateViewMatrix();
		void updateProjectionMatrix();

		void updateViewport(unsigned int _x = 0, unsigned int _y = 0, unsigned int _width = 0, unsigned int _height = 0);

	private:
		friend class Renderer;

		bool isCameraLocked;

	};
}