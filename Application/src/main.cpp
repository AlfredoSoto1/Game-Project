

#define GLEW_STATIC

#include "Display/Components/Window.h"

#include "Display/Graphics/Scene.h"
#include "Display/Graphics/SceneManager.h"

//#include "Display/Graphics/RenderProgram.h"

class RenderTest : public Graphics::Scene {
public:
	RenderTest() : Scene() {

	}

	~RenderTest() {

	}

	void init() {

	}

	void render() {

	}

	void update() {

	}

	void dispose() {

	}
};

int main() {
	Display::Window win("First Display", 1280, 720);

	win.loadScene(new RenderTest());
}