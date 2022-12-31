#pragma once

#include "ChunkShader.h"

#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"
#include "Utils/Buffers/IndexBuffer.h"
#include "Utils/Buffers/VertexArray.h"
#include "Utils/Buffers/VertexBuffer.h"
#include "Utils/Buffers/VirtualBuffer.h"
#include "Utils/Geometry/Mesh.h"
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

		IndexBuffer ibo(vao, GL_STATIC_DRAW, buffer->indexCount(), buffer->getIndices());

		VirtualBuffer vbo(vao, GL_STATIC_DRAW, buffer->vertexSize(), buffer->vertexCount(), buffer->getVertices());
		vbo.push_Layout(0, 3, GL_FLOAT, 0);
		vbo.push_Layout(1, 4, GL_FLOAT, offsetof(Vertex, color));

		vao->bindIbo(0);
	}

	void update() {
	}

	void render() {
		// binds Shader before using it
		shader->bind();

		// binds Mesh to render
		//mesh->bind();

		vao->bind();
		vao->enableAttribs();

		glEnable(GL_DEPTH_TEST);

		glDrawElements(GL_TRIANGLES, buffer->indexCount(), GL_UNSIGNED_INT, nullptr);

		glDisable(GL_DEPTH_TEST);

		vao->disableAttribs();
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