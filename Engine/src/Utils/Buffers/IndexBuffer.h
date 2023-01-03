#pragma once

#include <cstdint>

namespace GeometryUtils {
	class Model;
}

namespace BufferUtils {
	class IndexBuffer {
	private:
		uint32_t ibo;
		uint32_t count;
		uint32_t accessFormat;
		const void* data;

		GeometryUtils::Model* model;

	public:
		IndexBuffer(GeometryUtils::Model* _model, const uint32_t _accessFormat, const uint32_t _count, const void* _data);
		IndexBuffer(GeometryUtils::Model* _model, const uint32_t _index);

		operator uint32_t();

		uint32_t getCount();
		uint32_t getAccessFormat();

		void bind() const;
		void unbind() const;

		void remove();

		void setData(const uint32_t _offset, const uint32_t _count, const void* _data);
	};
}