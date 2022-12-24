#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>

#include "MemoryUtils/Mesh.h"

using namespace MemoryUtils;

Mesh::Mesh(uint32_t _maxAttribs, uint32_t _accessFormat) {
	// creates VAO
	glGenVertexArrays(1, &vao);
	maxAttribs = _maxAttribs;
	accessFormat = _accessFormat;

	vao = 0;
	ibo = 0;
	indexCount = 0;
	vertexBuffer = 0;
	attribBuffer = nullptr;
}

Mesh::~Mesh() {
	// disposes all content from VAO
	dispose();

	// deletes VAO
	glDeleteVertexArrays(1, &vao);
}

uint32_t Mesh::getIndexCount() const {
	return indexCount;
}

void Mesh::bind() const {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	for (uint32_t i = 0; i < maxAttribs; i++) {
		glEnableVertexAttribArray(i);
	}
}

void Mesh::unbind() const {
	for (uint32_t i = 0; i < maxAttribs; i++) {
		glDisableVertexAttribArray(i);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::dispose() {
	// Deletes all index buffer data
	glDeleteBuffers(1, &ibo);

	// Deletes all VBO buffer data
	if (attribBuffer != nullptr) {
		for (uint32_t i = 0; i < maxAttribs; i++)
			glDeleteBuffers(1, &attribBuffer[i]);
		delete[] attribBuffer;
		attribBuffer = nullptr;
	}
	else {
		glDeleteBuffers(1, &vertexBuffer);
	}

	ibo = 0;
	indexCount = 0;
	vertexBuffer = 0;
}

void Mesh::createIndexBuffer(const uint32_t _indexCount, const uint32_t _indexSize, const void* _data) {
	indexCount = _indexCount;
	glBindVertexArray(vao);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * _indexSize, _data, accessFormat);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::createVertexBuffer(const uint32_t _sizeBytes, const void* _data) {
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _sizeBytes, _data, accessFormat);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::setAttribPointer(const uint32_t _location, const uint32_t _componentCount, const uint32_t _type, const uint32_t _vertexSize, const void* _offset) {
	if (_location >= maxAttribs)
		return;
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(_location, _componentCount, GL_FLOAT, GL_FALSE, _vertexSize, _offset);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::createAttributeBuffer(const uint32_t _location, const uint32_t _componentCount, const uint32_t _type, const uint32_t _sizeBytes, const void* _data) {
	if (attribBuffer == nullptr)
		attribBuffer = new uint32_t[maxAttribs];
	if (_location >= maxAttribs)
		return;

	glBindVertexArray(vao);

	glGenBuffers(1, &attribBuffer[_location]);
	glBindBuffer(GL_ARRAY_BUFFER, attribBuffer[_location]);
	glBufferData(GL_ARRAY_BUFFER, _sizeBytes, _data, accessFormat);
	glVertexAttribPointer(_location, _componentCount, _type, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::updateVertexData(const uint32_t _start, const uint32_t _sizeBytes, const void* _vertexData) {
	//glBindVertexArray(vao);

	//glBindBuffer(_bufferTypeEnum, _bufferId);
	//glBufferSubData(_bufferTypeEnum, _startOffsetBytes, _sizeBytes, _data);
	//glBindBuffer(_bufferTypeEnum, 0);

	//glBindVertexArray(0);
}