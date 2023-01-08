#pragma once

#include "UserCamera.h"
#include "Application/Listeners/MouseEventListener.h"

namespace Uranium {

	class FPCamera : public UserCamera, public MouseEventListener {
	private:
		void calc_camera_rotation();
		void calcMovementDirection();

	protected:
		void update();
		
		void mouseDrop(int _pathCount, const char** _paths);
		void mouseEnterWindow(bool hasEntered);
		void mouseMoved(double xpos, double ypos);
		void mouseScrollButton(double xOffset, double yOffset);
		void mouseClickedButton(int button, int mods, double xpos, double ypos);
		void mousePressedButton(int button, int mods, double xpos, double ypos);
		void mouseReleasedButton(int button, int mods, double xpos, double ypos);
	public:
		FPCamera();
		~FPCamera();

	};
}