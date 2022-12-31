#pragma once

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
		BufferUtils::VertexArray* vao;

	public:
		Model();
		~Model();

	};
}