#include "WindowListener.h"

#include <GLFW/glfw3.h>
#include <iostream>

#include "graphics/settings/WindowSettings.h"
#include "graphics/components/display/Window.h"

using namespace Display;
using namespace Listener;

WindowListener::WindowListener(Window* window) {
	glfwSetWindowUserPointer(*window, window);

	auto positionCallback = [](GLFWwindow* winPtr, int xpos, int ypos) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		window.getSettings().uninit();
		window.getSettings().setPosition(xpos, ypos);
		window.getSettings().apply();
		if (window.getSettings().isDynamicUpdate()) {
			window.render(true);
		}
	};

	auto sizeCallback = [](GLFWwindow* winPtr, int width, int height) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		window.getSettings().uninit();
		window.getSettings().setSize(width, height);
		window.getSettings().apply();
	};

	auto closeCallback = [](GLFWwindow* winPtr) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		if (window.getWindowListener().closeListener != nullptr)
			window.getWindowListener().closeListener(&window);
	};

	auto focusCallback = [](GLFWwindow* winPtr, int isFocused) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		if (window.getWindowListener().focusListener != nullptr)
			window.getWindowListener().focusListener(&window, isFocused);
	};

	auto iconifyCallback = [](GLFWwindow* winPtr, int isIconified) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		if (window.getWindowListener().iconifyListener != nullptr)
			window.getWindowListener().iconifyListener(&window, isIconified);
	};

	auto maximizeCallback = [](GLFWwindow* winPtr, int isMaximized) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		if (window.getWindowListener().maximizeListener != nullptr)
			window.getWindowListener().maximizeListener(&window, isMaximized);
	};

	auto refreshCallback = [](GLFWwindow* winPtr) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		if (window.getSettings().isDynamicUpdate())
			window.render(true);
	};

	//sets the corresponding callback to GLFW
	glfwSetWindowPosCallback(*window, positionCallback);
	glfwSetWindowSizeCallback(*window, sizeCallback);
	glfwSetWindowCloseCallback(*window, closeCallback);
	glfwSetWindowFocusCallback(*window, focusCallback);
	glfwSetWindowIconifyCallback(*window, iconifyCallback);
	glfwSetWindowRefreshCallback(*window, refreshCallback);
	glfwSetWindowMaximizeCallback(*window, maximizeCallback);
}

WindowListener::~WindowListener() {

}