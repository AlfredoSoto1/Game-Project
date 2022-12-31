#pragma once

#include "ChunkShader.h"

#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"
#include "Utils/Buffers/VertexBuffer.h"
#include "Utils/Geometry/Mesh.h"
#include "Utils/Geometry/VertexArray.h"
using namespace MathsUtils;
using namespace BufferUtils;
using namespace GeometryUtils;

void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

void checkError() {
	while (GLenum error = glGetError())
		std::cout << "[GL ERROR]: " << error << std::endl;
}

class ChunkRenderer {
private:
	ChunkShader* shader;
	struct Vertex {
		vec3 position = vec3(0.0);
		vec4 color = vec4(0.0);
	};

	VertexBuffer<Vertex, unsigned int>* buffer;

	//Mesh* mesh;

	VertexArray* vao;

public:
	ChunkRenderer() {

	}

	void init() {

		// render(vao, shader);


		/*
		* 
		* 
		* 
		* 
		*/

		shader = new ChunkShader();
		shader->init();

		buffer = new VertexBuffer<Vertex, unsigned int>(2);

		buffer->pushBack({ vec3(-0.5f, -0.5f, -1.0f), vec4(1.0, 0.0, 0.0, 1.0) });
		buffer->pushBack({ vec3( 0.5f, -0.5f, -1.0f), vec4(0.0, 1.0, 0.0, 1.0) });
		buffer->pushBack({ vec3( 0.5f,  0.5f, -1.0f), vec4(0.0, 0.0, 1.0, 1.0) });

		buffer->fit();

		//mesh = new Mesh(2, GL_STATIC_DRAW);

		//mesh->setVertexBuffer(*buffer);

		//mesh->setAttribPointer(0, 3, GL_FLOAT, sizeof(Vertex), (const void*)0);
		//mesh->setAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, color));

		vao = new VertexArray();

		vao->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, buffer->indexCountSize(), buffer->getIndices());

		vao->bindBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, buffer->vertexCountSize(), buffer->getVertices());
		vao->addLayout(0, 3, GL_FLOAT, sizeof(Vertex), 0);
		vao->addLayout(1, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));

	}

	void update() {
	}

	void render() {
		// binds Shader before using it
		shader->bind();

		// binds Mesh to render
		//mesh->bind();

		vao->bind();

		glEnable(GL_DEPTH_TEST);

		glDrawElements(GL_TRIANGLES, buffer->indexCount(), GL_UNSIGNED_INT, nullptr);

		glDisable(GL_DEPTH_TEST);

		vao->unbind();
		//mesh->unbind();

		shader->unbind();
	}

	void dispose() {
		shader->dispose();
		delete shader;

		delete vao;

		//delete mesh;
		delete buffer;
	}

};