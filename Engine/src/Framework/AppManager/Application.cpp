#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

#include "Application.h"
using namespace FrameworkEngine;

unsigned int Application::appCount = 0;

/*
	Settings
*/
#include "Settings/WindowSettings.h"
using namespace Settings;

/*
	Display
*/
#include "Graphics/Display/Window.h"
using namespace Display;

/*
	SceneUtils
*/
#include "Framework/SceneManager/SceneManager.h"
using namespace SceneControl;

/*
	Peripherals
*/
#include "Framework/Peripherals/Device.h"
using namespace Peripherals;

Application::Application() {
	appCount++;
	if (appCount > 1) {
		cout << "Cannot create more than one Application instance" << endl;
		return;
	}
}

Application::~Application() {
	delete window;
	delete device;
	delete sceneManager;
}

void Application::clearError() {
	while (glGetError() != GL_NO_ERROR);
}

void Application::checkError() {
	while (GLenum error = glGetError())
		std::cout << "[GL ERROR]: " << error << std::endl;
}

//definition of error callback
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

void Application::createMainComponents() {
	window = new Window(this, "Default", 1280, 720);
	device = new Device(this);
	sceneManager = new SceneManager(this);
}

void Application::run() {
	// Initiates GLFW
	if (!glfwInit()) {
		isRunning = false;
		std::cout << "GLFW couldn't initiated correctly." << std::endl;
		return;
	}

	// set default GLFW error callback
	glfwSetErrorCallback(&error_callback);

	createMainComponents();

	// initiates the application content
	init();

	window->init();
	device->init();
	sceneManager->init();

	isRunning = true;
	while (!glfwWindowShouldClose(*window)) {

		// update
		sceneManager->update();

		// reset viewport
		if (window->getSettings().hasResized()) {
			glViewport(0, 0, window->getSettings().getWidth(), window->getSettings().getHeight());
		}

		// draw
		sceneManager->draw();

		// post processing

		// swap buffers
		glfwSwapBuffers(*window);

		// post draw
		window->getSettings().hasResized() = false;
		sceneManager->afterDraw();

		// poll events
		glfwPollEvents();
		device->update();
	}
	isRunning = false;

	// disposes everything after application has ended
	sceneManager->dispose();
	device->dispose();
	window->dispose();
	
	// closes the application
	close();

	glfwTerminate();
}

void Application::exit(int _errorCode) {
	this->errorCode = _errorCode;
}

Window& Application::getWindow() {
	return *window;
}

SceneManager& Application::getSceneManager() {
	return *sceneManager;
}

Device& Application::getDevice() {
	return *device;
}