#pragma once

#include "Graphics/Render/Renderer.h"
#include "Utils/Geometry/Model.h"
#include "Shader/Shader.h"
using namespace Uranium;

#include "Textures/Texture.h"
using namespace Graphics;

class ChunkRenderer : public Renderer {
private:
	Texture* texture;

	Uniform color;
public:
	ChunkRenderer()
		: Renderer(Shader(GL_VERTEX_SHADER, "src/testV.glsl"), Shader(GL_FRAGMENT_SHADER, "src/testF.glsl"))
	{

		texture = new Texture("src/Texture.png");
	}

	~ChunkRenderer() {
		delete texture;
	}

	void preProcessShader() override {
		color = getUniform("u_Color");

		Sampler2D sampler = getSampler2D("grass");
		bindSampler2D(sampler, 0);
	}

	void updateModifierUniforms() {
		setVec4(color, { 1.0, 0.0, 0.0, 1.0 });
	}

	void processShader(const Model& _model, const Material& _material) {
		_model.bind();
		_model.enableAttribs();

		texture->bind(0);

		draw(_model);

		texture->unbind();

		_model.unbind();
		_model.disableAttribs();
	}
};