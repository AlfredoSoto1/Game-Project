#pragma once

#include "Framework/SceneManager/Scene.h"
using namespace SceneControl;

#include "Graphics/Render/Renderer.h"
using namespace Render;

#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"
#include "Utils/Buffers/IndexBuffer.h"
#include "Utils/Buffers/VertexArray.h"
#include "Utils/Buffers/VertexBuffer.h"
#include "Utils/Buffers/VirtualBuffer.h"
#include "Utils/Geometry/Mesh.h"
using namespace MathsUtils;
using namespace BufferUtils;
using namespace GeometryUtils;

#include "../MarchingCubes/ChunkRenderer.h"
#include "../MarchingCubes/ChunkBuilder.h"

void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

void checkError() {
	while (GLenum error = glGetError())
		std::cout << "[GL ERROR]: " << error << std::endl;
}

class OverworldScene : public Scene {
private:

	Renderer renderer;
	ChunkShader* shader;
	ChunkBuilder* chunkBuilder;

public:
	OverworldScene() 
		: Scene()
	{

	}

	void init() {
		shader = new ChunkShader();
		chunkBuilder = new ChunkBuilder();
	}

	void load()  {
	
	}

	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		renderer.render(chunkBuilder->singleModel->getVao(), *shader);
	}

	void update() {
	}

	void unload()  {
	
	}

	void dispose() {
		renderer.dispose();

		delete shader;

		delete chunkBuilder;
	}

};