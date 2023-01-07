#pragma once

#define UR_CONTENT_API
#include "Engine.h"

namespace Uranium {
	
	class Window;
	class Device;
	class Scene;
	class SceneManager;
	class ApplicationRunner;

	class Application {
	private:
		friend class Window;
		friend class Device;
		friend class SceneManager;

		static Application* application;

		ApplicationRunner* applicationTemplate;
		
		Window* window;
		Device* device;
		SceneManager* sceneManager;

		bool isRunning;

		Application();
		virtual ~Application();

		void run();

	public:
		static Application& get();
		static void start(ApplicationRunner* _applicationTemplate);
		
		Application(const Application&) = delete;
		Application(const Application&&) = delete;

		void setCurrentScene(Scene* _scene);

		Window& getWindow();
		Device& getDevice();
		SceneManager& getSceneManager();
	};
}