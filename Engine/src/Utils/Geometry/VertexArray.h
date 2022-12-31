#pragma once

#include <stack>
#include <vector>
#include <cstdint>

namespace GeometryUtils {

	class VertexArray {
	private:
		uint32_t vao;
		uint32_t currIboBound;
		uint32_t currBufferBound;

		std::vector<uint32_t> vbos;
		std::vector<uint32_t> ibos;

		std::vector<uint32_t> enableAttribs;

		uint32_t getIfNormalized(uint32_t _type);	// returns GL_TRUE || GL_FALSE if and only if the "type" should be normalized

	public:
		VertexArray();
		~VertexArray();

		void bind();
		void unbind();

		void enable(const uint32_t _enableIndexBuffer);

		void bindBuffer(const uint32_t _target, const uint32_t _accessFormat, const uint32_t _size, const void* _data);
		void addLayout(const uint32_t _layoutLocation, const uint32_t _count, const uint32_t _type, const uint32_t _vertexSize, const uint32_t _offset);

	};
}