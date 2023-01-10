#pragma once

namespace Uranium {

	class Window;

	class Keyboard {
	private:
		friend class Application;
		
		bool* keys;

		bool toggled = false;
		bool released = false;

		Keyboard(Window* _window);

		void update();
	
	public:
		virtual ~Keyboard();

		bool isKeyDown(int _key);
		bool isKeyToggled(int _key);
		bool isKeyReleased(int _key);
	};
}