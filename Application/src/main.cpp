#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
using namespace std;

#include "Uranium/Application/Application.h"
#include "Uranium/Application/ApplicationRunner.h"

#include "Uranium/Application/Settings/WindowSettings.h"
#include "Uranium/Application/Devices/Window.h"

#include "Scenes/OverworldScene.h"
#include "Uranium/RenderEngine/SceneControl/Scene.h"
#include "Uranium/RenderEngine/SceneControl/SceneManager.h"

using namespace Uranium;

class MainApp : public ApplicationRunner {
public:
	
	OverworldScene* overworld;

	void init() {
		overworld = new OverworldScene();

		Application::get().getWindow().getSettings().setTitle("My Game");
		Application::get().getSceneManager().addScene(overworld);
	}

	void run() {

	}

	void dispose() {
		delete overworld;
	}
};

int main() {
	Application::start(new MainApp());
}