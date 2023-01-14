#pragma once

#include "Utils/Maths/vec2.h"
#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"

#include "Utils/Buffers/IndexBuffer.h"
#include "Utils/Buffers/VertexBuffer.h"

#include "Utils/Geometry/Mesh.h"
#include "Utils/Geometry/Model.h"

#include "UraniumApi.h"

#include <memory>

using namespace Uranium;

class ChunkBuilder {
public:
	struct Vertex {
		vec3 position;
		vec4 color;
		vec2 textCoord;
	};


	std::shared_ptr<Model> model;

	Mesh<Vertex, unsigned int>* mesh;

	ChunkBuilder() {
		mesh = new Mesh<Vertex, unsigned int>(2);
	}

	~ChunkBuilder() {
		delete mesh;
	}
	
	void create() {
		
		buildMesh();

		model = std::make_shared<Model>();

		IndexBuffer ibo(model.get(), GL_STATIC_DRAW, mesh->indexCount(), mesh->getIndices());
		//IndexBuffer ibo(model, GL_STATIC_DRAW, 12, indices);

		VertexBuffer vbo(model.get(), GL_STATIC_DRAW, mesh->vertexSize(), mesh->vertexCount(), mesh->getVertices());
		vbo.push_Layout(0, 3, GL_FLOAT, 0);
		vbo.push_Layout(1, 4, GL_FLOAT, offsetof(Vertex, color));
		vbo.push_Layout(2, 2, GL_FLOAT, offsetof(Vertex, textCoord));

		model->bindIbo(0);
	}

	void buildMesh() {

		vec3 blockPos = vec3(0.0);
		vec3 scale = vec3(1.0);

		//mesh->pushBack({ vec3(-0.5f, -0.5f, .0f), vec4(1.0, 0.0, 0.0, 1.0) , vec2(0.0, 0.0) });
		//mesh->pushBack({ vec3( 0.5f, -0.5f, .0f), vec4(0.0, 1.0, 0.0, 1.0) , vec2(1.0, 0.0) });
		//mesh->pushBack({ vec3( 0.5f,  0.5f, .0f), vec4(0.0, 0.0, 1.0, 1.0) , vec2(1.0, 1.0) });

		//mesh->pushBack({ vec3( 0.5f,  0.5f, .0f), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		//mesh->pushBack({ vec3(-0.5f,  0.5f, .0f), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		//mesh->pushBack({ vec3(-0.5f, -0.5f, .0f), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		// fase 1

		mesh->pushBack({ vec3(blockPos.x,           blockPos.y,           blockPos.z), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y,           blockPos.z), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y + scale.y, blockPos.z), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		mesh->pushBack({ vec3(blockPos.x,           blockPos.y,           blockPos.z), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y + scale.y, blockPos.z), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x,           blockPos.y + scale.y, blockPos.z), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		// fase 2

		mesh->pushBack({ vec3(blockPos.x,           blockPos.y,           blockPos.z + scale.z), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y,           blockPos.z + scale.z), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y + scale.y, blockPos.z + scale.z), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		mesh->pushBack({ vec3(blockPos.x,           blockPos.y,           blockPos.z + scale.z), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y + scale.y, blockPos.z + scale.z), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x,           blockPos.y + scale.y, blockPos.z + scale.z), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		// fase 3

		mesh->pushBack({ vec3(blockPos.x, blockPos.y,           blockPos.z          ), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x, blockPos.y + scale.y, blockPos.z          ), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x, blockPos.y + scale.y, blockPos.z + scale.z), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		mesh->pushBack({ vec3(blockPos.x, blockPos.y,           blockPos.z          ), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x, blockPos.y + scale.y, blockPos.z + scale.z), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x, blockPos.y          , blockPos.z + scale.z), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		// fase 4

		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y,           blockPos.z          ), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y + scale.y, blockPos.z          ), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y + scale.y, blockPos.z + scale.z), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y,           blockPos.z          ), vec4(1.0, 0.0, 0.0, 1.0) , vec2(1.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y + scale.y, blockPos.z + scale.z), vec4(0.0, 1.0, 0.0, 1.0) , vec2(0.0, 1.0) });
		mesh->pushBack({ vec3(blockPos.x + scale.x, blockPos.y          , blockPos.z + scale.z), vec4(0.0, 0.0, 1.0, 1.0) , vec2(0.0, 0.0) });

		mesh->fit();
	}
};