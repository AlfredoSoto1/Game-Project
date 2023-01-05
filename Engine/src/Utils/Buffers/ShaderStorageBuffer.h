#pragma once

#define UR_CONTENT_API
#include "Engine.h"

namespace Uranium {
	class ShaderStorageBuffer {
	private:
		uint32 ssbo;

	public:
		ShaderStorageBuffer(uint32 _accessFormat, uint32 _bindingOffset, uint32 _size, void* _data);
		~ShaderStorageBuffer();

		operator uint32() const;

		void bind() const;
		void unbind() const;

		void setData(uint32 _offset, uint32 _size, void* _data);
		void getData(uint32 _offset, uint32 _size, void* _data);

	};
}