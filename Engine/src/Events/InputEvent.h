#pragma once

namespace Uranium {

	class Mouse;
	class Keyboard;

	class InputEvent {
	private:

	protected:
		InputEvent();

	public:
		virtual ~InputEvent();

		Mouse& getMouse();
		Keyboard& getKeyboard();
		
	};
}