#pragma once

namespace Listener {
	class MouseListener {
	public:
		virtual void mouseDrop(int _pathCount, const char** _paths) = 0;
		virtual void mouseEnterWindow(bool hasEntered)				= 0;
		virtual void mouseMoved(double xpos, double ypos) = 0;
		virtual void mousePressedButton(int button, int action, int mods, double xpos, double ypos) = 0;
		virtual void mouseClickedButton(int button, int action, int mods, double xpos, double ypos) = 0;
		virtual void mouseReleasedButton(double xpos, double ypos) = 0;
		virtual void mouseScrollButton(double xOffset, double yOffset) = 0;
	};
}