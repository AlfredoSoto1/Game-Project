#pragma once

namespace FrameworkEngine {
	class App;
}

namespace SceneControl {

	class SceneManager;

	class Scene {
	private:
		friend class SceneManager;

		FrameworkEngine::Application* application;

		void setApplication(FrameworkEngine::Application* _reference);

	protected:
		virtual void init()		= 0;
		virtual void load()		= 0; //unused currently
		virtual void render()	= 0;
		virtual void update()	= 0;
		virtual void unload()	= 0; //unused currently
		virtual void dispose()	= 0;

		FrameworkEngine::Application& getApplication();

	public:
		Scene();
		virtual ~Scene();

	};
}