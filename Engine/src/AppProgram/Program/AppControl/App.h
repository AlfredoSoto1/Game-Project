#pragma once

namespace Display {
	class Window;
}

namespace SceneControl {
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
		friend class SceneControl::SceneManager;
		friend class Equipment::Equipments;

		Display::Window* window;
		SceneControl::SceneManager* sceneManager;
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
		SceneControl::SceneManager& getSceneManager();
	};
}