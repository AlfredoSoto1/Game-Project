#define GLEW_STATIC
#include <GL/glew.h>

#include "VertexArray.h"

using namespace GeometryUtils;

VertexArray::VertexArray() 
	:	currBufferBound(0), currIboBound(0)
{
	glGenVertexArrays(1, &vao);

	vbos.reserve(2);
	ibos.reserve(2);
	enableAttribs.reserve(4);
}

VertexArray::~VertexArray()
{
	for (uint32_t& ibo : ibos) {
		glDeleteBuffers(1, &ibo);
	}

	for (uint32_t& vbo : vbos) {
		glDeleteBuffers(1, &vbo);
	}

	glDeleteVertexArrays(1, &vao);

	vbos.clear();
	ibos.clear();
	enableAttribs.clear();
}

void VertexArray::bind() {
	if (currIboBound == 0)
		throw 1;
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currIboBound);
	for (uint32_t& enabAttrb : enableAttribs)
		glEnableVertexAttribArray(enabAttrb);
}

void VertexArray::unbind() {
	for (uint32_t& enabAttrb : enableAttribs)
		glDisableVertexAttribArray(enabAttrb);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexArray::enable(const uint32_t _enableIndexBuffer) {
	currIboBound = _enableIndexBuffer;
}

uint32_t VertexArray::getIfNormalized(uint32_t _type) {
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

void VertexArray::bindBuffer(const uint32_t _target,const uint32_t _accessFormat, const uint32_t _size, const void* _data) {
	glBindVertexArray(vao);

	uint32_t buffId;
	glGenBuffers(1, &buffId);

	glBindBuffer(_target, buffId);
	glBufferData(_target, _size, _data, _accessFormat);
	glBindBuffer(_target, 0);

	glBindVertexArray(0);

	bool isIBO = false;
	switch (_target) {
	case GL_ARRAY_BUFFER:			vbos.push_back(buffId); isIBO = false; break;
	case GL_ELEMENT_ARRAY_BUFFER: 	ibos.push_back(buffId); isIBO = true;  break;
	}

	if (isIBO) {
		currIboBound = ibos[0];
	}
	else {
		currBufferBound = buffId;
	}
}

void VertexArray::addLayout(const uint32_t _layoutLocation, const uint32_t _count, const uint32_t _type, const uint32_t _vertexSize, const uint32_t _offset) {
	if (_count <= 0 && _count > 4)
		throw 1;

	if (currBufferBound == 0)
		throw 1;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, currBufferBound);
	glVertexAttribPointer(_layoutLocation, _count, _type, getIfNormalized(_type), _vertexSize, (void*)_offset);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	enableAttribs.push_back(_layoutLocation);
}
