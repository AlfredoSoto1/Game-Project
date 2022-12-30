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

	void init() {

	}

	void load() {

	}

	void dispose() {
		destroy();
	}

};