#pragma once

#include "Utils/Maths/vec3.h"
#include "Utils/Maths/mat4.h"

#include "Renderer/AccesibleShader.h"

namespace Uranium {

	class Scene;

	class Camera : public AccesibleShader {
	public:
		Camera(Scene* _currentScene);
		virtual ~Camera();

		virtual void update() = 0;

		const mat4& getViewMatrix() const;
		const mat4& getProjectionMatrix() const;

		const vec3& getRotation() const;
		const vec3& getPosition() const;

		void setViewMatrix(const mat4& _matrix);
		void setProjectionMatrix(const mat4& _matrix);

		void setRotation(const vec3& _rotation);
		void setPosition(const vec3& _position);
	
	protected:
		vec3 position;
		vec3 rotation;

		mat4 viewMatrix;
		mat4 projectionMatrix;

		Scene* currentScene;

		double fov;
		double nearPlane;
		double farPlane;

		double xSensitivity;
		double ySensitivity;

		Uniform u_view;
		Uniform u_projection;

		virtual void staticUniforms(unsigned int _program);
		virtual void updateUniforms(unsigned int _program);

		void updateViewMatrix();
		void updateProjectionMatrix();

		void updateViewport(unsigned int _x = 0, unsigned int _y = 0, unsigned int _width = 0, unsigned int _height = 0);

	private:
		friend class BatchRenderer;

		bool isCameraLocked;

	};
}