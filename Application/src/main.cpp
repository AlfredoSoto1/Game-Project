

#define GLEW_STATIC

#include "Display/Components/Window.h"

#include "Display/Graphics/SceneUtils/Stage.h"

int main() {
	Display::Window win("First Display", 1280, 720);

	
	StageUtils::Stage* stage = new StageUtils::Stage();
	//stage->addScene(RenderTest());

	win.attach(stage);
	win.start();

	delete stage;
}