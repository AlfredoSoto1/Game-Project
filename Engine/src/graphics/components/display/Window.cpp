#include "Window.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "graphics/settings/WindowSettings.h"

using namespace std;
using namespace Display;

Window::Window(const WindowSettings& settings) {
	this->winPtr = nullptr;
	this->settings = new WindowSettings(settings);
}

Window::Window(const string& title, unsigned int width, unsigned int height) 
{
	winPtr = nullptr;
	settings = new WindowSettings();
	
	settings->setTitle(title);
	settings->setSize(width, height);
}

Window::~Window() {
	delete settings;
}

void Window::close() {
	if(winPtr) glfwSetWindowShouldClose(winPtr, GLFW_TRUE);
}

void Window::focus() {
	if(winPtr) glfwFocusWindow(winPtr);
}

void Window::processFrames() {
	//Current thread sleeps here to get targeted FPS
	//if (!vsyncEnabled && targetFrames != UNLIMITED_FPS) {
	//	while (glfwGetTime() < lastTime + 1.0 / targetFrames);
	//	lastTime += 1.0 / targetFrames;
	//}
	////Calculates FPS
	//frames++;
	//if (glfwGetTime() * 1000.0 > lastRefresh + 1000.0) {
	//	std::cout << "FPS: " << frames << std::endl;
	//	frames = 0;
	//	lastRefresh = glfwGetTime() * 1000.0;
	//}

	//double currentTime = glfwGetTime();
	//timeDifference = (currentTime - lastTimeDifference);
	//lastTimeDifference = currentTime;
}

void Window::render(int isOnCallback) {
	if (settings->hasResized())
		glViewport(0, 0, settings->getWidth(), settings->getHeight());

	//if (update != nullptr)
	//	update();

	glfwSwapBuffers(winPtr);
	settings->hasResized() = false;

	if (!isOnCallback)
		glfwPollEvents();
	//processFrames();
}

void Window::renderDisplay() {
	//glfwSetWindowUserPointer(window, this);
	//this->windowListener = new listener::WindowListener(this);
	//this->mouseListener = new listener::MouseListener(this);
	//this->keyListener = new listener::KeyListener(this);

	/*if (init != nullptr)
		init();*/

	while (!glfwWindowShouldClose(winPtr)) {
		render(0);
	}

	//if (dispose != nullptr)
	//	dispose();

	//delete windowListener;
	//delete mouseListener;
	//delete keyListener;

	glfwDestroyWindow(winPtr);
	//isRunning = false;
	glfwTerminate();
}

//definition of error callback
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

//overloads
Window::operator GLFWwindow* () {
	return winPtr;
}

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

bool Window::initGLFW() {
	if (!glfwInit()) {
		cout << "GLFW couldn't initiated correctly." << endl;
		return false;
	}
	return true;
}

void Window::initWindow() {
	//setting error callback
	glfwSetErrorCallback(&error_callback);

	//Initiates GLFW - returns false if it couldn't initiate
	if (!initGLFW()) return;

	settings->init();

	winPtr = glfwCreateWindow(settings->getWidth(), settings->getHeight(), settings->getTitle().c_str(), settings->isFullScreen() ? settings->getCurrentMonitor() : NULL, NULL);
	if (!winPtr) {
		cout << "Failed to create GLFW window." << endl;
		glfwTerminate();
		return;
	}

	settings->setContext(winPtr);
	settings->centerWindow();

	//create Display context
	glfwMakeContextCurrent(winPtr);

	//glfwSwapInterval(1);
	//glfwSwapInterval(0);
	glfwShowWindow(winPtr);

	//Initiates GLEW - returns false if it couldn't initiate
	if (!initGLEW()) return;
	glViewport(0, 0, settings->getWidth(), settings->getHeight());

	renderDisplay();
}

