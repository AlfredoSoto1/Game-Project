#pragma once

#include "ChunkShader.h"

#include "AppProgram/Utils/Maths/vec3.h"
#include "AppProgram/Utils/Maths/vec4.h"
#include "AppProgram/Utils/Buffers/VertexBuffer.h"
#include "AppProgram/Utils/Geometry/Mesh.h"
using namespace MathsUtils;
using namespace BufferUtils;
using namespace GeometryUtils;

class ChunkRenderer {
private:
	ChunkShader* shader;
	struct Vertex {
		vec3 position = vec3(0.0);
		vec4 color = vec4(0.0);
	};

	VertexBuffer<Vertex, unsigned int>* buffer;

	Mesh* mesh;

public:
	ChunkRenderer() {

	}

	void init() {
		shader = new ChunkShader();
		shader->init();

		buffer = new VertexBuffer<Vertex, unsigned int>(2);

		buffer->pushBack({ vec3(-0.5f, -0.5f, -1.0f), vec4(1.0, 0.0, 0.0, 1.0) });
		buffer->pushBack({ vec3(0.5f, -0.5f, -1.0f), vec4(0.0, 1.0, 0.0, 1.0) });
		buffer->pushBack({ vec3(0.5f,  0.5f, -1.0f), vec4(0.0, 0.0, 1.0, 1.0) });

		buffer->fit();

		mesh = new Mesh(2, GL_STATIC_DRAW);

		mesh->setVertexBuffer(*buffer);

		mesh->setAttribPointer(0, 3, GL_FLOAT, sizeof(Vertex), (const void*)0);
		mesh->setAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, color));
	}

	void update() {
	}

	void render() {
		// binds Shader before using it
		shader->bind();

		// binds Mesh to render
		mesh->bind();

		glEnable(GL_DEPTH_TEST);

		glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);

		glDisable(GL_DEPTH_TEST);

		mesh->unbind();

		shader->unbind();
	}

	void dispose() {
		shader->dispose();
		delete shader;

		delete mesh;
		delete buffer;
	}

};