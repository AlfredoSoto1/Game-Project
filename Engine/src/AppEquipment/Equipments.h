#pragma once

#include "AppProgram/Program/AppControl/AppComponent.h"

namespace Application {
	class App;
	class AppComponent;
}

namespace SceneUtils {
	class SceneManager;
}

namespace Equipment {

	class Mouse;

	class Equipments : public Application::AppComponent {
	private:
		friend class Application::App;
		friend class SceneUtils::SceneManager;
		friend class Application::AppComponent;

		Mouse* mouse;

	public:
		Equipments(Application::App* _appRef);
		~Equipments();

		Mouse& getMouse();

		void init();
		void dispose();
	};
}