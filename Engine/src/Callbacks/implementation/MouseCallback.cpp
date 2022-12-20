/*
*	External
*/
#include <GLFW/glfw3.h>
#include <iostream>

/*
	Application
*/
#include "Application/App.h"
using namespace Application;

/*
	Window
*/
#include "Display/Window.h"
using namespace Display;

/*
	Peripherals
*/
#include "PeripheralsUtils/Mouse.h"
#include "PeripheralsUtils/Peripherals.h"
using namespace PeripheralsUtils;

/*
	Callback
*/
#include "Callbacks/MouseCallback.h"
using namespace Callback;

/*
	Settings
*/
#include "Settings/MouseSettings.h"
#include "Settings/WindowSettings.h"

using namespace Settings;

#define TO_APPLICATION(x) *static_cast<App*>(glfwGetWindowUserPointer(x));

MouseCallback::MouseCallback(App* _app) {
	
	glfwSetWindowUserPointer(_app->getWindow(), _app);

	auto dropCallback = [](GLFWwindow* winPtr, int _pathCount, const char** _paths) {
		App& app = TO_APPLICATION(winPtr);
		app.getPeripherals().getMouse().getSettings().setDropPath(_pathCount, _paths);
	};

	auto enterCallback = [](GLFWwindow* winPtr, int isInside) {
		App& app = TO_APPLICATION(winPtr);

	};

	auto clickCallback = [](GLFWwindow* winPtr, int button, int action, int mods) {
		App& app = TO_APPLICATION(winPtr);
		app.getPeripherals().getMouse().getSettings().getButtons()[button] = action != GLFW_RELEASE;
	};

	auto scrollCallback = [](GLFWwindow* winPtr, double xOffset, double yOffset) {
		App& app = TO_APPLICATION(winPtr);
		app.getPeripherals().getMouse().getSettings().setScrollOffset(xOffset, yOffset);
	};

	auto positionCallback = [](GLFWwindow* winPtr, double xpos, double ypos) {
		App& app = TO_APPLICATION(winPtr);

		app.getPeripherals().getMouse().getSettings().setMousePosition(xpos, ypos);

		app.getPeripherals().getMouse().getSettings().setMousePositionNormalized(
			(xpos * 2.0) / app.getWindow().getWindowSettings().getWidth() - 1.0,
			-(ypos * 2.0) / app.getWindow().getWindowSettings().getHeight() + 1.0
		);
	};

	glfwSetDropCallback(_app->getWindow(), dropCallback);
	glfwSetScrollCallback(_app->getWindow(), scrollCallback);
	glfwSetCursorEnterCallback(_app->getWindow(), enterCallback);
	glfwSetMouseButtonCallback(_app->getWindow(), clickCallback);
	glfwSetCursorPosCallback(_app->getWindow(), positionCallback);
}
