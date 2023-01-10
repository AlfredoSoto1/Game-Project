#include <GLFW/glfw3.h>
#include <iostream>

#include "Mouse.h"

#include "Core/Application.h"

#include "Gui/Window.h"
#include "Gui/WindowSettings.h"

using namespace Uranium;

Mouse::Mouse(Window* _window)
	: cursor(_window)
{
	auto dropCallback = [](GLFWwindow* winPtr, int _pathCount, const char** _paths) {
		Mouse& mouse = Application::get().getMouse();
	};

	auto enterCallback = [](GLFWwindow* winPtr, int isInside) {
		Mouse& mouse = Application::get().getMouse();
		mouse.getCursor().isActive = isInside > 0 ? true : false;
	};

	auto clickCallback = [](GLFWwindow* winPtr, int button, int action, int mods) {
		Mouse& mouse = Application::get().getMouse();
		Cursor& cursor = mouse.getCursor();

		mouse.mouseButtons[button] = action != GLFW_RELEASE;
	};

	auto scrollCallback = [](GLFWwindow* winPtr, double xOffset, double yOffset) {
		Mouse& mouse = Application::get().getMouse();
	};

	auto positionCallback = [](GLFWwindow* winPtr, double xpos, double ypos) {
		Window& window = Application::get().getWindow();
		Mouse& mouse = Application::get().getMouse();
		Cursor& cursor = mouse.getCursor();

		cursor.changePosition(xpos, ypos);
		cursor.changeNormPosition((xpos * 2.0) / window.getSettings().getWidth() - 1.0, -(ypos * 2.0) / window.getSettings().getHeight() + 1.0);
	};

	glfwSetDropCallback(*_window, dropCallback);
	glfwSetScrollCallback(*_window, scrollCallback);
	glfwSetCursorPosCallback(*_window, positionCallback);
	glfwSetCursorEnterCallback(*_window, enterCallback);
	glfwSetMouseButtonCallback(*_window, clickCallback);

	mouseButtons = new bool[GLFW_MOUSE_BUTTON_LAST];
}

Mouse::~Mouse() {
	delete[] mouseButtons;
}

Cursor& Mouse::getCursor() {
	return cursor;
}

void Mouse::update() {
	
}

bool Mouse::isButtonDown(int button) {
	if (button < 0)
		return false;
	return mouseButtons[button] ? true : false;
}

int Mouse::isMouseToggled(int _button) {
	return 0;
}
