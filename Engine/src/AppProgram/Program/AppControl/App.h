#pragma once

namespace Display {
	class Window;
}

namespace SceneUtils {
	class SceneManager;
}

namespace Equipment {
	class Equipments;
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
		friend class Equipment::Equipments;

		Display::Window* window;
		SceneUtils::SceneManager* sceneManager;
		Equipment::Equipments* equipments;

		void init();
		void run();
		void end();

		void clearError();
		void checkError();

	public:
		explicit App();
		~App();

		void launch();
		void exit();

		Display::Window& getWindow();
		Equipment::Equipments& getEquipments();
		SceneUtils::SceneManager& getSceneManager();
	};
}