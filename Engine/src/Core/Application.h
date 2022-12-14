#pragma once

#define UR_CONTENT_API
#include "Engine.h"

namespace Uranium {
	
	class Mouse;
	class Window;
	class Keyboard;
	class AppProgram;

	class Application {
	private:
		friend class Mouse;
		friend class Window;
		friend class Keyboard;
		friend class AppProgram;

		static Application* application;

		Mouse* mouse;
		Window* window;
		Keyboard* keyboard;
		AppProgram* appProgram;

		bool isRunning;

		Application(AppProgram* _appProgram);
		virtual ~Application();

		void run();

	public:
		static Application& get();
		static void start(AppProgram* _appProgram);
		
		Application(const Application&) = delete;
		Application(const Application&&) = delete;

		Mouse& getMouse();
		Window& getWindow();
		Keyboard& getKeyboard();
	};
}