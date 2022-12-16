#pragma once

#include <string>
#include <vector>

struct GLFWwindow;

namespace Listener {
	class WindowListener;
}

namespace Settings {
	class WindowSettings;
}

namespace Graphics {
	class Scene;
}

namespace Display {
	class Window {
	public:
		Window(const Settings::WindowSettings& _settings);
		Window(const std::string& _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void close();
		void focus();

		void loadScene(Graphics::Scene* _scene);

		//temp
		void processFrames();
		void renderDisplay();
		void render(int);

		Settings::WindowSettings& getSettings();
		Listener::WindowListener& getWindowListener();

	private:
		GLFWwindow* winPtr;

		Settings::WindowSettings* settings;
		Listener::WindowListener* windowListener;

		std::vector<Graphics::Scene*> scnenes;

		bool initGLEW();
		bool initGLFW();
		void initWindow();
	};
}