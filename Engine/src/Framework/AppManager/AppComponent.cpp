#include "AppComponent.h"

using namespace FrameworkEngine;

AppComponent::AppComponent(Application* _reference) {
	reference = _reference;
}

Application* AppComponent::getAppRef() {
	return reference;
}