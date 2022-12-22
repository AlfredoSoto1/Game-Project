#pragma once

#ifndef _VERTEX_BUFFER_HEADER
#define _VERTEX_BUFFER_HEADER

namespace BufferUtils {

	enum Buffer;

	template<typename Vertex, typename Index>
	class VertexBuffer {
	private:
		unsigned int bufferCount;			// buffer count of used vertices
		unsigned int bufferCapacity;		// buffer capacity of total buffer (vertices)
		unsigned int initialBufferCapacity;	// initial capacity of buffer (vertices)

		unsigned int buffer_indexCount;				// count of total indices
		unsigned int buffer_indexCapacity;			// buffer capacity of total buffer (indices)
		unsigned int initial_Buffer_indexCapacity;	// initial capacity of buffer (indices)

		Index indexCounter;

		Index* indices;
		Vertex* vertices;

		void resizeIndexBuffer();
		void resizeVertexBuffer();

		bool needToRezizeIndexBuffer();
		bool needToRezizeVertexBuffer();
		bool needToShrink();

		void pushBackIndex(Index _index);

	public:
		VertexBuffer(unsigned int _initialBufferCapacity);
		~VertexBuffer();

		bool isEmpty() const;

		unsigned int size() const;
		unsigned int indexCount() const;
		unsigned int unallocSize() const;
		unsigned int vertexCount() const;
		unsigned int indexCapacity() const;
		unsigned int vertexCapacity() const;

		const Index* getIndices() const;
		const Vertex* getVertices() const;

		void clear();

		void pushBack(const Vertex& _vertex);	// push back a copy ref
		void pushBack(const Vertex&& _vertex);	// push back an rvalue ref

		void pushBack(const Vertex& _vertex, bool(*compare)(const Vertex& _vertex, Vertex& _other));	// push back a copy ref
		void pushBack(const Vertex&& _vertex, bool(*compare)(const Vertex&& _vertex, Vertex& _other));	// push back an rvalue ref

		template<typename... Args>
		void emplaceBack(Args&& ... _args);

	};
}

#include "BufferUtils/implementation/VertexBuffer_impl.h"

#endif // !_VERTEX_BUFFER

