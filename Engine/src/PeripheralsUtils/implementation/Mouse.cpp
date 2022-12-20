
/*
	Application
*/
#include "Application/App.h"
using namespace Application;

/*
	Peripherals
*/
#include "PeripheralsUtils/Mouse.h"
using namespace PeripheralsUtils;

/*
	Settings
*/
#include "Settings/MouseSettings.h"
using namespace Settings;

/*
	Callbacks
*/
#include "Callbacks/MouseCallback.h"
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
