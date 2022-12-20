#include "Application/AppComponent.h"

using namespace Application;

AppComponent::AppComponent() {
	appRef = nullptr;
}

void AppComponent::setAppRef(App* _appRef) {
	this->appRef = _appRef;
}

App* AppComponent::getAppRef() {
	return appRef;
}