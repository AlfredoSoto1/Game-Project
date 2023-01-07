#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"

#include "ShaderStorageBuffer.h"
using namespace Uranium;

ShaderStorageBuffer::ShaderStorageBuffer(unsigned int _accessFormat, unsigned int _bindingOffset, unsigned int _size, void* _data) {
	glGenBuffers(1, &ssbo);
	bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, _size, _data, _accessFormat);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, _bindingOffset, ssbo);
	unbind();
}

ShaderStorageBuffer::~ShaderStorageBuffer() {
	glDeleteBuffers(1, &ssbo);
}

ShaderStorageBuffer::operator unsigned int() const {
	return ssbo;
}

void ShaderStorageBuffer::bind() const {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
}

void ShaderStorageBuffer::unbind() const {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderStorageBuffer::setData(unsigned int _offset, unsigned int _size, void* _data) {
	bind();
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, _offset, _size, _data);
	unbind();
}

void ShaderStorageBuffer::getData(unsigned int _offset, unsigned int _size, void* _data) {
	bind();
	glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, _offset, _size, _data);
	unbind();
}
