#include "UserCamera.h"

#include "Application/Application.h"
#include "Application/Devices/Window.h"
#include "Application/Settings/WindowSettings.h"

#include "Utils/Maths/Operation.h"

using namespace Uranium;

UserCamera::UserCamera() {
	isCameraLocked = false;

	fov = 75.0;
	farPlane = 1000.0;
	nearPlane = 0.1;

	xSensitivity = 1.0;
	ySensitivity = 1.0;

	zero(&viewMatrix);
	zero(&projectionMatrix);
}

UserCamera::~UserCamera() {

}

void UserCamera::updateProjectionMatrix() {
	unsigned int width = Application::get().getWindow().getSettings().getWidth();
	unsigned int height = Application::get().getWindow().getSettings().getHeight();
	//calculates the projection matrix at current viewport
	project(&projectionMatrix, farPlane, nearPlane, fov, width, height);
}

void UserCamera::updateViewMatrix() {
	identity(&viewMatrix);
	//rotates matrix in the x-axis
	rotate(viewMatrix, &viewMatrix, toRadians(rotation.x), vec3(1, 0, 0));
	//rotates matrix in the y-axis
	rotate(viewMatrix, &viewMatrix, toRadians(rotation.y), vec3(0, 1, 0));
	//translate matrix relative to camera position
	translate(viewMatrix, &viewMatrix, -position);
}
