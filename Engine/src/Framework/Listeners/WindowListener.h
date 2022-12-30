#pragma once

namespace Listener {
	class WindowListener {
	public:

		virtual void windowClosed() = 0;
		virtual void windowRefresh() = 0;
		virtual void windowFrameBufferSize(int width, int height) = 0;
		
		virtual void windowFocused(bool hasFocused) = 0;
		virtual void windowIconified(bool hasIconified) = 0;
		virtual void windowMaximized(bool hasMaximized) = 0;
		
		virtual void windowMoved(int xpos, int ypos) = 0;
		virtual void windowSize(int width, int height) = 0;
	};
}