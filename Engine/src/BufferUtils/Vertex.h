#pragma once

#ifndef _VERTEX
#define _VERTEX

namespace BufferUtils {

	template<typename T>
	class Vertex {
	private:

	public:
		void set(T type);
		
	};
}

#endif // !_VERTEX

#include "BufferUtils/implementation/Vertex_impl.h"