#pragma once

namespace Uranium {

	class Model;
	class Camera;
	class Material;
	class ShaderProgram;

	class ModelRenderer {
	private:
		bool isWireframe;

		ShaderProgram* shader;

	protected:
		void showWireframe();
		void hideWireframe();

		virtual void technicalRender(const Model& _model, const Material& _material);

		void draw(unsigned int _indexCount, unsigned int _indexType);

	public:
		ModelRenderer(ShaderProgram* _shader);
		virtual ~ModelRenderer();

		void render(Camera* _camera, const Model& _model, const Material& _material);
	};
}