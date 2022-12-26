#include "AppComponent.h"

using namespace Application;

AppComponent::AppComponent(App* _appRef) {
	appRef = _appRef;
}

App* AppComponent::getAppRef() {
	return appRef;
}