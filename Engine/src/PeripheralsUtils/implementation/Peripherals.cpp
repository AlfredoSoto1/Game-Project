
/*
	Peripherals
*/
#include "PeripheralsUtils/Mouse.h"
#include "PeripheralsUtils/Peripherals.h"

using namespace PeripheralsUtils;

#include "Application/App.h"
#include "Application/AppComponent.h"

using namespace Application;

Peripherals::Peripherals()
	: AppComponent()
{
	mouse = nullptr;
}

Peripherals::~Peripherals() {

}

Mouse& Peripherals::getMouse() {
	return *mouse;
}

void Peripherals::init() {
	mouse = new Mouse(getAppRef());
}

void Peripherals::dispose() {
	delete mouse;
}
