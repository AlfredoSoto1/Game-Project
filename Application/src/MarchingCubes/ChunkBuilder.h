#pragma once

#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"
using namespace MathsUtils;

#include "Utils/Buffers/VertexBuffer.h"
using namespace BufferUtils;

#include "Utils/Geometry/Model.h"
using namespace GeometryUtils;

class ChunkBuilder {
public:

	struct Vertex {
		vec3 position = vec3(0.0);
		vec4 color = vec4(0.0);
	};

	VertexBuffer<Vertex, unsigned int>* mesh;	// reusable mesh

	Model* singleModel;

	ChunkBuilder() {
		mesh = new VertexBuffer<Vertex, unsigned int>(2);

	}

	~ChunkBuilder() {

	}
	
	void create() {

		// create mesh
		mesh->pushBack({ vec3(-0.5f, -0.5f, -1.0f), vec4(1.0, 0.0, 0.0, 1.0) });
		mesh->pushBack({ vec3( 0.5f, -0.5f, -1.0f), vec4(0.0, 1.0, 0.0, 1.0) });
		mesh->pushBack({ vec3( 0.5f,  0.5f, -1.0f), vec4(0.0, 0.0, 1.0, 1.0) });

		// fit buffer to real size
		mesh->fit();

		//singleModel = new Model(mesh, material, ...);

		singleModel = new Model();

		IndexBuffer ibo(&singleModel->getVao(), GL_STATIC_DRAW, mesh->indexCount(), mesh->getIndices());

		VirtualBuffer vbo(&singleModel->getVao(), GL_STATIC_DRAW, mesh->vertexSize(), mesh->vertexCount(), mesh->getVertices());
		vbo.push_Layout(0, 3, GL_FLOAT, 0);
		vbo.push_Layout(1, 4, GL_FLOAT, offsetof(Vertex, color));

		//vao->bindIbo(0);

		// clear and reset current mesh
		mesh->clear();
	}

	void dispose() {
		delete mesh;

		delete singleModel;
	}
};