#pragma once

namespace Uranium {

	class Image {
	private:
		int width;
		int height;
		int channels;

	public:
		Image();
		~Image();
	};
}