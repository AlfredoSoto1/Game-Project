#pragma once

namespace Graphics {
	class RenderProgram {
	public:
		RenderProgram();
		virtual ~RenderProgram();

		virtual void render()  = 0;
		virtual void update()  = 0;
		virtual void dispose() = 0;
	private:

	};
}