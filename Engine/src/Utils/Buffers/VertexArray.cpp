#define GLEW_STATIC
#include <GL/glew.h>

#include "VertexArray.h"

using namespace BufferUtils;

VertexArray::VertexArray() 
	:	boundIbo(0)
{
	glGenVertexArrays(1, &vao);
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
	attribs.clear();
}

VertexArray::operator uint32_t() {
	return vao;
}

void VertexArray::bind() const {
	glBindVertexArray(vao);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

void VertexArray::enableAttribs() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[boundIbo]);
	for (uint32_t& attr : attribs)
		glEnableVertexAttribArray(attr);
}

void VertexArray::disableAttribs() const {
	for (uint32_t& attr : attribs)
		glDisableVertexAttribArray(attr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::bindIbo(const uint32_t _boundIbo) {
	this->boundIbo = _boundIbo;
}
