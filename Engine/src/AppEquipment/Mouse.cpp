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
	Settings
*/
#include "AppSettings/MouseSettings.h"
#include "AppSettings/WindowSettings.h"
using namespace Settings;

/*
	Listener
*/
#include "AppEquipment/Listeners/MouseListener.h"
using namespace Listener;

#define TO_APPLICATION(x) *static_cast<App*>(glfwGetWindowUserPointer(x));

Mouse::Mouse(App* _appRef) {
	settings = new MouseSettings();
	initCallback(_appRef);
}

Mouse::~Mouse() {
	delete settings;
}

MouseSettings& Mouse::getSettings() {
	return *settings;
}

Listener::MouseListener* Mouse::getListener() {
	return listener;
}

void Mouse::setListener(Listener::MouseListener* _mouseListener) {
	this->listener = _mouseListener;
}

void Mouse::update() {
	if (settings->isButtonDown(settings->currentButton)) {
		if (listener != nullptr) {
			listener->mousePressedButton(settings->currentButton, settings->currentMods, settings->getX(), settings->getY());
		}
	}
}

void Mouse::initCallback(App* _appRef) {
	auto dropCallback = [](GLFWwindow* winPtr, int _pathCount, const char** _paths) {
		App& app = TO_APPLICATION(winPtr);
		if (app.getEquipments().getMouse().getListener() != nullptr) {
			app.getEquipments().getMouse().getListener()->mouseDrop(_pathCount, _paths);
		}
	};

	auto enterCallback = [](GLFWwindow* winPtr, int isInside) {
		App& app = TO_APPLICATION(winPtr);

		if (app.getEquipments().getMouse().getListener() != nullptr) {
			app.getEquipments().getMouse().getListener()->mouseEnterWindow(isInside > 0 ? true : false);
		}
	};

	auto clickCallback = [](GLFWwindow* winPtr, int button, int action, int mods) {
		App& app = TO_APPLICATION(winPtr);

		MouseSettings& settings = app.getEquipments().getMouse().getSettings();
		settings.getButtons()[button] = action != GLFW_RELEASE;
		
		settings.currentMods = mods;
		settings.currentButton = button;

		if (action != GLFW_RELEASE) {
			if (app.getEquipments().getMouse().getListener() != nullptr) {
				app.getEquipments().getMouse().getListener()->mouseClickedButton(button, mods, settings.getX(), settings.getY());
			}
		}
		else {
			if (app.getEquipments().getMouse().getListener() != nullptr) {
				app.getEquipments().getMouse().getListener()->mouseReleasedButton(button, mods, settings.getX(), settings.getY());
			}
		}

	};

	auto scrollCallback = [](GLFWwindow* winPtr, double xOffset, double yOffset) {
		App& app = TO_APPLICATION(winPtr);
		app.getEquipments().getMouse().getSettings().setScrollOffset(xOffset, yOffset);

		if (app.getEquipments().getMouse().getListener() != nullptr) {
			app.getEquipments().getMouse().getListener()->mouseScrollButton(xOffset, yOffset);
		}
	};

	auto positionCallback = [](GLFWwindow* winPtr, double xpos, double ypos) {
		App& app = TO_APPLICATION(winPtr);

		app.getEquipments().getMouse().getSettings().setMousePosition(xpos, ypos);

		app.getEquipments().getMouse().getSettings().setMousePositionNormalized(
			(xpos * 2.0) / app.getWindow().getSettings().getWidth() - 1.0,
			-(ypos * 2.0) / app.getWindow().getSettings().getHeight() + 1.0
		);

		if (app.getEquipments().getMouse().getListener() != nullptr) {
			app.getEquipments().getMouse().getListener()->mouseMoved(xpos, ypos);
		}
	};

	glfwSetDropCallback(_appRef->getWindow(), dropCallback);
	glfwSetScrollCallback(_appRef->getWindow(), scrollCallback);
	glfwSetCursorEnterCallback(_appRef->getWindow(), enterCallback);
	glfwSetMouseButtonCallback(_appRef->getWindow(), clickCallback);
	glfwSetCursorPosCallback(_appRef->getWindow(), positionCallback);
}
