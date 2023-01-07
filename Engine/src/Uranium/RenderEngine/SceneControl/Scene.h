#pragma once

namespace Uranium {

	class SceneManager;

	class Scene {
	private:
		friend class SceneManager;

	protected:
		virtual void init()		= 0;
		virtual void load()		= 0; //unused currently
		virtual void render()	= 0;
		virtual void update()	= 0;
		virtual void unload()	= 0; //unused currently
		virtual void dispose()	= 0;

	public:
		Scene();
		virtual ~Scene();

	};
}