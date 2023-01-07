#pragma once

namespace Uranium {

	class Mouse;
	class Application;
	class SceneManager;

	class Device {
	private:
		friend class SceneManager;
		friend class Application;

		Mouse* mouse;

		void init();
		void update();
		void dispose();

	public:
		Device();
		~Device();

		Mouse& getMouse();
	};
}