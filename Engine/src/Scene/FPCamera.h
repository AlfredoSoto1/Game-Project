#pragma once

#include "Camera.h"
#include "Events/InputEvent.h"

namespace Uranium {
	
	class Scene;

	class FPCamera : public Camera, public InputEvent {
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

	protected:

	public:
		FPCamera(Scene* _currentScene);
		virtual ~FPCamera();

		void update();
	};
}