#pragma once

#include <cstdint>

namespace Graphics {
	class ShaderProgram;
}

namespace GeometryUtils {
	class Model;
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

		void render(const GeometryUtils::Model& _model, const Graphics::ShaderProgram& _shader);
	};
}
