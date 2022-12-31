#pragma once

#include <cstdint>
#include "Utils/Buffers/VertexBuffer.h"

namespace GeometryUtils {

	class Mesh { 
	private:
		uint32_t vao;
		uint32_t ibo;

		uint32_t maxAttribs;
		uint32_t accessFormat;

		uint32_t indexCount;
		uint32_t vertexBuffer;
		uint32_t* attribBuffer;

	public:
		Mesh(uint32_t _maxAttribs, uint32_t _accessFormat);
		~Mesh();

		uint32_t getIndexCount() const;

		void dispose();

		void bind() const;
		void unbind() const;

		/*
			Indices
		*/
		void createIndexBuffer(const uint32_t _indexCount, const uint32_t _indexSize, const void* _data);

		/*
			Attributes
		*/
		void createAttributeBuffer(const uint32_t _location, const uint32_t _componentCount, const uint32_t _type, const uint32_t _sizeBytes, const void* _data);
		
		/*
			Vertices
		*/
		void createVertexBuffer(const uint32_t _sizeBytes, const void* _data);
		void setAttribPointer(const uint32_t _location, const uint32_t _componentCount, const uint32_t _type, const uint32_t _vertexSize, const void* _offset);

		template<typename Vertex, typename Index>
		void setVertexBuffer(const BufferUtils::VertexBuffer<Vertex, Index>& _vertexBuffer) {
			createIndexBuffer(_vertexBuffer.indexCount(), _vertexBuffer.indexSize(), _vertexBuffer.getIndices());
			createVertexBuffer(_vertexBuffer.vertexCountSize(), _vertexBuffer.getVertices());
		}


		/*
			update Data
		*/

		void updateVertexData(const uint32_t _start, const uint32_t _sizeBytes, const void* _vertexData);

	};
}