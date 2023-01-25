#pragma once

#include <memory>
#include "UraniumApi.h"
#include "Camera.h"
#include "Events/InputEvent.h"

namespace Uranium {
	
	class Scene;

	class FPCamera : extends Camera, implements InputEvent {
	private:
		double timeFactor;
		double responceTime;

		double xSensitivity;
		double ySensitivity;

		double xTraslation;
		double yTraslation;

		float cameraSpeed;
	
		bool grabOnCommand;

		void updateUniforms(std::shared_ptr<ShaderProgram> _shaderProgram);

		void calcCameraRotation();
		void calcMovementDirection();
		
		float getDirectionFromKey(int key1, int key2);

	protected:

	public:
		FPCamera(Scene* _currentScene);
		virtual ~FPCamera();

		void update();
	};
}