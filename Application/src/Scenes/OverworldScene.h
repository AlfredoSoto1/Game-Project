#pragma once

#define UR_OPENGL
#include "Engine.h"

#include "Uranium/Application/Application.h"
#include "Uranium/Application/ApplicationRunner.h"

#include "Uranium/Application/Settings/WindowSettings.h"
#include "Uranium/Application/Devices/Window.h"

#include "Scenes/OverworldScene.h"
#include "Uranium/RenderEngine/SceneControl/Scene.h"
#include "Uranium/RenderEngine/SceneControl/SceneManager.h"
#include "Uranium/RenderEngine/ShaderControl/Shader.h"
#include "Uranium/RenderEngine/Graphics/Renderer.h"

#include "Uranium/Utils/Materials/Material.h"

using namespace Uranium;

#include "../MarchingCubes/ChunkBuilder.h"
#include "../MarchingCubes/ChunkRenderer.h"

/*
* TODO
*	+ Camera Implementation
*	+ Key Listener / Object
*	+ Pre compiled headers and ASSERT macros
*	+ Restore application concept with window and scene and listeners
*	+ Material and textures
*	+ Basic Marching cube algorithm / Displaying
*	+ Organize code
*/

void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

void checkError() {
	while (GLenum error = glGetError())
		std::cout << "[GL ERROR]: " << error << std::endl;
}

class OverworldScene : public Scene {
private:

	ChunkBuilder* chunkBuilder;

	ChunkRenderer* chunkRenderer;

public:
	OverworldScene() 
		: Scene()
	{

	}

	void init() {

		chunkRenderer = new ChunkRenderer();

		chunkBuilder = new ChunkBuilder();
		chunkBuilder->create();

	}

	void load()  {
		
	}

	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		//compShader->bind();
		//compShader->update();
		//compShader->unbind();

		chunkRenderer->render(*chunkBuilder->model, Material());
	}

	void update() {
		
	}

	void unload()  {
	
	}

	void dispose() {
		delete chunkBuilder;
		delete chunkRenderer;
	}

};
