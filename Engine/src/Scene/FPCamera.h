#pragma once

#include <memory>
#include "UraniumApi.h"
#include "Camera.h"
#include "Events/InputEvent.h"

namespace Uranium {
	
	class Scene;

	class FPCamera : extends Camera, implements InputEvent {
	public:
		FPCamera(Scene* _currentScene);
		virtual ~FPCamera();

		void update();
	protected:
		void bindUniforms(std::shared_ptr<ShaderProgram> _shader);
		void preBindUniforms(std::shared_ptr<ShaderProgram> _shader);

	private:
		double timeFactor;
		double responceTime;

		double xSensitivity;
		double ySensitivity;

		double xTraslation;
		double yTraslation;

		float cameraSpeed;

		bool grabOnCommand;
		
		void calcCameraRotation();
		void calcMovementDirection();

		float getDirectionFromKey(int key1, int key2);
	};
}