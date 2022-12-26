/*
*	External
*/
#include <GLFW/glfw3.h>
#include <iostream>

/*
	Application
*/
#include "AppProgram/Program/AppControl/App.h"
using namespace Application;

/*
	Window
*/
#include "AppDisplay/Display/Window.h"
using namespace Display;

/*
	Peripherals
*/
#include "AppEquipment/Mouse.h"
#include "AppEquipment/Equipments.h"
using namespace Equipment;

/*
	Callback
*/
#include "MouseCallback.h"
using namespace Callback;

/*
	Settings
*/
#include "AppSettings/MouseSettings.h"
#include "AppSettings/WindowSettings.h"

using namespace Settings;

#define TO_APPLICATION(x) *static_cast<App*>(glfwGetWindowUserPointer(x));

MouseCallback::MouseCallback(App* _app) {
	
	glfwSetWindowUserPointer(_app->getWindow(), _app); //User Application pointer to GLFW

	auto dropCallback = [](GLFWwindow* winPtr, int _pathCount, const char** _paths) {
		App& app = TO_APPLICATION(winPtr);
		app.getEquipments().getMouse().getSettings().setDropPath(_pathCount, _paths);
	};

	auto enterCallback = [](GLFWwindow* winPtr, int isInside) {
		App& app = TO_APPLICATION(winPtr);

	};

	auto clickCallback = [](GLFWwindow* winPtr, int button, int action, int mods) {
		App& app = TO_APPLICATION(winPtr);
		app.getEquipments().getMouse().getSettings().getButtons()[button] = action != GLFW_RELEASE;
	};

	auto scrollCallback = [](GLFWwindow* winPtr, double xOffset, double yOffset) {
		App& app = TO_APPLICATION(winPtr);
		app.getEquipments().getMouse().getSettings().setScrollOffset(xOffset, yOffset);
	};

	auto positionCallback = [](GLFWwindow* winPtr, double xpos, double ypos) {
		App& app = TO_APPLICATION(winPtr);

		app.getEquipments().getMouse().getSettings().setMousePosition(xpos, ypos);

		app.getEquipments().getMouse().getSettings().setMousePositionNormalized(
			(xpos * 2.0) / app.getWindow().getSettings().getWidth() - 1.0,
			-(ypos * 2.0) / app.getWindow().getSettings().getHeight() + 1.0
		);
	};

	glfwSetDropCallback(_app->getWindow(), dropCallback);
	glfwSetScrollCallback(_app->getWindow(), scrollCallback);
	glfwSetCursorEnterCallback(_app->getWindow(), enterCallback);
	glfwSetMouseButtonCallback(_app->getWindow(), clickCallback);
	glfwSetCursorPosCallback(_app->getWindow(), positionCallback);
}
