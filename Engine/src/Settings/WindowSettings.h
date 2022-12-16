#pragma once

#define MIN_WIDTH 320
#define MIN_HEIGHT 180

#include <string>

struct GLFWmonitor;
struct GLFWwindow;

namespace Settings {
	class WindowSettings {
	public:
		WindowSettings();
		WindowSettings(const WindowSettings& settings);
		~WindowSettings();

		void reset();
		void loadHints();
		void apply();
		void uninit();
		void setContext(GLFWwindow* _context);

		void restore();
		void maximize();
		void minimize();
		void requestAttention();
		void centerWindow();

		void setTitle(const std::string& _title);

		void setTargetFPS(unsigned int _FPS);
		void setTransparency(unsigned int _transparency);
		void setCurrentMonitor(GLFWmonitor* _currentMonitor);
		void setSize(unsigned int _width, unsigned int _height);
		void setPosition(unsigned int _xPosition, unsigned int _yPosition);

		void setVisible(bool _isVisible);
		void setResizable(bool _isResizable);
		void setDecorated(bool _isDecorated);
		void setFullScreen(bool _isFullScreen);
		void setAlwaysOnTop(bool _isAlwaysOnTop);
		void setVSyncEnabled(bool _isVSyncEnabled);
		void setDynamicUpdate(bool _isDynamicUpdate);
		
		std::string getTitle();

		unsigned int getWidth();
		unsigned int getHeight();
		unsigned int getTargetFPS();
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
		bool isVSyncEnabled();
		bool isDynamicUpdate();

		bool& hasResized();

	private:
		std::string title;

		GLFWwindow* context;
		GLFWmonitor* monitor;

		unsigned int width;
		unsigned int height;
		unsigned int targetFrames;
		unsigned int transparency;
		
		int xPosition;
		int yPosition;

		bool is_Visible;
		bool is_Resizable;
		bool is_Decorated;
		bool is_FullScreen;
		bool is_AlwaysOnTop;
		bool is_VSyncEnabled;
		bool is_DynamicUpdate;
		
		bool has_Resized;
		bool hasInitialized;
		bool is_Maximized;
		bool is_Minimized;
	};
}
