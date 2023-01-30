//#pragma once
//
//#include "UraniumApi.h"
//
//#include "Scene/Camera.h"
//
//#include "Renderer/Texture.h"
//#include "Renderer/ShaderProgram.h"
//#include "Renderer/ModelRenderer.h"
//
//using namespace Uranium;
//
//class ChunkRenderer : public ModelRenderer {
//private:
//	Texture* texture;
//
//	
//public:
//	ChunkRenderer(ShaderProgram* _shader)
//		: ModelRenderer(_shader)
//	{
//		texture = new Texture("src/Texture.png");
//		
//	}
//
//	~ChunkRenderer() {
//		delete texture;
//	}
//
//	void technicalRender(const Model& _model, const Material& _material) override {
//		_model.bind();
//		_model.enableAttribs();
//
//		texture->bind(0);
//
//		glEnable(GL_DEPTH_TEST);
//
//		draw(_model.getIndexCount(), GL_UNSIGNED_INT);
//
//		glDisable(GL_DEPTH_TEST);
//
//		_model.unbind();
//		_model.disableAttribs();
//	}
//};