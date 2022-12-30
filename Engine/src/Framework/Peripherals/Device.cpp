
/*
	Peripherals
*/
#include "Mouse.h"
#include "Device.h"
using namespace Peripherals;

#include "Framework/AppManager/Application.h"
#include "Framework/AppManager/AppComponent.h"
using namespace FrameworkEngine;

Device::Device(Application* _reference)
	: AppComponent(_reference)
{
	mouse = nullptr;
}

Device::~Device() {

}

Mouse& Device::getMouse() {
	return *mouse;
}

void Device::init() {
	mouse = new Mouse(getAppRef());
}

void Device::dispose() {
	delete mouse;
}

void Device::update() {
	mouse->update();
}
