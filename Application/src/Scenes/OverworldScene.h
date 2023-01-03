#pragma once

#include "Framework/SceneManager/Scene.h"
using namespace SceneControl;

#include "Graphics/Render/Renderer.h"
using namespace Render;

#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"
using namespace MathsUtils;

#include "Utils/Buffers/IndexBuffer.h"
#include "Utils/Buffers/VertexBuffer.h"
#include "Utils/Buffers/VirtualBuffer.h"
using namespace BufferUtils;

#include "Utils/Geometry/Mesh.h"
#include "Utils/Geometry/Model.h"
using namespace GeometryUtils;

#include "../MarchingCubes/ChunkBuilder.h"
#include "../MarchingCubes/ChunkShader.h"
#include "../MarchingCubes/ComputeShader.h"

/*
* TODO
*	+ Compute Shaders
*	+ Shader Storage Buffers
*	+ Improve Buffers (Ibo, SSBo, Vbo, Vao)
*	+ Camera Implementation
*	+ Key Listener / Object
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

	ChunkShader* shader;
	ComputeShader* compShader;

	Renderer* renderer;

public:
	OverworldScene() 
		: Scene()
	{

	}

	void init() {

		renderer = new Renderer();

		shader = new ChunkShader();
		shader->load();

		chunkBuilder = new ChunkBuilder();

		chunkBuilder->create();

		compShader = new ComputeShader();
		compShader->load();

	}

	void load()  {
		
	}

	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		//compShader->bind();
		//compShader->update();
		//compShader->unbind();

		renderer->render(*chunkBuilder->model, *shader);
	}

	void update() {
		
	}

	void unload()  {
	
	}

	void dispose() {
		shader->unload();
		compShader->unload();

		delete chunkBuilder;
		delete shader;
		delete renderer;
	}

};
