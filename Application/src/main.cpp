

#define GLEW_STATIC

#include <iostream>
using namespace std;

#include "Display/Components/Window.h"

#include "Display/Graphics/SceneUtils/Stage.h"

#include "Maths/vec2.h"
#include "Maths/vec3.h"
using namespace Maths;


int main() {

	vec2 v1(4.0);
	vec3 v2(5.0);

	cout << v2[0] << endl;


	//Display::Window win("First Display", 1280, 720);

	//
	//StageUtils::Stage* stage = new StageUtils::Stage();
	////stage->addScene(RenderTest());

	//win.attach(stage);
	//win.start();

	//delete stage;
}