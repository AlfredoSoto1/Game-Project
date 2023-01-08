#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"

#include <memory>

#include "VertexBuffer.h"
#include "Uranium/Utils/Geometry/Model.h"
using namespace Uranium;

VertexBuffer::VertexBuffer(Model* _model, const unsigned int _accessFormat, const unsigned int _vertexSize, const unsigned int _count, const void* _data)
	: accessFormat(_accessFormat), vertexSize(_vertexSize), vertexCount(_count), data(_data), model(_model)
{
	model->bind();
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexSize, data, accessFormat);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();

	model->vbos.push_back(std::make_shared<VertexBuffer>(*this));
}

VertexBuffer::VertexBuffer(Model* _model, const unsigned int _index)
	: accessFormat(GL_STATIC_DRAW), vertexSize(0), vertexCount(0), data(nullptr), model(nullptr)
{
	std::shared_ptr<VertexBuffer>& vboPtr = _model->vbos[_index];

	data = vboPtr->data;
	model = vboPtr->model;

	vbo = vboPtr->vbo;
	vertexSize = vboPtr->vertexSize;
	vertexCount = vboPtr->vertexCount;
	accessFormat = vboPtr->accessFormat;
}

unsigned int VertexBuffer::getIfNormalized(unsigned int _type) {
	switch (_type) {
	case GL_BYTE:			return GL_FALSE;
	case GL_INT:			return GL_FALSE;
	case GL_SHORT:			return GL_FALSE;
	case GL_FLOAT:			return GL_FALSE;
	case GL_DOUBLE:			return GL_FALSE;
	case GL_UNSIGNED_INT:	return GL_FALSE;
	case GL_UNSIGNED_SHORT:	return GL_FALSE;
	case GL_UNSIGNED_BYTE:	return GL_TRUE;
	}
}

VertexBuffer::operator unsigned int() {
	return vbo;
}

unsigned int VertexBuffer::getVertexSize() {
	return vertexSize;
}

unsigned int VertexBuffer::getVertexCount() {
	return vertexCount;
}

unsigned int VertexBuffer::getAccessFormat() {
	return accessFormat;
}

void VertexBuffer::bind() const {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();
}

void VertexBuffer::remove() {
	std::vector<std::shared_ptr<VertexBuffer>>::iterator it = model->vbos.begin();
	while (it != model->vbos.end()) {
		if (this->vbo == (*it)->vbo)
			model->vbos.erase(it);
		else
			it++;
	}
	glDeleteBuffers(1, &vbo);
}

void VertexBuffer::push_Layout(const unsigned int _location, const unsigned int _compCount, const unsigned int _type, const unsigned int _offset) {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(_location, _compCount, _type, getIfNormalized(_type), vertexSize, (void*)_offset);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();

	model->attribs.push_back(_location);
}

void VertexBuffer::push_Layout(const unsigned int _location, const unsigned int _compCount, const unsigned int _type) {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(_location, _compCount, _type, getIfNormalized(_type), 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();

	model->attribs.push_back(_location);
}

void VertexBuffer::setData(const unsigned int _offset, const unsigned int _count, const void* _data) {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, _offset, _count * vertexSize, _data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();
}
