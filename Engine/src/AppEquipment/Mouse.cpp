
/*
	Application
*/
#include "AppProgram/Program/AppControl/App.h"
using namespace Application;

/*
	Peripherals
*/
#include "AppEquipment/Mouse.h"
using namespace Equipment;

/*
	Settings
*/
#include "AppSettings/MouseSettings.h"
using namespace Settings;

/*
	Callbacks
*/
#include "AppEquipment/Callbacks/MouseCallback.h"
using namespace Callback;

Mouse::Mouse(App* _appRef) {
	settings = new MouseSettings();
	callback = new MouseCallback(_appRef);
}

Mouse::~Mouse() {
	delete settings;
	delete callback;
}

MouseSettings& Mouse::getSettings() {
	return *settings;
}

MouseCallback& Mouse::getCallback() {
	return *callback;
}
