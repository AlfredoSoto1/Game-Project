#define GLEW_STATIC
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"

using namespace BufferUtils;

IndexBuffer::IndexBuffer(VertexArray* _vao, const uint32_t _accessFormat, const uint32_t _count, const void* _data)
	: accessFormat(_accessFormat), count(_count), data(_data), vao(_vao)
{
	vao->bind();
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, accessFormat);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	vao->unbind();

	vao->ibos.push_back(ibo);
}

IndexBuffer::IndexBuffer(VertexArray* _vao, const uint32_t _index)
	: vao(_vao)
{
	ibo = vao->ibos[_index];

	int32_t usage;
	int32_t bufferSize;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);

	count = bufferSize / sizeof(unsigned int);
	accessFormat = usage;
}

IndexBuffer::operator uint32_t() {
	return ibo;
}

uint32_t IndexBuffer::getCount() {
	return count;
}

uint32_t IndexBuffer::getAccessFormat() {
	return accessFormat;
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::remove() {
	std::vector<uint32_t>::iterator it = vao->ibos.begin();
	while (it != vao->ibos.end()) {
		if (this->ibo == *it)
			vao->ibos.erase(it);
		else
			it++;
	}
	glDeleteBuffers(1, &ibo);
}

void IndexBuffer::setData(const uint32_t _offset, const uint32_t _count, const void* _data) {
	vao->bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _offset, _count, _data);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	vao->unbind();
}
