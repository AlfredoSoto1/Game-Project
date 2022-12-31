#pragma once

#include <stack>
#include <vector>
#include <cstdint>

namespace BufferUtils {

	class IndexBuffer;
	class VirtualBuffer;

	class VertexArray {
	private:
		friend class IndexBuffer;
		friend class VirtualBuffer;

		uint32_t vao;
		uint32_t boundIbo;

		mutable std::vector<uint32_t> ibos;
		mutable std::vector<uint32_t> vbos;
		mutable std::vector<uint32_t> attribs;

	public:
		VertexArray();
		~VertexArray();

		operator uint32_t();

		void bind() const;
		void unbind() const;

		void enableAttribs() const;
		void disableAttribs() const;

		void bindIbo(const uint32_t _boundIbo);
	};
}