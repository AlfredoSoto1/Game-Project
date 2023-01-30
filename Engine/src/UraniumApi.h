#pragma once

#ifdef _DEBUG

#include <iostream>

#define throw_error(condition, message) if(condition) {std::cout << "Error at File: " << __FILE__ << "\nin line: "<< __LINE__  << "\n" << message << std::endl; __debugbreak();}
#define compile_error(message) static_assert(false, message)
#define print_status(status) std::cout << status  << std::endl

#define print_warning(condition, message) if(condition) std::cout << message << std::endl

#ifdef CATCH_OPENGL_ERROR

static void removePreviousErrors() {
	while (glGetError() != GL_NO_ERROR);
}

static bool printGLIfAnyError() {
	bool hadError = false;
	while (GLenum error = glGetError()) {
		print_status("[OPENGL ERROR]: <" << error << ">");
		print_status("on file: " << __FILE__ << "\n At line: " << __LINE__);
		hadError = true;
	}
	return hadError;
}

#define clearGLErrors() removePreviousErrors()
#define throw_GL_Errors() if (printGLIfAnyError()) {__debugbreak();}

#else
#define clearGLErrors()
#define throw_GL_Errors()
#endif

#else

#define throw_error(condition, message)
#define compile_error(message)
#define print_status(status)

#define print_warning(condition, message)

#define clearGLErrors()
#define throw_GL_Errors()

#endif

typedef int Sampler;
typedef int Uniform;

#define interface class

#define extends public
#define implements public

#define abstract virtual

#define declare_class class

#define link_class friend class

