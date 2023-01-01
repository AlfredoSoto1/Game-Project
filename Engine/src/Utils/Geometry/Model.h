#pragma once

#include <vector>

namespace BufferUtils {
	class VertexArray;
	class IndexBuffer;
	class VirtualBuffer;

	template<typename Vertex, typename Index> 
	class VertexBuffer;
}

namespace GeometryUtils {
	
	class Model {
	private:
		std::vector<BufferUtils::IndexBuffer> indexBuffers;
		
		BufferUtils::VertexArray* vao;

	public:
		Model();
		virtual ~Model();

		BufferUtils::VertexArray& getVao();

	};
}