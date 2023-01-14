#pragma once

namespace Uranium {

	class Mouse;
	class Keyboard;

	class InputEvent {
	private:

	public:
		Mouse& getMouse();
		Keyboard& getKeyboard();
		
	};
}