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
#include "AppProgram/Program/AppControl/App.h"
#include "AppProgram/Program/AppControl/AppComponent.h"
using namespace Application;
/*
	Display
*/
#include "AppDisplay/Display/Window.h"
using namespace Display;

/*
	Settings & Callbacks
*/
#include "AppSettings/WindowSettings.h"
#include "AppEquipment/Callbacks/WindowCallback.h"

using namespace Settings;
using namespace Callback;

Window::Window(App* _appRef, const char* _title, unsigned int _width, unsigned int _height) 
	: AppComponent(_appRef)
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

void Window::requestAttention() {
	if (winPtr) glfwRequestWindowAttention(winPtr);
}

WindowSettings& Window::getSettings() {
	return *windowSettings;
}

Callback::WindowCallback& Window::getCallback() {
	return *windowCallback;
}

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
	Initializes the window by creating it
	with corresponding settings and context
*/
void Window::init() {

	windowSettings->loadHints();

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
	glfwSetWindowUserPointer(winPtr, getAppRef());

	windowCallback = new WindowCallback(getAppRef());
}

/*
	terminates window context and GLFW
*/
void Window::dispose() {
	delete windowCallback;

	glfwDestroyWindow(winPtr);
	glfwTerminate();
}

