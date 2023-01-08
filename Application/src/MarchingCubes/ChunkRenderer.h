#pragma once

#define UR_OPENGL
#include "Engine.h"

#include "Uranium/Application/Application.h"

#include "Uranium/Application/Settings/WindowSettings.h"
#include "Uranium/Application/Devices/Window.h"

#include "Scenes/OverworldScene.h"
#include "Uranium/RenderEngine/SceneControl/Scene.h"
#include "Uranium/RenderEngine/ShaderControl/Shader.h"
#include "Uranium/RenderEngine/Graphics/Renderer.h"

#include "Uranium/Utils/Materials/Texture.h"

using namespace Uranium;

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