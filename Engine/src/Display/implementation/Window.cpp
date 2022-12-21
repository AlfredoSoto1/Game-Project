/*
	GLFW & GLEW
*/
#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
/*
	Application Components
*/
#include "Application/App.h"
#include "Application/AppComponent.h"

using namespace Application;
/*
	Display
*/
#include "Display/Window.h"

using namespace Display;

/*
	SceneUtils
*/
#include "SceneUtils/SceneManager.h"

using namespace SceneUtils;

/*
	Settings & Callbacks
*/
#include "Settings/WindowSettings.h"
#include "Callbacks/WindowCallback.h"

using namespace Settings;
using namespace Callback;

Window::Window(const WindowSettings& _settings)
	: AppComponent()
{
	this->winPtr = nullptr;
	this->windowCallback = nullptr;
	this->windowSettings = new WindowSettings(_settings);
}

Window::Window(const string& _title, unsigned int _width, unsigned int _height) 
	: AppComponent()
{
	this->winPtr = nullptr;
	this->windowCallback = nullptr;
	this->windowSettings = new WindowSettings();

	this->windowSettings->setTitle(_title);
	this->windowSettings->setSize(_width, _height);
}

Window::~Window() {
	delete windowSettings;
}

void Window::close() {
	if(winPtr) glfwSetWindowShouldClose(winPtr, GLFW_TRUE);
}

void Window::focus() {
	if(winPtr) glfwFocusWindow(winPtr);
}

WindowSettings& Window::getWindowSettings() {
	return *windowSettings;
}

Callback::WindowCallback& Window::getWindowCallback() {
	return *windowCallback;
}

//definition of error callback
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

//overloads
Window::operator GLFWwindow* () {
	return winPtr;
}

/*
	Initiates GLEW
*/
bool Window::initGLEW() {
	if (glewInit() != GLEW_OK) {
		cout << "Couldn't inititate GLEW correctly." << endl;
		return false;
	}
	else {
		cout << glGetString(GL_VERSION) << endl;
		return true;
	}
}

/*
	Initiates GLFW
*/
bool Window::initGLFW() {
	if (!glfwInit()) {
		cout << "GLFW couldn't initiated correctly." << endl;
		return false;
	}
	return true;
}

/*
	Initializes the window by creating it
	with corresponding settings and context
*/
void Window::init() {
	//setting error callback
	glfwSetErrorCallback(&error_callback);

	//Initiates GLFW - returns false if it couldn't initiate
	if (!initGLFW()) return;

	windowSettings->loadHints();
	windowSettings->apply();

	winPtr = glfwCreateWindow(
		windowSettings->getWidth(), windowSettings->getHeight(),
		windowSettings->getTitle().c_str(),
		windowSettings->isFullScreen() ? windowSettings->getCurrentMonitor() : NULL, NULL);
	if (!winPtr) {
		cout << "Failed to create GLFW window." << endl;
		glfwTerminate();
		return;
	}

	//set settings context and prefferences
	windowSettings->setContext(winPtr);
	windowSettings->centerWindow();

	//create Display context
	glfwMakeContextCurrent(winPtr);
	glfwShowWindow(winPtr);

	glfwSwapInterval(0);

	//Initiates GLEW - returns false if it couldn't initiate
	if (!initGLEW()) {
		cout << "Failed to initiate GLEW." << endl;
		glfwTerminate();
		return;
	}
	glViewport(0, 0, windowSettings->getWidth(), windowSettings->getHeight());

	// Create a Window Callback
	windowCallback = new WindowCallback(this);
}

/*
	runs a loop to keep updating the window
*/
void Window::runLoop() {
	while (!glfwWindowShouldClose(winPtr)) {
		getAppRef()->sceneManager->update();
		pollEvents(GL_FALSE);
	}
}

/*
	polls events
*/
void Window::pollEvents(int _isOnCallback) {
	if (windowSettings->hasResized())
		glViewport(0, 0, windowSettings->getWidth(), windowSettings->getHeight());

	getAppRef()->sceneManager->draw();
	
	glfwSwapBuffers(winPtr);
	windowSettings->hasResized() = false;

	if (_isOnCallback == GL_FALSE)
		glfwPollEvents();

	getAppRef()->sceneManager->afterDraw();
}

/*
	terminates window context and GLFW
*/
void Window::dispose() {
	delete windowCallback;

	glfwDestroyWindow(winPtr);
	glfwTerminate();
}

