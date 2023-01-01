#pragma once

#include <cstdint>

namespace BufferUtils {
	class VertexArray;

	class VirtualBuffer {
	private:
		uint32_t vbo;
		uint32_t accessFormat;
		uint32_t vertexSize;
		uint32_t vertexCount;
		const void* data;

		VertexArray* vao;

		uint32_t getIfNormalized(uint32_t _type);

	public:
		VirtualBuffer(VertexArray* _vao, const uint32_t _vertexSize, const uint32_t _index);
		VirtualBuffer(VertexArray* _vao, const uint32_t _accessFormat, const uint32_t _vertexSize, const uint32_t _count, const void* _data);
	
		operator uint32_t();

		uint32_t getVertexSize();
		uint32_t getVertexCount();
		uint32_t getAccessFormat();

		void bind() const;
		void unbind() const;

		void remove();

		void setData(const uint32_t _offset, const uint32_t _count, const void* _data);

		void push_Layout(const uint32_t _location, const uint32_t _compCount, const uint32_t _type);
		void push_Layout(const uint32_t _location, const uint32_t _compCount, const uint32_t _type, const uint32_t _offset);

	};
}