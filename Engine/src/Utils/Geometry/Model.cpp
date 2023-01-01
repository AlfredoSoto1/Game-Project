#include "Model.h"

#include "Utils/Buffers/VertexArray.h"
#include "Utils/Buffers/IndexBuffer.h"
#include "Utils/Buffers/VertexBuffer.h"

using namespace BufferUtils;
using namespace GeometryUtils;

Model::Model() {
	vao = new VertexArray();
}

Model::~Model() {
	delete vao;
}

VertexArray& Model::getVao() {
	return *vao;
}

