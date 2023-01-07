#pragma once

#define UR_CONTENT_API
#include "Engine.h"

namespace Uranium {
	class Model;

	class IndexBuffer {
	private:
		unsigned int ibo;
		unsigned int count;
		unsigned int accessFormat;
		const void* data;

		Model* model;

	public:
		IndexBuffer(Model* _model, const unsigned int _accessFormat, const unsigned int _count, const void* _data); // create IBO
		IndexBuffer(Model* _model, const unsigned int _index); // obtain back IBO

		operator unsigned int() const;

		unsigned int getCount();
		unsigned int getAccessFormat();

		void bind() const;
		void unbind() const;

		void remove();

		void setData(const unsigned int _offset, const unsigned int _count, const void* _data);
	};
}