#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
using namespace std;

#include "AppProgram/Program/AppControl/App.h"

#include "AppDisplay/Display/Window.h"

#include "AppSettings/WindowSettings.h"

#include "AppProgram/Program/SceneControl/Scene.h"
#include "AppProgram/Program/SceneControl/SceneManager.h"

using namespace SceneUtils;

#include "AppProgram/Utils/Buffers/BufferE.h"
#include "AppProgram/Utils/Buffers/VertexBuffer.h"

using namespace BufferUtils;

#include "AppProgram/Utils/Maths/vec2.h"
#include "AppProgram/Utils/Maths/vec3.h"
#include "AppProgram/Utils/Maths/vec4.h"
using namespace MathsUtils;

#include "AppProgram/Utils/Geometry/Mesh.h"

using namespace GeometryUtils;

#include "AppDisplay/Graphics/ShaderControl/ShaderProgram.h"
using namespace Graphics;

#include "AppEquipment/Listeners/MouseListener.h"
using namespace Listener;

#include "AppEquipment/Equipments.h"
#include "AppEquipment/Mouse.h"
#include "AppEquipment/Listeners/WindowListener.h"
using namespace Equipment;

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

	app.getWindow().getSettings().setTitle("First Display");

	app.getSceneManager().addScene(scene1);

	app.launch();

	delete scene1;

}