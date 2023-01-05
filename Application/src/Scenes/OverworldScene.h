#pragma once

#include "Framework/SceneManager/Scene.h"
using namespace SceneControl;

#include "Graphics/Render/Renderer.h"

#include "Utils/Buffers/IndexBuffer.h"
#include "Utils/Buffers/VertexBuffer.h"

#include "Utils/Geometry/Mesh.h"
#include "Utils/Geometry/Model.h"
#include "Shader/Material.h"
using namespace Uranium;

#include "../MarchingCubes/ChunkBuilder.h"
#include "../MarchingCubes/ChunkRenderer.h"

/*
* TODO
*	+ Improve Buffers (Ibo, SSBo, Vbo, Vao)
*	+ Camera Implementation
*	+ Key Listener / Object
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
