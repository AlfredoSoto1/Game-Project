#pragma once

namespace RenderUtils {
	class Renderable {
	public:
		virtual void init()		= 0;
		virtual void render()	= 0;
		virtual void update()	= 0;
		virtual void dispose()	= 0;

	protected:
		virtual void in_init(bool _isOnCallback)	= 0;
		virtual void in_render(bool _isOnCallback)	= 0;
		virtual void in_update(bool _isOnCallback)	= 0;
		virtual void in_dispose(bool _isOnCallback)	= 0;
	};
}