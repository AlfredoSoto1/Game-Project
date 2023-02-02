#include "FPCamera.h"

#include <GLFW/glfw3.h>
#include <cmath>
#include "UraniumApi.h"

#include "Core/Application.h"

#include "Gui/Window.h"
#include "Gui/WindowSettings.h"

#include "Utils/Maths/Operation.h"

#include "Devices/Mouse.h"
#include "Devices/Keyboard.h"

#include "Scene.h"
#include "Renderer/ShaderProgram.h"

using namespace Uranium;

FPCamera::FPCamera(Scene* _currentScene)
	: Camera(_currentScene)
{
	timeFactor = 0.0;

	xTraslation = 0.0;
	yTraslation = 0.0;

	responceTime = 1000.0; // miliseconds
	xSensitivity = 15.; // 100%
	ySensitivity = 15.; // 100%

	cameraSpeed = 0.1;

	grabOnCommand = false;

	updateProjectionMatrix();
}

FPCamera::~FPCamera() {

}

void FPCamera::update() {

	timeFactor = parentScene->getTimeInstance() / responceTime;//miliseconds

	//update projection matrix
	if (Application::get().getWindow().getSettings().hasResized()) {
		updateProjectionMatrix();
	}

	//move camera
	 xTraslation = getMouse().getCursor().getXSpeed();
	 yTraslation = getMouse().getCursor().getYSpeed();

	if (getKeyboard().isKeyToggled(GLFW_KEY_P)) {
		grabOnCommand = !grabOnCommand;
		if (grabOnCommand) {
			getMouse().getCursor().grab();
		}
		else {
			getMouse().getCursor().backToDefault();
			double xpos = Application::get().getWindow().getSettings().getWidth() / 2.0;
			double ypos = Application::get().getWindow().getSettings().getHeight() / 2.0;
			getMouse().getCursor().setPosition(xpos, ypos);
		}
	}

	if (!grabOnCommand)
		return;

	calcCameraRotation();
	calcMovementDirection();

	//update camera position
	position += direction;

	//update view matrix
	updateViewMatrix();
}

void FPCamera::calcCameraRotation() {
	rotation.y -= xTraslation * timeFactor * xSensitivity;
	rotation.x -= yTraslation * timeFactor * ySensitivity;

	rotation.x = rotation.x > 90.0 ? 90.0 : rotation.x;
	rotation.x = rotation.x < -90.0 ? -90.0 : rotation.x;
}

void FPCamera::calcMovementDirection() {
	//gets corresponding direction according to pressed keys (W,A,S,D, SPACE, L_SHIFT)
	direction.x = getDirectionFromKey(GLFW_KEY_D, GLFW_KEY_A);
	direction.y = getDirectionFromKey(GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT);
	direction.z = getDirectionFromKey(GLFW_KEY_S, GLFW_KEY_W);

	normalize(&direction);

	//update camera view direction
	float yRotationRadians = toRadians(rotation.y);
	float xViewDir = sin(yRotationRadians);
	float zViewDir = cos(yRotationRadians);

	float xDisplacement = zViewDir * direction.x - xViewDir * direction.z;
	float zDisplacement = zViewDir * direction.z + xViewDir * direction.x;

	direction.x = xDisplacement;
	direction.z = zDisplacement;

	//apply speed to camera when moving
	direction *= cameraSpeed * timeFactor;
}

float FPCamera::getDirectionFromKey(int key1, int key2) {
	if (getKeyboard().isKeyDown(key1) && getKeyboard().isKeyDown(key2))
		return 0.0f;
	else if (getKeyboard().isKeyDown(key1))
		return 1.0f;
	else if (getKeyboard().isKeyDown(key2))
		return -1.0f;
	return 0.0f;
}

void FPCamera::bindUniforms(std::shared_ptr<ShaderProgram> _shader) {
	if (_shader->hasViewMatrix()) {
		_shader->setViewMatrix(viewMatrix);
	}
	if (_shader->hasProjectionMatrix()) {
		_shader->setProjectionMatrix(projectionMatrix);
	}
}

void FPCamera::preBindUniforms(std::shared_ptr<ShaderProgram> _shader) {

}

