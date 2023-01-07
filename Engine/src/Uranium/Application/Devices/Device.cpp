#include "Mouse.h"
#include "Device.h"

using namespace Uranium;

Device::Device()
{
	mouse = nullptr;
}

Device::~Device() {

}

Mouse& Device::getMouse() {
	return *mouse;
}

void Device::init() {
	mouse = new Mouse();
}

void Device::dispose() {
	delete mouse;
}

void Device::update() {
	mouse->update();
}
