#pragma once

#define OPENGL_ERROR 2
#define APPLICATION_ERROR 3

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
		bool isRunning;

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