
/*
	Application
*/
#include "Application/App.h"
#include "Application/AppComponent.h"

using namespace Application;

/*
	Display
*/
#include "Display/Window.h"
using namespace Display;

/*
	SceneUtils
*/
#include "SceneUtils/SceneManager.h"
using namespace SceneUtils;

/*
	Peripherals
*/
#include "PeripheralsUtils/Peripherals.h"
using namespace PeripheralsUtils;

App::App() {
	this->window = new Window("Default", 1280, 720);
	this->peripherals = new Peripherals();
	this->sceneManager = new SceneManager();
	
	window->setAppRef(this);
	peripherals->setAppRef(this);
	sceneManager->setAppRef(this);
}

App::~App() {
	delete window;
	delete peripherals;
	delete sceneManager;
}

void App::init() {
	// initialze Window
	window->init();

	// initialze peripherals
	peripherals->init();

	// initialize Scenes
	sceneManager->init();
}

void App::run() {
	// run application loop
	window->runLoop();
}

void App::end() {
	//dispose everything on the app
	sceneManager->dispose();
	peripherals->dispose();
	window->dispose();
}

void App::launch() {
	//initiates application
	init();
	//runs application
	run();
	//ends application
	end();
}

void App::exit() {
	//exits application
	// TODO + in the future
}

Window& App::getWindow() {
	return *window;
}

SceneManager& App::getSceneManager() {
	return *sceneManager;
}

Peripherals& App::getPeripherals() {
	return *peripherals;
}


