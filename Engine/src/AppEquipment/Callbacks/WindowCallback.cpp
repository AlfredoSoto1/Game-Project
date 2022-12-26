/*
*	External
*/
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

/*
	Application
*/
#include "AppProgram/Program/AppControl/App.h"

using namespace Application;
/*
	Display
*/
#include "AppDisplay/Display/Window.h"

using namespace Display;

/*
	Callbacks
*/
#include "WindowCallback.h"

using namespace Callback;

/*
	Settings
*/
#include "AppSettings/WindowSettings.h"

using namespace Settings;

#define TO_APPLICATION(x) *static_cast<App*>(glfwGetWindowUserPointer(x));

WindowCallback::WindowCallback(App* _app) {
	glfwSetWindowUserPointer(_app->getWindow(), _app);

	auto positionCallback = [](GLFWwindow* winPtr, int xpos, int ypos) {
		App& app = TO_APPLICATION(winPtr);
		app.getWindow().getSettings().changePosition(xpos, ypos);
	};

	auto sizeCallback = [](GLFWwindow* winPtr, int width, int height) {
		App& app = TO_APPLICATION(winPtr);
		app.getWindow().getSettings().changeSize(width, height);
	};

	auto closeCallback = [](GLFWwindow* winPtr) {
		App& app = TO_APPLICATION(winPtr);
	};

	auto focusCallback = [](GLFWwindow* winPtr, int isFocused) {
		App& app = TO_APPLICATION(winPtr);
	};

	auto iconifyCallback = [](GLFWwindow* winPtr, int isIconified) {
		App& app = TO_APPLICATION(winPtr);
	};

	auto maximizeCallback = [](GLFWwindow* winPtr, int isMaximized) {
		App& app = TO_APPLICATION(winPtr);
	};

	auto refreshCallback = [](GLFWwindow* winPtr) {
		App& app = TO_APPLICATION(winPtr);
	};

	auto frameBufferSizeCallback = [](GLFWwindow* winPtr, int width, int height) {
		App& app = TO_APPLICATION(winPtr);
	};

	//sets the corresponding callback to GLFW
	glfwSetWindowPosCallback(_app->getWindow(), positionCallback);
	glfwSetWindowSizeCallback(_app->getWindow(), sizeCallback);
	glfwSetWindowCloseCallback(_app->getWindow(), closeCallback);
	glfwSetWindowFocusCallback(_app->getWindow(), focusCallback);
	glfwSetWindowIconifyCallback(_app->getWindow(), iconifyCallback);
	glfwSetWindowRefreshCallback(_app->getWindow(), refreshCallback);
	glfwSetWindowMaximizeCallback(_app->getWindow(), maximizeCallback);
	glfwSetFramebufferSizeCallback(_app->getWindow(), frameBufferSizeCallback);
}
