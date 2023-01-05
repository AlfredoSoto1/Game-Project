#define GLEW_STATIC
#include <GL/glew.h>

#include "Texture.h"
#include "stb_image.h"

using namespace Graphics;

Texture::Texture(const char* _path)
	: width(0), height(0), channels(0), localImageData(nullptr)
{
	stbi_set_flip_vertically_on_load(1);

	localImageData = stbi_load(_path, &width, &height, &channels, 4);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localImageData);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localImageData != nullptr)
		stbi_image_free(localImageData);

}

Texture::~Texture() {
	glDeleteTextures(1, &texture);
}

void Texture::bind(unsigned int _slot) const {
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}