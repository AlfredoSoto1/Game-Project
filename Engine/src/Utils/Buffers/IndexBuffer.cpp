#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"

#include <utility>

#include "IndexBuffer.h"
#include "Utils/Geometry/Model.h"

using namespace Uranium;

IndexBuffer::IndexBuffer(Model* _model, const uint32 _accessFormat, const uint32 _count, const void* _data)
	: accessFormat(_accessFormat), count(_count), data(_data), model(_model)
{
	model->bind();
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, accessFormat);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	model->unbind();

	model->ibos.push_back(std::pair<uint32, uint32>(ibo, _count));
}

IndexBuffer::IndexBuffer(Model* _model, const uint32 _index)
	: model(_model), data(nullptr)
{
	ibo = model->ibos[_index].first;

	int32 usage;
	int32 bufferSize;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);

	count = bufferSize / sizeof(unsigned int);
	accessFormat = usage;
}

IndexBuffer::operator uint32() {
	return ibo;
}

uint32 IndexBuffer::getCount() {
	return count;
}

uint32 IndexBuffer::getAccessFormat() {
	return accessFormat;
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::remove() {
	std::vector<std::pair<uint32, uint32>>::iterator it = model->ibos.begin();
	while (it != model->ibos.end()) {
		if (this->ibo == it->first)
			model->ibos.erase(it);
		else
			it++;
	}
	glDeleteBuffers(1, &ibo);
}

void IndexBuffer::setData(const uint32 _offset, const uint32 _count, const void* _data) {
	model->bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _offset, _count, _data);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	model->unbind();
}
