#pragma once

namespace Display {
	class Window;
}

namespace SceneControl {
	class SceneManager;
}

namespace Peripherals {
	class Device;
}

namespace FrameworkEngine {
	class Application {
	private:
		static unsigned int appCount;

		friend class AppComponent;
		friend class Display::Window;
		friend class Peripherals::Device;
		friend class SceneControl::SceneManager;

		Display::Window* window;
		Peripherals::Device* device;
		SceneControl::SceneManager* sceneManager;

		int errorCode;

		bool isAlive;
		bool isRunning;

		void checkIfExit();
		void createMainComponents();

	protected:
		Application();

		virtual void init() = 0;
		virtual void close() = 0;

		void clearError();
		void checkError();

	public:
		~Application();
		
		void run();
		void exit(int _errorCode);

		Display::Window& getWindow();
		Peripherals::Device& getDevice();
		SceneControl::SceneManager& getSceneManager();
	};
}