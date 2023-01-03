#define GLEW_STATIC
#include <GL/glew.h>

#include "Utils/Geometry/Model.h"
using namespace GeometryUtils;

#include "VirtualBuffer.h"
using namespace BufferUtils;

VirtualBuffer::VirtualBuffer(Model* _model, const uint32_t _accessFormat, const uint32_t _vertexSize, const uint32_t _count, const void* _data)
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

VirtualBuffer::VirtualBuffer(Model* _model, const uint32_t _vertexSize, const uint32_t _index)
	: model(_model)
{
	vbo = model->vbos[_index];

	int32_t usage;
	int32_t bufferSize;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);

	vertexSize = _vertexSize;
	vertexCount = bufferSize / _vertexSize;
	accessFormat = usage;
}

uint32_t VirtualBuffer::getIfNormalized(uint32_t _type) {
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

VirtualBuffer::operator uint32_t() {
	return vbo;
}

uint32_t VirtualBuffer::getVertexSize() {
	return vertexSize;
}

uint32_t VirtualBuffer::getVertexCount() {
	return vertexCount;
}

uint32_t VirtualBuffer::getAccessFormat() {
	return accessFormat;
}

void VirtualBuffer::bind() const {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VirtualBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();
}

void VirtualBuffer::remove() {
	std::vector<uint32_t>::iterator it = model->vbos.begin();
	while (it != model->vbos.end()) {
		if (this->vbo == *it)
			model->vbos.erase(it);
		else
			it++;
	}
	glDeleteBuffers(1, &vbo);
}

void VirtualBuffer::push_Layout(const uint32_t _location, const uint32_t _compCount, const uint32_t _type, const uint32_t _offset) {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(_location, _compCount, _type, getIfNormalized(_type), vertexSize, (void*)_offset);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();

	model->attribs.push_back(_location);
}

void VirtualBuffer::push_Layout(const uint32_t _location, const uint32_t _compCount, const uint32_t _type) {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(_location, _compCount, _type, getIfNormalized(_type), 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();

	model->attribs.push_back(_location);
}

void VirtualBuffer::setData(const uint32_t _offset, const uint32_t _count, const void* _data) {
	model->bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, _offset, _count * vertexSize, _data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	model->unbind();
}
