#pragma once

#include <cstdint>

namespace Graphics {
	class ShaderProgram;
}

namespace BufferUtils {
	class VertexArray;
}

namespace Render {

	class Renderer {
	private:
		bool isWireframe;

	public:
		Renderer();
		virtual ~Renderer();

		void showWireframe();
		void hideWireframe();

		void dispose();

		void render(const BufferUtils::VertexArray& _vao, const Graphics::ShaderProgram& _shader);
	};
}
