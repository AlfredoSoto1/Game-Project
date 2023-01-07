#define UR_GLFW
#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"

#include <iostream>
using namespace std;

#include "Application.h"
#include "ApplicationRunner.h"
#include "Devices/Window.h"
#include "Devices/Device.h"
#include "Settings/WindowSettings.h"
#include "Uranium/RenderEngine/SceneControl/Scene.h"
#include "Uranium/RenderEngine/SceneControl/SceneManager.h"

using namespace Uranium;

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

Application* Application::application;

Application& Application::get() {
	return *application;
}

void Application::start(ApplicationRunner* _applicationTemplate) {
	// create Application
	Application::application = new Application();
	Application::get().applicationTemplate = _applicationTemplate;
	// run application
	Application::get().run();
	// end aplication
	delete Application::application;
}

// Create Application
Application::Application() {
	// Initiates GLFW
	if (!glfwInit()) {
		isRunning = false;
		std::cout << "GLFW couldn't initiated correctly." << std::endl;
		return;
	}

	// set default GLFW error callback
	glfwSetErrorCallback(&error_callback);
}

// End Application
Application::~Application() {
	delete window;
	delete device;
	delete sceneManager;

	glfwTerminate();
}

// Run Application
void Application::run() {
	
	window = new Window("Default", 1280, 720);
	device = new Device();
	sceneManager = new SceneManager();

	// initiates the application content
	applicationTemplate->init();

	window->init();
	device->init();
	sceneManager->init();

	isRunning = true;
	while (!glfwWindowShouldClose(*window)) {

		applicationTemplate->run();

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
	applicationTemplate->dispose();
}

//void Application::clearError() {
//	while (glGetError() != GL_NO_ERROR);
//}
//
//void Application::checkError() {
//	while (GLenum error = glGetError())
//		std::cout << "[GL ERROR]: " << error << std::endl;
//}

Window& Application::getWindow() {
	return *window;
}

SceneManager& Application::getSceneManager() {
	return *sceneManager;
}

Device& Application::getDevice() {
	return *device;
}

void Application::setCurrentScene(Scene* _scene) {

}