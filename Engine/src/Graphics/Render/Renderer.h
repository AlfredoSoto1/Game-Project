#pragma once

#include <cstdint>

namespace BufferUtils {
	class VertexArray;
}

namespace Render {

	class Renderer {
	private:
		bool isWireframe;

	public:
		Renderer();
		~Renderer();

		void showWireframe();
		void hideWireframe();

		void render(const BufferUtils::VertexArray& _vao);
	};
}
