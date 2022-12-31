#pragma once

namespace BufferUtils {
	class VertexArray;
}

namespace Render {

	class Renderer {
	private:

	public:
		Renderer();
		~Renderer();

		void render(const BufferUtils::VertexArray& _vao);
	};
}
