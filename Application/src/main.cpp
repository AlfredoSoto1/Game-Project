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

	Mesh* mesh;

	ShaderProgram* shader;

	void init() {

		buffer = new VertexBuffer<Vertex, unsigned int>(2);

		buffer->pushBack({ vec3(-0.5f, -0.5f, -1.0f), vec4(1.0, 0.0, 0.0, 1.0)});
		buffer->pushBack({ vec3( 0.5f, -0.5f, -1.0f), vec4(0.0, 1.0, 0.0, 1.0)});
		buffer->pushBack({ vec3( 0.5f,  0.5f, -1.0f), vec4(0.0, 0.0, 1.0, 1.0)});

		buffer->fit();

		mesh = new Mesh(2, GL_STATIC_DRAW);

		mesh->setVertexBuffer(*buffer);

		mesh->setAttribPointer(0, 3, GL_FLOAT, sizeof(Vertex), (const void*)0);
		mesh->setAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, color));

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

		mesh->bind();

		glEnable(GL_DEPTH_TEST);

		glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);

		glDisable(GL_DEPTH_TEST);

		mesh->unbind();

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