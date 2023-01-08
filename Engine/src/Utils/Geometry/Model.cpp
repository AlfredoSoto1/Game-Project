#define GLEW_STATIC
#include <GL/glew.h>

#include "Model.h"
#include "Utils/Buffers/IndexBuffer.h"
#include "Utils/Buffers/VertexBuffer.h"
using namespace Uranium;

Model::Model() 
	:	boundIbo(0)
{
	glGenVertexArrays(1, &vao);
}

Model::~Model()
{
	for (std::shared_ptr<IndexBuffer>& ibo : ibos) {
		unsigned int id = *ibo;
		glDeleteBuffers(1, &id);
	}
	for (std::shared_ptr<VertexBuffer>& vbo : vbos) {
		unsigned int id = *vbo;
		glDeleteBuffers(1, &id);
	}
	glDeleteVertexArrays(1, &vao);
	vbos.clear();
	ibos.clear();
	attribs.clear();
}

Model::operator unsigned int() {
	return vao;
}

unsigned int Model::getIndexCount() const {
	return ibos[boundIbo]->getCount();
}

void Model::bind() const {
	glBindVertexArray(vao);
}

void Model::unbind() const {
	glBindVertexArray(0);
}

void Model::enableAttribs() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibos[boundIbo]);
	for (unsigned int& attr : attribs)
		glEnableVertexAttribArray(attr);
}

void Model::disableAttribs() const {
	for (unsigned int& attr : attribs)
		glDisableVertexAttribArray(attr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::bindIbo(const unsigned int _boundIbo) {
	this->boundIbo = _boundIbo;
}
