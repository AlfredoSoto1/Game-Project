#pragma once

#define UR_CONTENT_API
#include "Engine.h"

namespace Uranium {

	class Model;

	class VertexBuffer {
	private:
		uint32 vbo;
		uint32 accessFormat;
		uint32 vertexSize;
		uint32 vertexCount;
		const void* data;

		Model* model;

		uint32 getIfNormalized(uint32 _type);

	public:
		VertexBuffer(Model* _model, const uint32 _vertexSize, const uint32 _index);
		VertexBuffer(Model* _model, const uint32 _accessFormat, const uint32 _vertexSize, const uint32 _count, const void* _data);
	
		operator uint32();

		uint32 getVertexSize();
		uint32 getVertexCount();
		uint32 getAccessFormat();

		void bind() const;
		void unbind() const;

		void remove();

		void setData(const uint32 _offset, const uint32 _count, const void* _data);

		void push_Layout(const uint32 _location, const uint32 _compCount, const uint32 _type);
		void push_Layout(const uint32 _location, const uint32 _compCount, const uint32 _type, const uint32 _offset);

	};
}