#pragma once

#include <string>

struct GLFWwindow;

namespace Settings {
	class MouseSettings;
	class WindowSettings;
}

namespace Callback {
	class MouseCallback;
	class WindowCallback;
}

namespace StageUtils {
	class Stage;
}

namespace Display {
	class Window {
	public:
		Window(const Settings::WindowSettings&& _settings);
		Window(const std::string& _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void start();
		void close();
		void focus();

		void attach(StageUtils::Stage* _stage);

		void pollEvents(int _isOnCallback);

		StageUtils::Stage& getStage();

		Settings::MouseSettings& getMouseSettings();
		Settings::WindowSettings& getWindowSettings();

		Callback::MouseCallback& getMouseCallback();
		Callback::WindowCallback& getWindowCallback();

	private:
		GLFWwindow* winPtr;

		Settings::MouseSettings* mouseSettings;
		Settings::WindowSettings* windowSettings;

		Callback::MouseCallback* mouseCallback;
		Callback::WindowCallback* windowCallback;

		StageUtils::Stage* stage;

		bool hadStageCreated;

		bool initGLEW();
		bool initGLFW();

		void runLoop();
		void finish();
	};
}