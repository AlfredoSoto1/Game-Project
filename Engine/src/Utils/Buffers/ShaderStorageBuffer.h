#pragma once

#include <cstdint>

namespace BufferUtils {
	class ShaderStorageBuffer {
	private:
		uint32_t ssbo;

	public:
		ShaderStorageBuffer(uint32_t _accessFormat, uint32_t _bindingOffset, uint32_t _size, void* _data);
		~ShaderStorageBuffer();

		operator uint32_t() const;

		void bind() const;
		void unbind() const;

		void setData(uint32_t _offset, uint32_t _size, void* _data);
		void getData(uint32_t _offset, uint32_t _size, void* _data);

	};
}