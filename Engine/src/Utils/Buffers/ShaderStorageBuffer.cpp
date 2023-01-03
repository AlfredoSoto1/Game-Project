#define GLEW_STATIC
#include <GL/glew.h>

#include "ShaderStorageBuffer.h"

using namespace BufferUtils;

ShaderStorageBuffer::ShaderStorageBuffer(uint32_t _accessFormat, uint32_t _bindingOffset, uint32_t _size, void* _data) {
	glGenBuffers(1, &ssbo);
	bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, _size, _data, _accessFormat);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, _bindingOffset, ssbo);
	unbind();
}

ShaderStorageBuffer::~ShaderStorageBuffer() {
	glDeleteBuffers(1, &ssbo);
}

ShaderStorageBuffer::operator uint32_t() const {
	return ssbo;
}

void ShaderStorageBuffer::bind() const {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
}

void ShaderStorageBuffer::unbind() const {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderStorageBuffer::setData(uint32_t _offset, uint32_t _size, void* _data) {
	bind();
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, _offset, _size, _data);
	unbind();
}

void ShaderStorageBuffer::getData(uint32_t _offset, uint32_t _size, void* _data) {
	bind();
	glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, _offset, _size, _data);
	unbind();
}
