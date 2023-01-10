#define GLEW_STATIC
#include <GL/glew.h>

#include "Engine.h"

#include "UraniumApi.h"
//#include "UraniumPch.h"

#include "Core/AppProgram.h"
#include "Core/Application.h"

#include "Gui/Window.h"
#include "Gui/WindowSettings.h"
#include "Devices/Mouse.h"

#include "Events/MouseListener.h"

#include "Scenes/OverworldScene.h"
#include "Scene/Scene.h"

#include "Renderer/Material.h"
#include "Renderer/Renderer.h"
#include "Scene/Camera.h"
#include "Scene/FPCamera.h"
#include "Renderer/Shader.h"

#include "MarchingCubes/ChunkBuilder.h"
#include "MarchingCubes/ChunkRenderer.h"

using namespace Uranium;

/*
* TODO
*	+ Key / mouse listener implementation
*	+ fix and organize
*	+ Better renderer
*	+ camera movement
*	+ Basic Marching cube algorithm / Displaying
*	+ Organize code
* 
* Window -> and methods
* WindowProps -> window settings
* 
* Mouse -> and methods
* MouseProps -> mouse settings
*/

class OverworldScene : public Scene {
private:
	ChunkBuilder* chunkBuilder;
	ChunkRenderer* chunkRenderer;

	FPCamera* camera;

public:
	OverworldScene()
		: Scene("Overworld")
	{
		camera = new FPCamera(this);

		chunkRenderer = new ChunkRenderer();

		chunkBuilder = new ChunkBuilder();
		chunkBuilder->create();
	}
	~OverworldScene() {
		delete chunkBuilder;
		delete chunkRenderer;
		delete camera;
	}
	void load() {

	}
	void unload() {

	}
	void draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		chunkRenderer->render(camera, *chunkBuilder->model, Material());
	}
	void update() {
		camera->update();
	}

};

class MainApp : public AppProgram {
public:
	
	OverworldScene* scene;

	void init() {
		Application::get().getWindow().getSettings().setTitle("My Game");
		scene = new OverworldScene();
		push_firstNewScene(scene);
	}

	void dispose() {
		delete scene;
	}
};

int main() {
	Application::start(new MainApp());
}