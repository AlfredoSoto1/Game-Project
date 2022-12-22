#pragma once

#ifndef _VERTEX_BUFFER_IMPL
#define _VERTEX_BUFFER_IMPL

#include <utility>
#include "BufferUtils/BufferE.h"
#include "BufferUtils/VertexBuffer.h"

#define BUFFER_t template<typename Vertex, typename Index>
#define BUFFER_def VertexBuffer<Vertex, Index>

namespace BufferUtils {

	BUFFER_t void BUFFER_def::resizeIndexBuffer() {
		if (indices == nullptr) {
			indices = new Index[initial_Buffer_indexCapacity];
			return;
		}

		Index* tempData = new Index[buffer_indexCapacity * 2];
		for (unsigned int i = 0; i < buffer_indexCount; i++)
			tempData[i] = indices[i];
		delete[] indices;
		indices = tempData;
		buffer_indexCapacity *= 2;
	}

	BUFFER_t void BUFFER_def::resizeVertexBuffer() {
		if (vertices == nullptr) {
			vertices = new Vertex[initialBufferCapacity];
			return;
		}

		Vertex* tempData = new Vertex[bufferCapacity * 2];
		for (unsigned int i = 0; i < bufferCount; i++)
			tempData[i] = (Vertex&&)(vertices[i]);
		delete[] vertices;
		vertices = tempData;
		bufferCapacity *= 2;
	}

	BUFFER_t bool BUFFER_def::needToRezizeVertexBuffer() {
		return bufferCapacity == bufferCount;
	}

	BUFFER_t bool BUFFER_def::needToRezizeIndexBuffer() {
		return buffer_indexCapacity == buffer_indexCount;
	}

	BUFFER_t bool BUFFER_def::needToShrink() {
		return bufferCount < bufferCapacity / 2;
	}

	BUFFER_t BUFFER_def::VertexBuffer(unsigned int _initialBufferCapacity) {
		bufferCount = 0;
		bufferCapacity = _initialBufferCapacity;
		initialBufferCapacity = _initialBufferCapacity;

		buffer_indexCount = 0;			
		buffer_indexCapacity = _initialBufferCapacity;
		initial_Buffer_indexCapacity = _initialBufferCapacity;

		indices = nullptr;
		vertices = nullptr;

		resizeIndexBuffer();
		resizeVertexBuffer();
	}

	BUFFER_t BUFFER_def::~VertexBuffer() {
		clear();
	}

	BUFFER_t bool BUFFER_def::isEmpty() const {
		return buffer_indexCount == 0;
	}

	BUFFER_t unsigned int BUFFER_def::size() const {
		return bufferCount * sizeof(Vertex) + buffer_indexCount * sizeof(Index);
	}

	BUFFER_t unsigned int BUFFER_def::unallocSize() const {
		return bufferCapacity * sizeof(Vertex) + buffer_indexCapacity * sizeof(Index);
	}

	BUFFER_t unsigned int BUFFER_def::vertexCount() const {
		return bufferCount;
	}

	BUFFER_t unsigned int BUFFER_def::vertexCapacity() const {
		return bufferCapacity;
	}

	BUFFER_t unsigned int BUFFER_def::indexCapacity() const {
		return buffer_indexCapacity;
	}

	BUFFER_t unsigned int BUFFER_def::indexCount() const {
		return buffer_indexCount;
	}

	BUFFER_t const Index* BUFFER_def::getIndices() const {
		return indices;
	}

	BUFFER_t const Vertex* BUFFER_def::getVertices() const {
		return vertices;
	}

	BUFFER_t void BUFFER_def::clear() {
		if (indices != nullptr)
			delete[] indices;
		if (vertices != nullptr)
			delete[] vertices;

		bufferCount = 0;
		buffer_indexCount = 0;

		bufferCapacity = initialBufferCapacity;
		buffer_indexCapacity = initial_Buffer_indexCapacity;
	}

	BUFFER_t void BUFFER_def::pushBack(const Vertex& _vertex) {
		if (needToRezizeVertexBuffer())
			resizeVertexBuffer();
		vertices[bufferCount++] = _vertex;
		pushBackIndex(indexCounter++);
	}

	BUFFER_t void BUFFER_def::pushBack(const Vertex&& _vertex) {
		if (needToRezizeVertexBuffer())
			resizeVertexBuffer();
		vertices[bufferCount++] = (Vertex&&)(_vertex);
		pushBackIndex(indexCounter++);
	}

	BUFFER_t void BUFFER_def::pushBackIndex(Index _index) {
		if (needToRezizeIndexBuffer())
			resizeIndexBuffer();
		indices[buffer_indexCount++] = _index;
	}

	BUFFER_t void BUFFER_def::pushBack(const Vertex& _vertex, bool(*compare)(const Vertex& _vertex, Vertex& _other)) {
		for (int i = 0; i < bufferCount; i++) {
			if (!compare(_vertex, vertices[i])) continue;
			pushBackIndex(static_cast<Index>(i));
			return;
		}
		pushBack(_vertex);
	}

	BUFFER_t void BUFFER_def::pushBack(const Vertex&& _vertex, bool(*compare)(const Vertex&& _vertex, Vertex& _other)) {
		for (int i = 0; i < bufferCount; i++) {
			if (!compare((Vertex&&)_vertex, vertices[i])) continue;
			pushBackIndex(static_cast<Index>(i));
			return;
		}
		pushBack((Vertex&&)_vertex);
	}

	BUFFER_t template<typename... Args> void BUFFER_def::emplaceBack(Args&& ... _args) {
		if (needToRezizeVertexBuffer())
			resizeVertexBuffer();
		new(&vertices[bufferCount++]) Vertex{ std::forward<Args>(_args) ...};
		pushBackIndex(indexCounter++);
	}
}

#undef BUFFER_t
#undef BUFFER_def

#endif // !_VERTEX_BUFFER_IMPL
