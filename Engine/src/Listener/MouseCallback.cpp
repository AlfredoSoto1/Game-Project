#include "MouseCallback.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Settings/MouseSettings.h"
#include "Settings/WindowSettings.h"
#include "Display/Components/Window.h"

using namespace Display;
using namespace Callback;
using namespace Settings;

#define TO_WINDOW(x) *static_cast<Window*>(glfwGetWindowUserPointer(x));

MouseCallback::MouseCallback(Display::Window* window) {
	glfwSetWindowUserPointer(*window, window);
	//auto dropCallback = [](GLFWwindow* _window, int _pathCount, const char** _paths) {
	//	//FIXME
	//	//display::Window& windowDisplay = *static_cast<display::Window*>(glfwGetWindowUserPointer(_window));
	//	//windowDisplay.mouseListener->pathCount = _pathCount;
	//	//windowDisplay.mouseListener->droppedPaths = _paths;
	//};

	auto enterCallback = [](GLFWwindow* winPtr, int isInside) {
		//Window* window = TO_WINDOW(winPtr);

	};

	auto clickCallback = [](GLFWwindow* winPtr, int button, int action, int mods) {
		Window& window = TO_WINDOW(winPtr);
		window.getMouseSettings().getButtons()[button] = action != GLFW_RELEASE;
	};

	auto scrollCallback = [](GLFWwindow* winPtr, double xOffset, double yOffset) {
		Window& window = TO_WINDOW(winPtr);
		window.getMouseSettings().setScrollOffset(xOffset, yOffset);
	};

	auto positionCallback = [](GLFWwindow* winPtr, double xpos, double ypos) {
		Window& window = TO_WINDOW(winPtr);

		window.getMouseSettings().setMousePosition(xpos, ypos);
		window.getMouseSettings().setMousePositionNormalized(
			(xpos * 2.0) / window.getSettings().getWidth() - 1.0,
			-(ypos * 2.0) / window.getSettings().getHeight() + 1.0
		);
	};

	//convert via operator overload Display to GLFWwindpw pointer
	//GLFWwindow* window = *(graphics::Display*)displayPtr;

	//sets the corresponding callback to GLFW
	//glfwSetDropCallback(window, dropCallback);
	glfwSetScrollCallback(*window, scrollCallback);
	glfwSetCursorEnterCallback(*window, enterCallback);
	glfwSetMouseButtonCallback(*window, clickCallback);
	glfwSetCursorPosCallback(*window, positionCallback);
}
