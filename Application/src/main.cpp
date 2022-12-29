#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
using namespace std;

#include "AppProgram/Program/AppControl/App.h"
#include "AppProgram/Program/SceneControl/SceneManager.h"

#include "AppDisplay/Display/Window.h"
#include "AppSettings/WindowSettings.h"

#include "Scenes/OverworldScene.h"

int main() {

	OverworldScene* overworld = new OverworldScene();
	
	//Create Application
	Application::App app = Application::App();

	app.getWindow().getSettings().setTitle("First Display");

	app.getSceneManager().addScene(overworld);

	app.launch();

	delete overworld;

}