#pragma once

#include <string>

namespace Uranium {

	class AppProgram;

	class Scene {
	private:
		friend class AppProgram;

		volatile double lastTime;
		volatile double lastRefresh;
		volatile double timeDifference;
		volatile double lastTimeDifference;

		volatile unsigned short frames;

		short targetFrames;

		std::string sceneName;
		std::string nextScene;

		bool isPaused;
		bool changeScene_requested;

		void postDraw();
		
	protected:
		virtual void load()		= 0; 
		virtual void unload()	= 0;
		virtual void draw()		= 0;
		virtual void update()	= 0;

		virtual void reset();

		bool isWaiting();
		bool hasToChangeScene();
		void changeScene(bool _changeScene_Requested);

		void wait();
		void resume();

		void calibrateFramerate();

	public:
		Scene(const std::string& _name);
		virtual ~Scene();

		inline short unlimitedFramerate();
		volatile double getTimeInstance();

		std::string& getName();
		std::string& getNextScene();

		void setTargetFPS(short _FPS);
		void setNextScene(const std::string& _sceneID);
	};
}
