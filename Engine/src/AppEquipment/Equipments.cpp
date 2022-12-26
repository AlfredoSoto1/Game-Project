
/*
	Peripherals
*/
#include "Mouse.h"
#include "Equipments.h"

using namespace Equipment;

#include "AppProgram/Program/AppControl/App.h"
#include "AppProgram/Program/AppControl/AppComponent.h"

using namespace Application;

Equipments::Equipments(App* _appRef)
	: AppComponent(_appRef)
{
	mouse = nullptr;
}

Equipments::~Equipments() {

}

Mouse& Equipments::getMouse() {
	return *mouse;
}

void Equipments::init() {
	mouse = new Mouse(getAppRef());
}

void Equipments::dispose() {
	delete mouse;
}
