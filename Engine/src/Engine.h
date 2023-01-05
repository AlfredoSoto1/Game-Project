#pragma once

#ifdef UR_OPENGL
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#ifdef UR_CONTENT_API

#define UR_APIT extern

#define UR_link			friend class
#define UR_prototype	class
#define UR_namespace	namespace

typedef int Sampler2D;
typedef int Uniform;

typedef const char* const_string;

//typedef void* Data;
//typedef char  Byte;
//typedef char* Bytes;

#include <cstdint>

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#endif







