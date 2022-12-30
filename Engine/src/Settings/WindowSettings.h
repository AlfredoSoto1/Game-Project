#pragma once

#define MIN_WIDTH 320
#define MIN_HEIGHT 180

#include <string>

struct GLFWmonitor;
struct GLFWwindow;

namespace Callback {
	class WindowCallback;
}


namespace Display {
	class Window;
}

namespace Settings {
	class WindowSettings {
	private:
		friend class Display::Window;
		friend class Callback::WindowCallback;

		std::string title;

		GLFWwindow* context;
		GLFWmonitor* monitor;

		unsigned int width;
		unsigned int height;
		unsigned int transparency;
		unsigned int mayorGLVersion;
		unsigned int minorGLVersion;

		int xPosition;
		int yPosition;

		bool is_Visible;
		bool is_Resizable;
		bool is_Decorated;
		bool is_FullScreen;
		bool is_AlwaysOnTop;

		bool has_Resized;
		bool is_Maximized;
		bool is_Minimized;

		void loadHints();
		void centerWindow();

		void setContext(GLFWwindow* _context);
		void changeSize(unsigned int _width, unsigned int _height);
		void changePosition(unsigned int _xPosition, unsigned int _yPosition);

	public:
		WindowSettings();
		~WindowSettings();

		void reset();

		void restore();
		void maximize();
		void minimize();

		void setTitle(const std::string& _title);

		void setTransparency(unsigned int _transparency);
		void setCurrentMonitor(GLFWmonitor* _currentMonitor);
		void setSize(unsigned int _width, unsigned int _height);
		void setPosition(unsigned int _xPosition, unsigned int _yPosition);

		void setVisible(bool _isVisible);
		void setResizable(bool _isResizable);
		void setDecorated(bool _isDecorated);
		void setFullScreen(bool _isFullScreen);
		void setAlwaysOnTop(bool _isAlwaysOnTop);

		void setGLVersion(unsigned int mayor, unsigned int minor);
		
		std::string getTitle();

		unsigned int getWidth();
		unsigned int getHeight();
		unsigned int getTransparency();
		GLFWmonitor* getCurrentMonitor();
		
		int getXPosition();
		int getYPosition();
		GLFWmonitor** getAvailableMonitors();

		bool isVisible();
		bool isResizable();
		bool isDecorated();
		bool isFullScreen();
		bool isAlwaysOnTop();

		bool& hasResized();
	
	};
}
