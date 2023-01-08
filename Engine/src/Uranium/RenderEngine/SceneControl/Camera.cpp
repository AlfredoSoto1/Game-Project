#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Uranium/Application/Application.h"
#include "Uranium/Application/Devices/Window.h"
#include "Uranium/Application/Settings/WindowSettings.h"
#include "Uranium/Utils/Maths/Operation.h"

using namespace Uranium;

Camera::Camera() 
	: position(0.0), rotation(0.0), direction(0.0)
{
	fov = 75.0;
	farPlane = 1000.0;
	nearPlane = 0.1;

	zero(&viewMatrix);
	zero(&projectionMatrix);
}

Camera::~Camera() {

}

void Camera::calc_camera_rotation(const double& milisecDif) {
	//rotation += vec3(yPixelDif * milisecDif * ySensitivity, xPixelDif * milisecDif * xSensitivity, 0.0/*z-axis rot*/);

	rotation.x = rotation.x > 90.0 ? 90.0 : rotation.x;
	rotation.x = rotation.x < -90.0 ? -90.0 : rotation.x;
}

void Camera::calcMovementDirection(const double& milisecDif) {
	//gets corresponding direction according to pressed keys (W,A,S,D, SPACE, L_SHIFT)
	direction.x = getDirectionFromKey(GLFW_KEY_D, GLFW_KEY_A);
	direction.y = getDirectionFromKey(GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT);
	direction.z = getDirectionFromKey(GLFW_KEY_S, GLFW_KEY_W);

	normalize(&direction);

	//update camera view direction
	float yRotationRadians = toRadians(rotation.y);
	float xViewDir = sin(yRotationRadians);
	float zViewDir = cos(yRotationRadians);

	//combines camera direction with movement direction
	direction.x = zViewDir * direction.x - xViewDir * direction.z;
	direction.z = zViewDir * direction.z + xViewDir * direction.x;
	
	//apply speed to camera when moving
	//direction *= milisecDif * movementSpeed;
}

void Camera::updateViewMatrix() {
	identity(&viewMatrix);
	//rotates matrix in the x-axis
	rotate(viewMatrix, &viewMatrix, toRadians(rotation.x), vec3(1, 0, 0));
	//rotates matrix in the y-axis
	rotate(viewMatrix, &viewMatrix, toRadians(rotation.y), vec3(0, 1, 0));
	//translate matrix relative to camera position
	translate(viewMatrix, &viewMatrix, -position);
}

void Camera::updateProjectionMatrix() {
	unsigned int width = Application::get().getWindow().getSettings().getWidth();
	unsigned int height = Application::get().getWindow().getSettings().getHeight();
	//calculates the projection matrix at current viewport
	project(&projectionMatrix, farPlane, nearPlane, fov, width, height);
}

float Camera::getDirectionFromKey(unsigned int key1, unsigned int key2) {
	/*if (displayRef->keyListener->isKeyDown(key1) && displayRef->keyListener->isKeyDown(key2))
		return 0.0f;
	else if (displayRef->keyListener->isKeyDown(key1))
		return 1.0f;
	else if (displayRef->keyListener->isKeyDown(key2))
		return -1.0f;*/
	return 0.0f;
}

