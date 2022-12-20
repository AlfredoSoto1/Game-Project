#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
using namespace std;

#include "Application/App.h"

#include "Display/Window.h"

#include "Settings/WindowSettings.h"

#include "SceneUtils/Scene.h"
#include "SceneUtils/SceneManager.h"

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
	TestScene* scene1 = new TestScene();
	
	//Create Application
	Application::App app;

	app.getWindow().getWindowSettings().setTitle("First Display");

	app.getSceneManager().addScene(scene1);

	app.launch();
}