#pragma once

#include <vector>
#include <memory>

namespace Uranium {

	class IndexBuffer;
	class VertexBuffer;

	class Model {
	public:
		Model();
		virtual ~Model();

		operator unsigned int();

		unsigned int getIndexCount() const;

		void bind() const;
		void unbind() const;

		void enableAttribs() const;
		void disableAttribs() const;

		void bindIbo(const unsigned int _boundIbo);

	private:
		friend class IndexBuffer;
		friend class VertexBuffer;

		unsigned int vao;
		unsigned int boundIbo;

		mutable std::vector<unsigned int> attribs;
		mutable std::vector<std::shared_ptr<IndexBuffer>> ibos;
		mutable std::vector<std::shared_ptr<VertexBuffer>> vbos;

	};
}