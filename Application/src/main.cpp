#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
using namespace std;

#include "Application/App.h"

#include "Display/Window.h"

#include "Settings/WindowSettings.h"

#include "SceneUtils/Scene.h"
#include "SceneUtils/SceneManager.h"

#include "SceneUtils/Mesh.h"
#include "SceneUtils/Model.h"

using namespace SceneUtils;

#include "BufferUtils/Vertex.h"
#include "BufferUtils/VertexBuffer.h"

using namespace BufferUtils;

class TestScene : public Scene {
public:

	TestScene() 
		: Scene() 
	{

	}

	void init() {

		Vertex<float> vertex;
		vertex.set(0.0);
	
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
	Application::App app = Application::App();

	app.getWindow().getWindowSettings().setTitle("First Display");

	app.getSceneManager().addScene(scene1);

	app.launch();

	delete scene1;
}