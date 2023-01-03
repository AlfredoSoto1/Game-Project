#pragma once

#include <stack>
#include <vector>
#include <cstdint>
#include <utility> 

namespace Render {
	class Renderer;
}

namespace BufferUtils {
	class IndexBuffer;
	class VirtualBuffer;
}

namespace GeometryUtils {
	class Model {
	private:
		friend class Render::Renderer;
		friend class BufferUtils::IndexBuffer;
		friend class BufferUtils::VirtualBuffer;

		uint32_t vao;
		uint32_t boundIbo;

		mutable std::vector<uint32_t> vbos;
		mutable std::vector<uint32_t> attribs;
		mutable std::vector<std::pair<uint32_t, uint32_t>> ibos;

	public:
		void enableAttribs() const;
		void disableAttribs() const;

	public:
		Model();
		~Model();

		operator uint32_t();

		uint32_t getIndexCount() const;

		void bind() const;
		void unbind() const;

		void bindIbo(const uint32_t _boundIbo);
	};
}