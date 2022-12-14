#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "UraniumApi.h"

#include <iostream>
using namespace std;

#include "AppProgram.h"
#include "Application.h"
#include "Gui/Window.h"
#include "Gui/WindowSettings.h"
#include "Scene/Scene.h"
#include "Devices/Mouse.h"
#include "Devices/Keyboard.h"

using namespace Uranium;

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

Application* Application::application;

Application& Application::get() {
	return *application;
}

void Application::start(AppProgram* _appProgram) {
	throw_error(_appProgram == nullptr, "No AppProgram defined for Application context.");
	// create Application
	Application::application = new Application(_appProgram);
	// run application
	Application::get().run();
	// end aplication
	delete Application::application;
}

// Create Application
Application::Application(AppProgram* _appProgram) 
	: appProgram(_appProgram), isRunning(false)
{
	mouse = nullptr;
	window = nullptr;
	// Initiates GLFW
	if (!glfwInit()) {
		isRunning = false;
		print_status("GLFW couldn't initiated correctly.");
		return;
	}
	// set default GLFW error callback
	glfwSetErrorCallback(&error_callback);

	isRunning = true;
}

// End Application
Application::~Application() {
	if (!isRunning)
		return;
	isRunning = false;

	delete mouse;
	delete keyboard;
	delete window;
	delete appProgram;

	glfwTerminate();
}

// Run Application
void Application::run() {
	
	// initiates the application content
	window = new Window("Default", 1280, 720);
	window->init();

	glfwSetWindowUserPointer(getWindow(), this);

	// init external devices
	mouse = new Mouse(window);
	keyboard = new Keyboard(window);
	
	// init application program
	appProgram->init();

	while (!glfwWindowShouldClose(*window)) {
		// update
		appProgram->update();
		// reset viewport
		if (window->getSettings().hasResized()) {
			glViewport(0, 0, window->getSettings().getWidth(), window->getSettings().getHeight());
		}

		// draw
		appProgram->draw();

		// post processing

		// swap buffers
		glfwSwapBuffers(*window);

		// post draw
		window->getSettings().hasResized() = false;
		appProgram->afterDraw();

		// poll events
		glfwPollEvents();

		mouse->update();
		keyboard->update();
	}
	// closes the application
	appProgram->dispose();

	// disposes everything after application has ended
	window->dispose();
}

Window& Application::getWindow() {
	return *window;
}

Mouse& Application::getMouse() {
	return *mouse;
}

Keyboard& Application::getKeyboard() {
	return *keyboard;
}

