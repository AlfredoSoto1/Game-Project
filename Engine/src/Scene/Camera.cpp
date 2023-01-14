#define GLEW_STATIC
#include <GL/glew.h>

#include "Camera.h"

#include "Core/Application.h"
#include "Gui/Window.h"
#include "Gui/WindowSettings.h"

#include "Utils/Maths/Operation.h"

using namespace Uranium;

Camera::Camera(Scene* _currentScene)
	: currentScene(_currentScene)
{
	isCameraLocked = false;

	fov = 75.0;
	farPlane = 1000.0;
	nearPlane = 0.1;

	xSensitivity = 1.0;
	ySensitivity = 1.0;

	identity(&viewMatrix);
	identity(&projectionMatrix);
}

Camera::~Camera() {

}

const mat4& Camera::getViewMatrix() const {
	return viewMatrix;
}

const mat4& Camera::getProjectionMatrix() const {
	return projectionMatrix;
}

const vec3& Camera::getRotation() const {
	return rotation;
}

const vec3& Camera::getPosition() const {
	return position;
}

void Camera::setViewMatrix(const mat4& _matrix) {
	viewMatrix = _matrix;
}

void Camera::setProjectionMatrix(const mat4& _matrix) {
	projectionMatrix = _matrix;
}

void Camera::setRotation(const vec3& _rotation) {
	rotation = _rotation;
}

void Camera::setPosition(const vec3& _position) {
	position = _position;
}

void Camera::updateViewport(unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height) {
	glViewport(_x, _y, _width, _height);
}

void Camera::updateProjectionMatrix() {
	unsigned int width = Application::get().getWindow().getSettings().getWidth();
	unsigned int height = Application::get().getWindow().getSettings().getHeight();
	//calculates the projection matrix at current viewport
	project(&projectionMatrix, farPlane, nearPlane, fov, width, height);
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

void Camera::staticUniforms(unsigned int _program) {
	u_view = getUniform(_program, "viewMatrix");
	u_projection = getUniform(_program, "projectionMatrix");
}

void Camera::updateUniforms(unsigned int _program) {
	setMat4(u_view, viewMatrix);
	setMat4(u_projection, projectionMatrix);
}