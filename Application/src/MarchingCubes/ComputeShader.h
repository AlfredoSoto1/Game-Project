#pragma once

#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"
using namespace MathsUtils;

#include "Shader/ShaderProgram.h"
using namespace Graphics;

#include "Utils/Buffers/ShaderStorageBuffer.h"
using namespace BufferUtils;

class ComputeShader : public ShaderProgram {
private:

public:
	ComputeShader() 
		: ShaderProgram("src/testComp.glsl")
	{

	}

	void load() const {
		vec4 colors[] = {
			vec4(1.0, 0.0, 0.0, 1.0),
			vec4(0.0, 1.0, 0.0, 1.0),
			vec4(0.0, 0.0, 1.0, 1.0),
			vec4(1.0, 1.0, 1.0, 1.0),
		};

		ShaderStorageBuffer* ssbo = new ShaderStorageBuffer(GL_DYNAMIC_DRAW, 0, sizeof(colors), colors);

		bind();

		dispatchCompute(1, 1, 1, GL_SHADER_STORAGE_BARRIER_BIT);

		unbind();

		ssbo->getData(0, sizeof(colors), colors);

		for (int i = 0; i < 4; i++) {
			cout << colors[i].x << ", " << colors[i].y << ", " << colors[i].z << ", " << colors[i].w << endl;
		}

		delete ssbo;
	}

	void update() const {

	}

	void unload() const {

	}

};