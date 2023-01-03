#pragma once

#include "Shader/ShaderProgram.h"

using namespace Graphics;

class ChunkShader : public ShaderProgram {
private:

public:
	ChunkShader()
		: ShaderProgram("src/testV.glsl", "src/testF.glsl")
	{

	}

	void load() const {

		getUniformLocation("u_Color");

		//get uniform location
		getUniformLocation("grass");

		//load slot texture to shader
		bind();
		setInt1("grass", 0);
		unbind();
	}

	void update() const {

		setVec4("u_Color", {1.0, 0.0, 0.0, 1.0});

	}

	void unload() const {
		
	}

};