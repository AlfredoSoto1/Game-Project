#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"

#include "Model.h"
using namespace Uranium;

Model::Model() 
	:	boundIbo(0)
{
	glGenVertexArrays(1, &vao);
}

Model::~Model()
{
	for (std::pair<uint32, uint32>& ibo : ibos) {
		glDeleteBuffers(1, &ibo.first);
	}
	for (uint32& vbo : vbos) {
		glDeleteBuffers(1, &vbo);
	}
	glDeleteVertexArrays(1, &vao);
	vbos.clear();
	ibos.clear();
	attribs.clear();
}

Model::operator uint32() {
	return vao;
}

uint32 Model::getIndexCount() const {
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
	for (uint32& attr : attribs)
		glEnableVertexAttribArray(attr);
}

void Model::disableAttribs() const {
	for (uint32& attr : attribs)
		glDisableVertexAttribArray(attr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::bindIbo(const uint32 _boundIbo) {
	this->boundIbo = _boundIbo;
}
