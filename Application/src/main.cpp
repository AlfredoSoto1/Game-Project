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

#include "BufferUtils/BufferE.h"
#include "BufferUtils/VertexBuffer.h"

using namespace BufferUtils;

#include "Maths/vec2.h"
#include "Maths/vec3.h"
#include "Maths/vec4.h"
using namespace Maths;

#include "MemoryUtils/Mesh.h"

using namespace MemoryUtils;
#include "Graphics/ShaderProgram.h"

using namespace Graphics;

static void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

static void checkError() {
	while (GLenum error = glGetError()) {
		printf("[GL ERROR]: %x, %i \n", error, error);
	}
}

class TestScene : public Scene {
public:

	TestScene() 
		: Scene() 
	{

	}

	struct Vertex {
		vec3 position = vec3(0.0);
		vec4 color = vec4(0.0);
	};

	VertexBuffer<Vertex, unsigned int>* buffer;

	uint32_t vao;
	uint32_t ibo;
	uint32_t vbo;

	Mesh* mesh;

	ShaderProgram* shader;

	void init() {

		unsigned int indices[3] = {
			0, 1, 2,
		};

		float positions[9] = {
			-0.5f, -0.5f, 1.0f,
			 0.5f, -0.5f, -1.0f,
			 0.5f,  0.5f, -1.0f,
		};

		//buffer = new VertexBuffer<Vertex, unsigned int>(2);

		//buffer->pushBack({ vec3(-0.5f, -0.5f, -1.0f), vec4(1.0, 0.0, 0.0, 1.0)});
		//buffer->pushBack({ vec3( 0.5f, -0.5f, -1.0f), vec4(0.0, 1.0, 0.0, 1.0)});
		//buffer->pushBack({ vec3( 0.5f,  0.5f, -1.0f), vec4(0.0, 0.0, 1.0, 1.0)});

		//buffer->fit();

		//mesh = new Mesh(2, GL_STATIC_DRAW);

		//mesh->createIndexBuffer(buffer->indexCount(), buffer->indexSize(), buffer->getIndices());
		//mesh->createVertexBuffer(buffer->vertexCountSize(), buffer->getVertices());
		////mesh->setVertexBuffer(*buffer);

		//mesh->setAttribPointer(0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		//mesh->setAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		clearError();
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		checkError();


		clearError();
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positions, GL_STATIC_DRAW);
		checkError();

		clearError();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		checkError();

		glBindVertexArray(0);


		const char* vert = "src/testV.glsl";
		const char* frag = "src/testF.glsl";

		const char* paths[2] = { vert, frag };

		shader = new ShaderProgram(2, paths);
	}

	void load() {

	}

	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		shader->onProgram();

		clearError();
		//mesh->bind();
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glEnableVertexAttribArray(0);

		glEnable(GL_DEPTH_TEST);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		glDisable(GL_DEPTH_TEST);

		//mesh->unbind();

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		checkError();

		shader->offProgram();
	}

	void update() {
	}

	void unload() {
	}

	void dispose() {
		delete mesh;
		delete buffer;

		delete shader;
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