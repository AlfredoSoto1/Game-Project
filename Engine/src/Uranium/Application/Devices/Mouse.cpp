#include <GLFW/glfw3.h>
#include <iostream>

#include "Mouse.h"
#include "Window.h"
#include "Uranium/Application/Application.h"
#include "Uranium/Application/Settings/MouseSettings.h"
#include "Uranium/Application/Settings/WindowSettings.h"
#include "Uranium/Application/Listeners/MouseListener.h"

using namespace Uranium;

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
		Mouse& mouse = Application::get().getMouse();
		if (mouse.listener != nullptr) {
			mouse.listener->mouseDrop(_pathCount, _paths);
		}
	};

	auto enterCallback = [](GLFWwindow* winPtr, int isInside) {
		Mouse& mouse = Application::get().getMouse();
		if (mouse.listener != nullptr) {
			mouse.listener->mouseEnterWindow(isInside > 0 ? true : false);
		}
	};

	auto clickCallback = [](GLFWwindow* winPtr, int button, int action, int mods) {
		Mouse& mouse = Application::get().getMouse();

		MouseSettings& settings = mouse.getSettings();
		settings.getButtons()[button] = action != GLFW_RELEASE;
		
		settings.currentMods = mods;
		settings.currentButton = button;

		if (action != GLFW_RELEASE) {
			if (mouse.listener != nullptr) {
				mouse.listener->mouseClickedButton(button, mods, settings.getX(), settings.getY());
			}
		}
		else {
			if (mouse.listener != nullptr) {
				mouse.listener->mouseReleasedButton(button, mods, settings.getX(), settings.getY());
			}
		}

	};

	auto scrollCallback = [](GLFWwindow* winPtr, double xOffset, double yOffset) {
		Mouse& mouse = Application::get().getMouse();
		mouse.getSettings().setScrollOffset(xOffset, yOffset);

		if (mouse.listener != nullptr) {
			mouse.listener->mouseScrollButton(xOffset, yOffset);
		}
	};

	auto positionCallback = [](GLFWwindow* winPtr, double xpos, double ypos) {
		Window& window = Application::get().getWindow();
		Mouse& mouse = Application::get().getMouse();

		mouse.getSettings().setMousePosition(xpos, ypos);

		mouse.getSettings().setMousePositionNormalized(
			(xpos * 2.0) / window.getSettings().getWidth() - 1.0,
			-(ypos * 2.0) / window.getSettings().getHeight() + 1.0
		);

		if (mouse.listener != nullptr) {
			mouse.listener->mouseMoved(xpos, ypos);
		}
	};

	Window& window = Application::get().getWindow();

	glfwSetDropCallback(window, dropCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorEnterCallback(window, enterCallback);
	glfwSetMouseButtonCallback(window, clickCallback);
	glfwSetCursorPosCallback(window, positionCallback);
}
