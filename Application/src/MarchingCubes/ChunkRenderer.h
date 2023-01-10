#pragma once

#define UR_OPENGL
#include "Engine.h"
#include "UraniumApi.h"

#include "Core/Application.h"

#include "Gui/Window.h"
#include "Gui/WindowSettings.h"

#include "Scenes/OverworldScene.h"
#include "Scene/Camera.h"
#include "Scene/Scene.h"
#include "Renderer/Shader.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Renderer.h"

#include "Renderer/Texture.h"
#include "Utils/Maths/Operation.h"

using namespace Uranium;

class ChunkRenderer : public Renderer {
private:
	Texture* texture;

	Sampler2D sampler;

	Uniform color;
	Uniform viewMatrix;
	Uniform projectionMatrix;
	Uniform transformationMatrix;

	mat4 transformMat;
public:
	ChunkRenderer()
		: Renderer(Shader(GL_VERTEX_SHADER, "src/testV.glsl"), Shader(GL_FRAGMENT_SHADER, "src/testF.glsl"))
	{

		texture = new Texture("src/Texture.png");
		
		shader->bind();
		preProcessShader();
		shader->unbind();

		transform(&transformMat, vec3(0.0, 0.0, 0.0), vec3(0.0), vec3(1.0));

	}

	~ChunkRenderer() {
		delete texture;
	}

	void preProcessShader() {
		color = getUniform("u_Color");
		viewMatrix = getUniform("viewMatrix");
		projectionMatrix = getUniform("projectionMatrix");
		transformationMatrix = getUniform("transformationMatrix");

		sampler = getSampler2D("grass");
		bindSampler2D(sampler, 0);
	}

	void updateModifierUniforms(Camera* _camera) {
		setVec4(color, { 1.0, 0.0, 0.0, 1.0 });
		setMat4(viewMatrix, _camera->getViewMatrix());
		setMat4(projectionMatrix, _camera->getProjectionMatrix());
		setMat4(transformationMatrix, transformMat);
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