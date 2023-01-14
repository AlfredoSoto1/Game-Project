#pragma once

namespace Uranium {

	class Texture {
	private:
		int width;
		int height;
		int channels;

		unsigned int texture;

		unsigned char* localImageData;

	public:
		Texture(const char* _path);
		~Texture();

		void bind(unsigned int _slot = 0) const;
		void unbind() const;

	};
}