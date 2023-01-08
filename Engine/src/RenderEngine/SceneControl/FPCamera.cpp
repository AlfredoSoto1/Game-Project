#include "FPCamera.h"

#include <cmath>
#include "Utils/Maths/Operation.h"

using namespace Uranium;

FPCamera::FPCamera() {

}

FPCamera::~FPCamera() {

}

void FPCamera::update() {

}

void FPCamera::calc_camera_rotation() {
	//rotation += vec3(yPixelDif * milisecDif * ySensitivity, xPixelDif * milisecDif * xSensitivity, 0.0/*z-axis rot*/);

	rotation.x = rotation.x > 90.0 ? 90.0 : rotation.x;
	rotation.x = rotation.x < -90.0 ? -90.0 : rotation.x;
}

void FPCamera::calcMovementDirection() {
	//gets corresponding direction according to pressed keys (W,A,S,D, SPACE, L_SHIFT)
	//direction.x = getDirectionFromKey(GLFW_KEY_D, GLFW_KEY_A);
	//direction.y = getDirectionFromKey(GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT);
	//direction.z = getDirectionFromKey(GLFW_KEY_S, GLFW_KEY_W);

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

void FPCamera::mouseDrop(int _pathCount, const char** _paths) {
	
}

void FPCamera::mouseEnterWindow(bool hasEntered) {
	
}

void FPCamera::mouseMoved(double xpos, double ypos) {
	
}

void FPCamera::mouseScrollButton(double xOffset, double yOffset) {
	
}

void FPCamera::mouseClickedButton(int button, int mods, double xpos, double ypos) {
	
}

void FPCamera::mousePressedButton(int button, int mods, double xpos, double ypos) {
	
}

void FPCamera::mouseReleasedButton(int button, int mods, double xpos, double ypos) {
	
}
