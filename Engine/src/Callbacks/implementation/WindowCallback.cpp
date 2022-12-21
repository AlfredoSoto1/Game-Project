/*
*	External
*/
#include <GLFW/glfw3.h>
#include <iostream>

/*
	Display
*/
#include "Display/Window.h"

using namespace Display;

/*
	Callbacks
*/
#include "Callbacks/WindowCallback.h"

using namespace Callback;

/*
	Settings
*/
#include "Settings/WindowSettings.h"

using namespace Settings;

WindowCallback::WindowCallback(Window* window) {
	glfwSetWindowUserPointer(*window, window);

	auto positionCallback = [](GLFWwindow* winPtr, int xpos, int ypos) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		window.getWindowSettings().uninit();
		window.getWindowSettings().setPosition(xpos, ypos);
		window.getWindowSettings().apply();
		//if (window.getWindowSettings().isDynamicUpdate()) {
		//	window.pollEvents(GL_TRUE);
		//}
	};

	auto sizeCallback = [](GLFWwindow* winPtr, int width, int height) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		//window.getWindowSettings().uninit();
		//window.getWindowSettings().setSize(width, height);
		//window.getWindowSettings().apply();
	};

	auto closeCallback = [](GLFWwindow* winPtr) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
	};

	auto focusCallback = [](GLFWwindow* winPtr, int isFocused) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
	};

	auto iconifyCallback = [](GLFWwindow* winPtr, int isIconified) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
	};

	auto maximizeCallback = [](GLFWwindow* winPtr, int isMaximized) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
	};

	auto refreshCallback = [](GLFWwindow* winPtr) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(winPtr));
		//if (window.getWindowSettings().isDynamicUpdate())
		//	window.pollEvents(GL_TRUE);
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
