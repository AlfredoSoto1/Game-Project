#pragma once

#define UR_CONTENT_API
#include "Engine.h"

#include <vector>
#include <cstdint>
#include <utility> 

namespace Uranium {

	class Renderer;
	class IndexBuffer;
	class VertexBuffer;

	class Model {
	private:
		friend class IndexBuffer;
		friend class VertexBuffer;

		uint32 vao;
		uint32 boundIbo;

		mutable std::vector<uint32> vbos;
		mutable std::vector<uint32> attribs;
		mutable std::vector<std::pair<uint32, uint32>> ibos;

	public:
		void enableAttribs() const;
		void disableAttribs() const;

	public:
		Model();
		~Model();

		operator uint32();

		uint32 getIndexCount() const;

		void bind() const;
		void unbind() const;

		void bindIbo(const uint32 _boundIbo);
	};
}