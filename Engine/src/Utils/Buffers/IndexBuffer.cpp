#define GLEW_STATIC
#include <GL/glew.h>
#include <utility>

#include "IndexBuffer.h"
using namespace BufferUtils;

#include "Utils/Geometry/Model.h"
using namespace GeometryUtils;

IndexBuffer::IndexBuffer(Model* _model, const uint32_t _accessFormat, const uint32_t _count, const void* _data)
	: accessFormat(_accessFormat), count(_count), data(_data), model(_model)
{
	model->bind();
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, accessFormat);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	model->unbind();

	model->ibos.push_back(std::pair<uint32_t, uint32_t>(ibo, _count));
}

IndexBuffer::IndexBuffer(Model* _model, const uint32_t _index)
	: model(_model)
{
	ibo = model->ibos[_index].first;

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
	std::vector<std::pair<uint32_t, uint32_t>>::iterator it = model->ibos.begin();
	while (it != model->ibos.end()) {
		if (this->ibo == it->first)
			model->ibos.erase(it);
		else
			it++;
	}
	glDeleteBuffers(1, &ibo);
}

void IndexBuffer::setData(const uint32_t _offset, const uint32_t _count, const void* _data) {
	model->bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _offset, _count, _data);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	model->unbind();
}
