#pragma once

#include <vector>

namespace Listener {
	class WindowListener;
}

namespace Graphics {
	class Scene {
	public:
		Scene();
		virtual ~Scene();

		virtual void init()    = 0;
		virtual void render()  = 0;
		virtual void update()  = 0;
		virtual void dispose() = 0;
	private:
		std::vector<Listener::WindowListener*> listeners;
	};
}