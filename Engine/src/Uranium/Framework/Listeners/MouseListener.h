#pragma once

namespace Uranium {
	class MouseListener {
	public:
		virtual void mouseDrop(int _pathCount, const char** _paths) = 0;

		virtual void mouseEnterWindow(bool hasEntered) = 0;

		virtual void mouseMoved(double xpos, double ypos) = 0;
		
		virtual void mouseScrollButton(double xOffset, double yOffset) = 0;
		virtual void mouseClickedButton(int button, int mods, double xpos, double ypos) = 0;
		virtual void mousePressedButton(int button, int mods, double xpos, double ypos) = 0;
		virtual void mouseReleasedButton(int button, int mods, double xpos, double ypos) = 0;
		
	};
}