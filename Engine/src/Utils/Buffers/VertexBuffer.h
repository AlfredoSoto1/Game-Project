#pragma once

namespace Uranium {

	class Model;

	class VertexBuffer {
	private:
		unsigned int vbo;
		unsigned int accessFormat;
		unsigned int vertexSize;
		unsigned int vertexCount;
		const void* data;

		Model* model;

		unsigned int getIfNormalized(unsigned int _type);

	public:
		VertexBuffer(Model* _model, const unsigned int _index); // obtain VBO
		VertexBuffer(Model* _model, const unsigned int _accessFormat, const unsigned int _vertexSize, const unsigned int _count, const void* _data); // create VBO
	
		operator unsigned int();

		unsigned int getVertexSize();
		unsigned int getVertexCount();
		unsigned int getAccessFormat();

		void bind() const;
		void unbind() const;

		void remove();

		void setData(const unsigned int _offset, const unsigned int _count, const void* _data);

		void push_Layout(const unsigned int _location, const unsigned int _compCount, const unsigned int _type);
		void push_Layout(const unsigned int _location, const unsigned int _compCount, const unsigned int _type, const unsigned int _offset);

	};
}