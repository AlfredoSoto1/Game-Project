#pragma once

#include <stack>
#include <vector>
#include <cstdint>
#include <utility> 

namespace BufferUtils {

	class IndexBuffer;
	class VirtualBuffer;

	class VertexArray {
	private:
		friend class IndexBuffer;
		friend class VirtualBuffer;

		uint32_t vao;
		uint32_t boundIbo;

		mutable std::vector<uint32_t> vbos;
		mutable std::vector<uint32_t> attribs;
		mutable std::vector<std::pair<uint32_t, uint32_t>> ibos;

	public:
		VertexArray();
		~VertexArray();

		operator uint32_t();

		uint32_t getIndexCount() const;

		void bind() const;
		void unbind() const;

		void enableAttribs() const;
		void disableAttribs() const;

		void bindIbo(const uint32_t _boundIbo);
	};
}