#define GLEW_STATIC
#include <GL/glew.h>
#include <cstdlib>
#include <vector>

#include "UraniumApi.h"

#include "Core/AppProgram.h"
#include "Core/Application.h"

#include "Gui/Window.h"
#include "Gui/WindowSettings.h"
#include "Devices/Mouse.h"

#include "Scene/Scene.h"
#include "Scene/Camera.h"
#include "Scene/Entity.h"
#include "Scene/FPCamera.h"
#include "Scenes/OverworldScene.h"

#include "Renderer/Asset.h"
#include "Renderer/Texture.h"
#include "Renderer/Material.h"
#include "Renderer/Renderer.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Shader.h"

#include "MarchingCubes/ChunkBuilder.h"

using namespace Uranium;

//https://ffainelli.github.io/openal-example/

//https://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade

//https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetActiveUniform.xhtml

/*
* TODO
*	+ Basic Marching cube algorithm / Displaying
*	+ Organize code
* 
* Window -> and methods
* WindowProps -> window settings
* 
* Mouse -> and methods
* MouseProps -> mouse settings
*/

class OverworldScene : public Scene {
private:
	ChunkBuilder* chunkBuilder;

	std::vector<std::shared_ptr<Entity>> entities;
	
	std::shared_ptr<Asset> asset;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Material> material;
	

	Renderer* batchRenderer;
	std::shared_ptr<FPCamera> camera;
	std::shared_ptr<ShaderProgram> shader;
	std::shared_ptr<Shader> vertexShader;
	std::shared_ptr<Shader> fragmentShader;

public:
	OverworldScene()
		: Scene("Overworld")
	{
		// create mesh
		chunkBuilder = new ChunkBuilder();
		chunkBuilder->create();

		// create camera in curent scene
		camera = std::make_shared<FPCamera>(this);

		// create material
		texture = std::make_shared<Texture>("src/Texture.png");

		material = std::make_shared<Material>();
		material->setAlbedo(texture);

		// load to asset
		asset = std::make_shared<Asset>(chunkBuilder->model, material);

		// create shader
		vertexShader = std::make_shared<Shader>("src/testV.glsl", GL_VERTEX_SHADER);
		fragmentShader = std::make_shared<Shader>("src/testF.glsl", GL_FRAGMENT_SHADER);
		shader = std::make_shared<ShaderProgram>(vertexShader, fragmentShader);

		// create renderer
		batchRenderer = new Renderer(shader);

		for (int i = 0; i < 2; i++) {
			entities.push_back(std::make_shared<Entity>(asset, "Entity"));
			entities[i]->getRigidBody().getPosition().x = i;
			entities[i]->getRigidBody().getPosition().y = i;
			entities[i]->getRigidBody().getPosition().z = i;
			batchRenderer->push(entities[i]);
		}
		
	}
	~OverworldScene() {
		delete chunkBuilder;
		delete batchRenderer;

		entities.clear();
	}
	void load() {
		
	}
	void unload() {

	}
	void draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		//chunkRenderer->render(camera, *chunkBuilder->model, Material());

		batchRenderer->render(camera);
	}
	void update() {
		camera->update();

		// update all entities
		for (std::shared_ptr<Entity> entity : entities) {
			entity->update();
		}
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
