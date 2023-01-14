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
#include "Renderer/BatchRenderer.h"

#include "MarchingCubes/ChunkShader.h"
#include "MarchingCubes/ChunkBuilder.h"
#include "MarchingCubes/ChunkRenderer.h"

using namespace Uranium;

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

	std::shared_ptr<Asset> asset;
	std::shared_ptr<Material> material;
	std::shared_ptr<ShaderProgram> shader;

	std::shared_ptr<Texture> texture;
	
	std::vector<Entity> entities;

	FPCamera* camera;
	BatchRenderer* batchRenderer;

public:
	OverworldScene()
		: Scene("Overworld")
	{
		// create camera in curent scene
		camera = new FPCamera(this);

		// create a simple albedo texture
		texture = std::make_shared<Texture>("src/Texture.png");

		// create and load material
		material = std::make_shared<Material>();

		material->setAlbedo("grass", texture);

		// create ShaderProgram
		shader = std::make_shared<ShaderProgram>();

		// load to asset
		asset = std::make_shared<Asset>();

		asset->setMaterial(material);

		// create renderer
		batchRenderer = new BatchRenderer();

		// create mesh
		chunkBuilder = new ChunkBuilder();
		chunkBuilder->create();



		for (int i = 0; i < 2; i++) {

			entities.emplace_back(Entity(asset, "Entity"));

			float x = rand() % 50;
			float y = rand() % 50;
			float z = rand() % 50;

			vec3& pos = entities[i].getRigidBody().getPosition();

			pos.x = x;
			pos.y = y;
			pos.z = z;

			// pass entities to renderer
			batchRenderer->submit(&entities[i]);
		}
	}
	~OverworldScene() {
		delete camera;
		//delete chunkShader;
		delete chunkBuilder;
		//delete chunkRenderer;

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