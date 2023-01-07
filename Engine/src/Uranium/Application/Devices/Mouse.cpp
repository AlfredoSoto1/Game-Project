#include <GLFW/glfw3.h>
#include <iostream>

#include "Mouse.h"
#include "Window.h"
#include "Device.h"
#include "Uranium/Application/Application.h"
#include "Uranium/Application/Settings/MouseSettings.h"
#include "Uranium/Application/Settings/WindowSettings.h"
#include "Uranium/Framework/Listeners/MouseListener.h"

using namespace Uranium;

#define TO_APPLICATION(x) *static_cast<Application*>(glfwGetWindowUserPointer(x));

Mouse::Mouse() {
	settings = new MouseSettings();
	initCallback();
}

Mouse::~Mouse() {
	delete settings;
}

MouseSettings& Mouse::getSettings() {
	return *settings;
}

void Mouse::setListener(MouseListener* _mouseListener) {
	this->listener = _mouseListener;
}

void Mouse::update() {
	if (settings->isButtonDown(settings->currentButton)) {
		if (listener != nullptr) {
			listener->mousePressedButton(settings->currentButton, settings->currentMods, settings->getX(), settings->getY());
		}
	}
}

void Mouse::initCallback() {
	auto dropCallback = [](GLFWwindow* winPtr, int _pathCount, const char** _paths) {
		Application& app = TO_APPLICATION(winPtr);
		if (app.getDevice().getMouse().listener != nullptr) {
			app.getDevice().getMouse().listener->mouseDrop(_pathCount, _paths);
		}
	};

	auto enterCallback = [](GLFWwindow* winPtr, int isInside) {
		Application& app = TO_APPLICATION(winPtr);

		if (app.getDevice().getMouse().listener != nullptr) {
			app.getDevice().getMouse().listener->mouseEnterWindow(isInside > 0 ? true : false);
		}
	};

	auto clickCallback = [](GLFWwindow* winPtr, int button, int action, int mods) {
		Application& app = TO_APPLICATION(winPtr);

		MouseSettings& settings = app.getDevice().getMouse().getSettings();
		settings.getButtons()[button] = action != GLFW_RELEASE;
		
		settings.currentMods = mods;
		settings.currentButton = button;

		if (action != GLFW_RELEASE) {
			if (app.getDevice().getMouse().listener != nullptr) {
				app.getDevice().getMouse().listener->mouseClickedButton(button, mods, settings.getX(), settings.getY());
			}
		}
		else {
			if (app.getDevice().getMouse().listener != nullptr) {
				app.getDevice().getMouse().listener->mouseReleasedButton(button, mods, settings.getX(), settings.getY());
			}
		}

	};

	auto scrollCallback = [](GLFWwindow* winPtr, double xOffset, double yOffset) {
		Application& app = TO_APPLICATION(winPtr);
		app.getDevice().getMouse().getSettings().setScrollOffset(xOffset, yOffset);

		if (app.getDevice().getMouse().listener != nullptr) {
			app.getDevice().getMouse().listener->mouseScrollButton(xOffset, yOffset);
		}
	};

	auto positionCallback = [](GLFWwindow* winPtr, double xpos, double ypos) {
		Application& app = TO_APPLICATION(winPtr);

		app.getDevice().getMouse().getSettings().setMousePosition(xpos, ypos);

		app.getDevice().getMouse().getSettings().setMousePositionNormalized(
			(xpos * 2.0) / app.getWindow().getSettings().getWidth() - 1.0,
			-(ypos * 2.0) / app.getWindow().getSettings().getHeight() + 1.0
		);

		if (app.getDevice().getMouse().listener != nullptr) {
			app.getDevice().getMouse().listener->mouseMoved(xpos, ypos);
		}
	};

	Application& application = Application::get();

	glfwSetDropCallback(application.getWindow(), dropCallback);
	glfwSetScrollCallback(application.getWindow(), scrollCallback);
	glfwSetCursorEnterCallback(application.getWindow(), enterCallback);
	glfwSetMouseButtonCallback(application.getWindow(), clickCallback);
	glfwSetCursorPosCallback(application.getWindow(), positionCallback);
}
