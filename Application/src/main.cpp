#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
using namespace std;

#define UR_OPENGL
#include "Engine.h"

#include "UraniumApi.h"

#include "Uranium/Application/Application.h"
#include "Uranium/Application/AppProgram.h"

#include "Uranium/Application/Devices/Window.h"
#include "Uranium/Application/Settings/WindowSettings.h"

#include "Scenes/OverworldScene.h"
#include "Uranium/RenderEngine/SceneControl/Scene.h"

#include "Uranium/Utils/Materials/Material.h"
#include "Uranium/RenderEngine/Graphics/Renderer.h"
#include "Uranium/RenderEngine/SceneControl/Scene.h"
#include "Uranium/RenderEngine/ShaderControl/Shader.h"

#include "MarchingCubes/ChunkBuilder.h"
#include "MarchingCubes/ChunkRenderer.h"

using namespace Uranium;

/*
* TODO
*	+ Pre compiled headers and ASSERT macros
*	+ Restore application concept with window and scene and listeners
*	+ Camera Implementation
*	+ Key Listener / Object
*	+ Material and textures
*	+ Basic Marching cube algorithm / Displaying
*	+ Organize code
*/

class OverworldScene : public Scene {
private:
	ChunkBuilder* chunkBuilder;
	ChunkRenderer* chunkRenderer;

public:
	OverworldScene()
		: Scene("Overworld")
	{
		chunkRenderer = new ChunkRenderer();

		chunkBuilder = new ChunkBuilder();
		chunkBuilder->create();
	}
	~OverworldScene() {
		delete chunkBuilder;
		delete chunkRenderer;
	}
	void load() {

	}
	void unload() {

	}
	void draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		chunkRenderer->render(*chunkBuilder->model, Material());
	}
	void update() {

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