#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
using namespace std;

#include "Framework/AppManager/Application.h"

#include "Framework/SceneManager/SceneManager.h"

#include "Graphics/Display/Window.h"
#include "Settings/WindowSettings.h"

#include "Scenes/OverworldScene.h"

class MainApp : public FrameworkEngine::Application {
public:
	
	OverworldScene* overworld;

	MainApp() 
		: Application()
	{

	}

protected:

	void init() {
		overworld = new OverworldScene();

		getWindow().getSettings().setTitle("My Game");
		getSceneManager().addScene(overworld);
	}

	void close() {
		delete overworld;
	}

};

int main() {
	MainApp myApp = MainApp();
	myApp.run();
}