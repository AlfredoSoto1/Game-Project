#include "Keyboard.h"

#include <GLFW/glfw3.h>

#include "Core/Application.h"
#include "Gui/Window.h"

using namespace Uranium;

Keyboard::Keyboard(Window* _window) 
{
	auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Keyboard& keyboard = Application::get().getKeyboard();
		keyboard.keys[key] = action != GLFW_RELEASE;
	};

	auto charCallback = [](GLFWwindow* window, unsigned int codePoint) {

	};

	glfwSetKeyCallback(*_window, keyCallback);
	glfwSetCharCallback(*_window, charCallback);

	keys = new bool[GLFW_KEY_LAST];
	for (int i = 0; i < GLFW_KEY_LAST; i++)
		keys[i] = false;
}

Keyboard::~Keyboard() {
	delete[] keys;
}

void Keyboard::update() {

}

bool Keyboard::isKeyDown(int key) {
	return keys[key] ? true : false;
}

bool Keyboard::isKeyToggled(int key) {
	if (isKeyDown(key)) {
		if (!toggled) {
			toggled = true;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		toggled = false;
		return false;
	}
}

bool Keyboard::isKeyReleased(int key) {
	if (!isKeyDown(key)) {
		if (released) {
			released = false;
			return true;
		}
		return false;
	}
	else {
		released = true;
		return false;
	}
}

