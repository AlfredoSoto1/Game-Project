#pragma once

#define UR_CONTENT_API
#include "Engine.h"

namespace Uranium {
	class Model;

	class IndexBuffer {
	private:
		uint32 ibo;
		uint32 count;
		uint32 accessFormat;
		const void* data;

		Model* model;

	public:
		IndexBuffer(Model* _model, const uint32 _accessFormat, const uint32 _count, const void* _data);
		IndexBuffer(Model* _model, const uint32 _index);

		operator uint32();

		uint32 getCount();
		uint32 getAccessFormat();

		void bind() const;
		void unbind() const;

		void remove();

		void setData(const uint32 _offset, const uint32 _count, const void* _data);
	};
}