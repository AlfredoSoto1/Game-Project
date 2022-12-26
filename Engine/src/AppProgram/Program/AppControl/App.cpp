
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
/*
	Application
*/
#include "AppProgram/Program/AppControl/App.h"
#include "AppProgram/Program/AppControl/AppComponent.h"

using namespace Application;

/*
	Settings
*/
#include "AppSettings/WindowSettings.h"
using namespace Settings;

/*
	Display
*/
#include "AppDisplay/Display/Window.h"
using namespace Display;

/*
	SceneUtils
*/ 
#include "AppProgram/Program/SceneControl/SceneManager.h"
using namespace SceneUtils;

/*
	Peripherals
*/
#include "AppEquipment/Equipments.h"
using namespace Equipment;

App::App() {
	window = new Window(this, "Default", 1280, 720);
	equipments = new Equipments(this);
	sceneManager = new SceneManager(this);
}

App::~App() {
	delete window;
	delete equipments;
	delete sceneManager;
}

void App::clearError() {
	while (glGetError() != GL_NO_ERROR);
}

void App::checkError() {
	while (GLenum error = glGetError())
		std::cout << "[GL ERROR]: " << error << std::endl;
}

//definition of error callback
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

void App::init() {

	if (!glfwInit()) {
		std::cout << "GLFW couldn't initiated correctly." << std::endl;
		return;
	}

	glfwSetErrorCallback(&error_callback);

	window->init();
	equipments->init();
	sceneManager->init();
}

void App::run() {
	// run application loop

	while (!glfwWindowShouldClose(*window)) {
		sceneManager->update();

		if (window->getSettings().hasResized()) {
			glViewport(0, 0, window->getSettings().getWidth(), window->getSettings().getHeight());
		}
		sceneManager->draw();

		glfwSwapBuffers(*window);
		window->getSettings().hasResized() = false;
		sceneManager->afterDraw();

		glfwPollEvents();
		equipments->update();
	}
}

void App::end() {
	//dispose everything on the app
	sceneManager->dispose();
	equipments->dispose();
	window->dispose();
}

void App::launch() {
	//initiates application
	init();
	//runs application
	run();
	//ends application
	end();
}

void App::exit() {
	//exits application
	// TODO + in the future
}

Window& App::getWindow() {
	return *window;
}

SceneManager& App::getSceneManager() {
	return *sceneManager;
}

Equipments& App::getEquipments() {
	return *equipments;
}


