#pragma once

#include "AppProgram/Program/SceneControl/Scene.h"
using namespace SceneControl;

#include "../MarchingCubes/ChunkRenderer.h"

class OverworldScene : public Scene {
private:

	ChunkRenderer renderer;

public:
	OverworldScene() 
		: Scene()
	{

	}

	void init() {
		renderer.init();

	}

	void load()  {
	
	}

	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		renderer.render();
	}

	void update() {
		renderer.update();
	}

	void unload()  {
	
	}

	void dispose() {
		renderer.dispose();
		
	}

};