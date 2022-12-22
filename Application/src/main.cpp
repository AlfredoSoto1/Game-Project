#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
using namespace std;

#include "Application/App.h"

#include "Display/Window.h"

#include "Settings/WindowSettings.h"

#include "SceneUtils/Scene.h"
#include "SceneUtils/SceneManager.h"

#include "SceneUtils/Mesh.h"
#include "SceneUtils/Model.h"

using namespace SceneUtils;

#include "BufferUtils/BufferE.h"
#include "BufferUtils/VertexBuffer.h"

using namespace BufferUtils;

#include "Maths/vec2.h"
#include "Maths/vec3.h"
#include "Maths/vec4.h"
using namespace Maths;

class TestScene : public Scene {
public:

	TestScene() 
		: Scene() 
	{

	}

	void init() {

		struct Vertex {
			vec2 position = vec2(0.0);
			vec3 color = vec3(0.0);
		};

		Vertex vert1 = {vec2(-0.5f, -0.5f), vec3(1.0)};
		Vertex vert2 = {vec2( 0.0f,  0.5f), vec3(1.0)};
		Vertex vert3 = {vec2( 0.5f, -0.5f), vec3(1.0)};

		VertexBuffer<Vertex, unsigned int> buffer(2);

		auto repeatedVertices = [](const Vertex& _v, Vertex& _other) {
			if (_v.position.x == _other.position.x && _v.position.y == _other.position.y)
				return true;
			return false;
		};

		buffer.pushBack({ vec2(-0.5f, -0.5f), vec3(1.0) });
		buffer.pushBack({ vec2( 0.0f,  0.5f), vec3(1.0) });
		buffer.pushBack({ vec2( 0.5f, -0.5f), vec3(1.0) });

		buffer.emplaceBack(vec2(-0.5f, -0.5f), vec3(1.0));

		cout << "size: "			<< buffer.size() << "B"		<< endl;
		cout << "total: "			<< buffer.unallocSize() << "B" << endl;
		cout << "vertex count: "	<< buffer.vertexCount()		<< endl;
		cout << "index count: "		<< buffer.indexCount()		<< endl;
		cout << "vertex capacity: " << buffer.vertexCapacity()	<< endl;
		cout << "index capacity: "	<< buffer.indexCapacity()	<< endl;

	}

	void load() {

	}

	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();

	}

	void update() {
	}

	void unload() {
	}

	void dispose() {
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