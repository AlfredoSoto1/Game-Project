#pragma once

namespace StageUtils {
	class Scene {
	public:
		Scene();
		virtual ~Scene();

		//virtual void init()		= 0;
		//virtual void render()	= 0;
		//virtual void update()	= 0;
		//virtual void dispose()	= 0;

		void init();
		void render();
		void update();
		void dispose();
	};
}