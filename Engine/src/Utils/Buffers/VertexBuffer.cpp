#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"

#include "VertexBuffer.h"
#include "Utils/Geometry/Model.h"
using namespace Uranium;

VertexBuffer::VertexBuffer(Model* _model, const uint32 _accessFormat, const uint32 _vertexSize, const uint32 _count, const void* _data)
	: accessFormat(_accessFormat), vertexSize(_vertexSize), vertexCount(_count), data(_data), model(_model)
{
	model->bind();
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexSize, data, accessFormat);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();

	model->vbos.push_back(vbo);
}

VertexBuffer::VertexBuffer(Model* _model, const uint32 _vertexSize, const uint32 _index)
	: model(_model), data(nullptr)
{
	vbo = model->vbos[_index];

	int32 usage;
	int32 bufferSize;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);

	vertexSize = _vertexSize;
	vertexCount = bufferSize / _vertexSize;
	accessFormat = usage;
}

uint32 VertexBuffer::getIfNormalized(uint32 _type) {
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

VertexBuffer::operator uint32() {
	return vbo;
}

uint32 VertexBuffer::getVertexSize() {
	return vertexSize;
}

uint32 VertexBuffer::getVertexCount() {
	return vertexCount;
}

uint32 VertexBuffer::getAccessFormat() {
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
	std::vector<uint32>::iterator it = model->vbos.begin();
	while (it != model->vbos.end()) {
		if (this->vbo == *it)
			model->vbos.erase(it);
		else
			it++;
	}
	glDeleteBuffers(1, &vbo);
}

void VertexBuffer::push_Layout(const uint32 _location, const uint32 _compCount, const uint32 _type, const uint32 _offset) {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(_location, _compCount, _type, getIfNormalized(_type), vertexSize, (void*)_offset);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();

	model->attribs.push_back(_location);
}

void VertexBuffer::push_Layout(const uint32 _location, const uint32 _compCount, const uint32 _type) {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(_location, _compCount, _type, getIfNormalized(_type), 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();

	model->attribs.push_back(_location);
}

void VertexBuffer::setData(const uint32 _offset, const uint32 _count, const void* _data) {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, _offset, _count * vertexSize, _data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();
}
