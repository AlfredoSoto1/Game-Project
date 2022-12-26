#pragma once

namespace Application {
	
	class App;

	class AppComponent {
	private:
		friend class App;

		App* appRef;

	protected:
		AppComponent(App* _appRef);

		App* getAppRef();

	};
}