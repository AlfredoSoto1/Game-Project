#pragma once

namespace Application {
	class App;
}

namespace SceneUtils {

	class SceneManager;

	class Scene {
	private:
		friend class SceneManager;

		Application::App* app;

		void setApplication(Application::App* _app);

	protected:
		virtual void init()		= 0;
		virtual void load()		= 0; //unused currently
		virtual void render()	= 0;
		virtual void update()	= 0;
		virtual void unload()	= 0; //unused currently
		virtual void dispose()	= 0;

		Application::App& getApp();

	public:
		Scene();
		virtual ~Scene();

	};
}