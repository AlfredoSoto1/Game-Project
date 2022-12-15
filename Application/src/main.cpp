

#define GLEW_STATIC

#include "graphics/components/display/Window.h"

int main() {
	Display::Window win("First Display", 1280, 720);

	win.initWindow();
}