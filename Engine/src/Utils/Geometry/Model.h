#pragma once

#define UR_CONTENT_API
#include "Engine.h"

#include <vector>
#include <memory>

namespace Uranium {

	class Renderer;
	class IndexBuffer;
	class VertexBuffer;

	class Model {
	private:
		friend class IndexBuffer;
		friend class VertexBuffer;

		unsigned int vao;
		unsigned int boundIbo;

		mutable std::vector<unsigned int> attribs;
		mutable std::vector<std::shared_ptr<IndexBuffer>> ibos;
		mutable std::vector<std::shared_ptr<VertexBuffer>> vbos;

	public:
		void enableAttribs() const;
		void disableAttribs() const;

	public:
		Model();
		~Model();

		operator unsigned int();

		unsigned int getIndexCount() const;

		void bind() const;
		void unbind() const;

		void bindIbo(const unsigned int _boundIbo);
	};
}