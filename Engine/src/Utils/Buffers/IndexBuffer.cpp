#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"

#include <memory>
#include "IndexBuffer.h"
#include "Uranium/Utils/Geometry/Model.h"
using namespace Uranium;

IndexBuffer::IndexBuffer(Model* _model, const unsigned int _accessFormat, const unsigned int _count, const void* _data)
	: accessFormat(_accessFormat), count(_count), data(_data), model(_model)
{
	model->bind();
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, accessFormat);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	model->unbind();

	model->ibos.push_back(std::make_shared<IndexBuffer>(*this));
}

IndexBuffer::IndexBuffer(Model* _model, const unsigned int _index)
	: accessFormat(GL_STATIC_DRAW), count(0), data(nullptr), model(nullptr)
{
	std::shared_ptr<IndexBuffer>& iboPtr = _model->ibos[_index];

	data = iboPtr->data;
	model = iboPtr->model;

	ibo = iboPtr->ibo;
	count = iboPtr->count;
	accessFormat = iboPtr->accessFormat;
}

IndexBuffer::operator unsigned int() const {
	return ibo;
}

unsigned int IndexBuffer::getCount() {
	return count;
}

unsigned int IndexBuffer::getAccessFormat() {
	return accessFormat;
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::remove() {
	std::vector<std::shared_ptr<IndexBuffer>>::iterator it = model->ibos.begin();
	while (it != model->ibos.end()) {
		if (this->ibo == (*it)->ibo)
			model->ibos.erase(it);
		else
			it++;
	}
	glDeleteBuffers(1, &ibo);
}

void IndexBuffer::setData(const unsigned int _offset, const unsigned int _count, const void* _data) {
	model->bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _offset, _count, _data);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	model->unbind();
}
