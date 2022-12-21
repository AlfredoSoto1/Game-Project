#pragma once

#ifndef _VERTEX_IMPL
#define _VERTEX_IMPL

#include "BufferUtils/Vertex.h"

#include <iostream>

using namespace std;
using namespace BufferUtils;

template<typename T>
void Vertex<T>::set(T type) {
	cout << "Printed" << endl;
}

#endif // !_VERTEX_IMPL

