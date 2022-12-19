#define GLEW_STATIC

#include <GL/glew.h>

#include <iostream>
using namespace std;

#include "Settings/WindowSettings.h"

#include "Display/Components/Window.h"
#include "Display/Graphics/SceneUtils/Scene.h"
#include "Display/Graphics/SceneUtils/SceneManager.h"

using namespace SceneUtils;

class TestScene : public Scene {
public:
	TestScene() 
		: Scene() 
	{

	}

	void load() {
	}

	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}

	void update() {
	}

	void unload() {
	}

	void dispose() {
	}

};

int main() {

	Display::Window win("First Display", 1280, 720);
	
	TestScene* scene1 = new TestScene();

	win.getSceneManager().addScene(scene1);

	win.start();
}