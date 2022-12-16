#pragma once

#include <string>

struct GLFWwindow;

namespace Listener {
	class WindowListener;
}

namespace Settings {
	class MouseSettings;
	class WindowSettings;
}

namespace StageUtils {
	class Stage;
}

namespace Display {
	class Window {
	public:
		Window(const Settings::WindowSettings& _settings);
		Window(const std::string& _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void start();
		void close();
		void focus();

		void attach(StageUtils::Stage* _stage);

		void pollEvents(int _isOnCallback);

		StageUtils::Stage& getStage();
		Settings::WindowSettings& getSettings();
		Settings::MouseSettings& getMouseSettings();
		Listener::WindowListener& getWindowListener();

	private:
		GLFWwindow* winPtr;

		Settings::WindowSettings* settings;
		Settings::MouseSettings* mouseSettings;
		Listener::WindowListener* windowListener;

		StageUtils::Stage* stage;

		bool hadStageCreated;

		bool initGLEW();
		bool initGLFW();

		void runLoop();
		void finish();
	};
}