#pragma once

namespace Uranium {
	class ShaderStorageBuffer {
	private:
		unsigned int ssbo;

	public:
		ShaderStorageBuffer(unsigned int _accessFormat, unsigned int _bindingOffset, unsigned int _size, void* _data);
		~ShaderStorageBuffer();

		operator unsigned int() const;

		void bind() const;
		void unbind() const;

		void setData(unsigned int _offset, unsigned int _size, void* _data);
		void getData(unsigned int _offset, unsigned int _size, void* _data);

	};
}