#pragma once

namespace SceneUtils {
	class Scene {
	public:
		Scene();
		virtual ~Scene();

		virtual void load()		= 0;
		virtual void render()	= 0;
		virtual void update()	= 0;
		virtual void unload()	= 0;
		virtual void dispose()	= 0;
	};
}