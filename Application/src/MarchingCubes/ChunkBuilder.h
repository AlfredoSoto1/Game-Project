#pragma once

#include "Utils/Maths/vec2.h"
#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"

#include "Utils/Buffers/IndexBuffer.h"
#include "Utils/Buffers/VertexBuffer.h"

#include "Utils/Geometry/Mesh.h"
#include "Utils/Geometry/Model.h"
using namespace Uranium;

class ChunkBuilder {
public:
	struct Vertex {
		vec3 position = vec3(0.0);
		vec4 color = vec4(0.0);
		vec2 textCoord = vec2(0.0);
	};

	Model* model;

	Mesh<Vertex, unsigned int>* mesh;

	ChunkBuilder() {
		mesh = new Mesh<Vertex, unsigned int>(2);
	}

	~ChunkBuilder() {
		delete model;
		delete mesh;
	}
	
	void create() {
		
		buildMesh();

		model = new Model();

		IndexBuffer ibo(model, GL_STATIC_DRAW, mesh->indexCount(), mesh->getIndices());

		VertexBuffer vbo(model, GL_STATIC_DRAW, mesh->vertexSize(), mesh->vertexCount(), mesh->getVertices());
		vbo.push_Layout(0, 3, GL_FLOAT, 0);
		vbo.push_Layout(1, 4, GL_FLOAT, offsetof(Vertex, color));
		vbo.push_Layout(2, 2, GL_FLOAT, offsetof(Vertex, textCoord));

		model->bindIbo(0);
	}

	void buildMesh() {
		mesh->pushBack({ vec3(-0.5f, -0.5f, -1.0f), vec4(1.0, 0.0, 0.0, 1.0) , vec2(0.0, 0.0) });
		mesh->pushBack({ vec3( 0.5f, -0.5f, -1.0f), vec4(0.0, 1.0, 0.0, 1.0) , vec2(1.0, 0.0) });
		mesh->pushBack({ vec3( 0.5f,  0.5f, -1.0f), vec4(0.0, 0.0, 1.0, 1.0) , vec2(1.0, 1.0) });

		mesh->pushBack({ vec3( 0.5f,  0.5f, -1.0f), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		mesh->pushBack({ vec3(-0.5f,  0.5f, -1.0f), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		mesh->pushBack({ vec3(-0.5f, -0.5f, -1.0f), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		mesh->fit();
	}
};