#include "InputEvent.h"

#include "Core/Application.h"

using namespace Uranium;

InputEvent::InputEvent() {

}

InputEvent::~InputEvent() {

}

Mouse& InputEvent::getMouse() {
	return Application::get().getMouse();
}

Keyboard& InputEvent::getKeyboard() {
	return Application::get().getKeyboard();
}
