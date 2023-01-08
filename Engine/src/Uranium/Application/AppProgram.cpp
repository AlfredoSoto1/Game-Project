#include "AppProgram.h"

#include <string>
#include "UraniumApi.h"
#include "Uranium/RenderEngine/SceneControl/Scene.h"
using namespace Uranium;

AppProgram::AppProgram()
{
	hasChangedScene = false;
	currentScene = nullptr;
}

AppProgram::~AppProgram() {
	activeScenes.clear();
}

void AppProgram::push_firstNewScene(Scene* _scenePtr) {
	throw_error(_scenePtr == nullptr, "Scene must NOT be nullptr");
	activeScenes.push_back(_scenePtr);
	currentScene = _scenePtr;
	hasChangedScene = true;
}

void AppProgram::update() {
	throw_error(activeScenes.empty(), "No scenes available");

	// load scene once after scene has changed
	if (hasChangedScene) {
		currentScene->load();
		hasChangedScene = false;
	}

	// update scene content
	currentScene->update();

	// change scene to next
	if (!currentScene->hasToChangeScene())
		return;

	// unload scene content
	currentScene->unload();

	// linear search for the next scene
	bool foundScene_toChange = false;
	for (Scene* scene : activeScenes) {
		if (currentScene->getNextScene().compare(scene->getName()) != 0)
			continue;
		currentScene = scene;
		foundScene_toChange = true;
		break;
	}

	// if no next scene is found, current scene will be set to the first scene
	if (!foundScene_toChange) {
		currentScene = activeScenes[0];
	}

	// reset scene
	currentScene->reset();

	hasChangedScene = true;
}

void AppProgram::draw() {
	currentScene->draw();
}

void AppProgram::afterDraw() {
	currentScene->postDraw();
}
