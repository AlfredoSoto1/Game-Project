#pragma once

namespace Display {
	class Window;
}

namespace SceneUtils {
	class SceneManager;
}

namespace PeripheralsUtils {
	class Peripherals;
}

namespace Application {

	/*
		Application Component
	*/
	class AppComponent;

	/*
		App declaration
	*/
	class App {
	private:
		friend class AppComponent;
		friend class Display::Window;
		friend class SceneUtils::SceneManager;
		friend class PeripheralsUtils::Peripherals;

		Display::Window* window;
		SceneUtils::SceneManager* sceneManager;
		PeripheralsUtils::Peripherals* peripherals;

		void init();
		void run();
		void end();

	public:
		explicit App();
		~App();

		void launch();
		void exit();

		Display::Window& getWindow();
		SceneUtils::SceneManager& getSceneManager();
		PeripheralsUtils::Peripherals& getPeripherals();
	};
}