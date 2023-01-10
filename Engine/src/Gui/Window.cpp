/*
	GLFW & GLEW
*/
#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

#include "Core/Application.h"
#include "Events/WindowListener.h"

#include "Window.h"
#include "WindowSettings.h"

using namespace Uranium;

Window::Window(const char* _title, unsigned int _width, unsigned int _height) 
{
	this->listener = nullptr;
	this->winPtr = nullptr;
	this->settings = new WindowSettings();

	this->settings->setTitle(_title);
	this->settings->setSize(_width, _height);
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

void Window::requestAttention() {
	if (winPtr) glfwRequestWindowAttention(winPtr);
}

void Window::setListener(WindowListener* _listener) {
	this->listener = _listener;
}

WindowSettings& Window::getSettings() {
	return *settings;
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

	settings->loadHints();

	winPtr = glfwCreateWindow(
		settings->getWidth(), settings->getHeight(),
		settings->getTitle().c_str(),
		settings->isFullScreen() ? settings->getCurrentMonitor() : NULL, NULL);
	
	if (!winPtr) {
		cout << "Failed to create GLFW window." << endl;
		glfwTerminate();
		return;
	}

	//set settings context and prefferences
	settings->setContext(winPtr);
	settings->centerWindow();

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
	glViewport(0, 0, settings->getWidth(), settings->getHeight());

	initCallback();
}

/*
	terminates window context and GLFW
*/
void Window::dispose() {
	glfwDestroyWindow(winPtr);
}

void Window::initCallback() {
	auto positionCallback = [](GLFWwindow* winPtr, int xpos, int ypos) {
		Window& window = Application::get().getWindow();
		window.getSettings().changePosition(xpos, ypos);
		if (window.listener != nullptr)
			window.listener->windowMoved(xpos, ypos);
	};

	auto sizeCallback = [](GLFWwindow* winPtr, int width, int height) {
		Window& window = Application::get().getWindow();
		window.getSettings().changeSize(width, height);
		if (window.listener != nullptr)
			window.listener->windowSize(width, height);
	};

	auto closeCallback = [](GLFWwindow* winPtr) {
		Window& window = Application::get().getWindow();
		if (window.listener != nullptr)
			window.listener->windowClosed();
	};

	auto focusCallback = [](GLFWwindow* winPtr, int isFocused) {
		Window& window = Application::get().getWindow();
		if (window.listener != nullptr)
			window.listener->windowFocused(isFocused > 0 ? true : false);
	};

	auto iconifyCallback = [](GLFWwindow* winPtr, int isIconified) {
		Window& window = Application::get().getWindow();
		if (window.listener != nullptr)
			window.listener->windowIconified(isIconified > 0 ? true : false);
	};

	auto maximizeCallback = [](GLFWwindow* winPtr, int isMaximized) {
		Window& window = Application::get().getWindow();
		if (window.listener != nullptr)
			window.listener->windowMaximized(isMaximized > 0 ? true : false);
	};

	auto refreshCallback = [](GLFWwindow* winPtr) {
		Window& window = Application::get().getWindow();
		if (window.listener != nullptr)
			window.listener->windowRefresh();
	};

	auto frameBufferSizeCallback = [](GLFWwindow* winPtr, int width, int height) {
		Window& window = Application::get().getWindow();
		if (window.listener != nullptr)
			window.listener->windowFrameBufferSize(width, height);
	};

	//sets the corresponding callback to GLFW
	glfwSetWindowPosCallback(winPtr, positionCallback);
	glfwSetWindowSizeCallback(winPtr, sizeCallback);
	glfwSetWindowCloseCallback(winPtr, closeCallback);
	glfwSetWindowFocusCallback(winPtr, focusCallback);
	glfwSetWindowIconifyCallback(winPtr, iconifyCallback);
	glfwSetWindowRefreshCallback(winPtr, refreshCallback);
	glfwSetWindowMaximizeCallback(winPtr, maximizeCallback);
	glfwSetFramebufferSizeCallback(winPtr, frameBufferSizeCallback);
}

