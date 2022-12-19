#pragma once

namespace SceneUtils {

	class SceneManager;

	class Scene {
	public:
		Scene();
		virtual ~Scene();

		virtual void load()		= 0;
		virtual void render()	= 0;
		virtual void update()	= 0;
		virtual void unload()	= 0;
		virtual void dispose()	= 0;

		SceneManager& getSceneManager();

	private:
		friend class SceneManager;

		SceneManager* sceneManager;

		void setSceneManager(SceneManager* _sceneManager);

	};
}