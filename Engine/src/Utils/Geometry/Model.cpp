#define GLEW_STATIC
#include <GL/glew.h>

#include "Model.h"

using namespace GeometryUtils;

Model::Model() 
	:	boundIbo(0)
{
	glGenVertexArrays(1, &vao);
}

Model::~Model()
{
	for (std::pair<uint32_t, uint32_t>& ibo : ibos) {
		glDeleteBuffers(1, &ibo.first);
	}
	for (uint32_t& vbo : vbos) {
		glDeleteBuffers(1, &vbo);
	}
	glDeleteVertexArrays(1, &vao);
	vbos.clear();
	ibos.clear();
	attribs.clear();
}

Model::operator uint32_t() {
	return vao;
}

uint32_t Model::getIndexCount() const {
	return ibos[boundIbo].second;
}

void Model::bind() const {
	glBindVertexArray(vao);
}

void Model::unbind() const {
	glBindVertexArray(0);
}

void Model::enableAttribs() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[boundIbo].first);
	for (uint32_t& attr : attribs)
		glEnableVertexAttribArray(attr);
}

void Model::disableAttribs() const {
	for (uint32_t& attr : attribs)
		glDisableVertexAttribArray(attr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::bindIbo(const uint32_t _boundIbo) {
	this->boundIbo = _boundIbo;
}
