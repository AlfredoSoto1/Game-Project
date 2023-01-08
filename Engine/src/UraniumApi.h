#pragma once

#ifdef _DEBUG

#include <iostream>

#define throw_error(condition, message) if(condition) {std::cout << "Error at File: " << __FILE__ << "\nin line: "<< __LINE__  << "\n" << message << std::endl; __debugbreak();}
#define compile_error(message) static_assert(false, message)
#define print_status(status) std::cout << status  << std::endl


#define GLEW_STATIC
#include <GL/glew.h>

static void clear_OpenGL_error() {
	while (glGetError() != GL_NO_ERROR);
}

static bool check_OpenGL_error() {
	bool hadError = false;
	while (GLenum error = glGetError()) {
		print_status("[OPENGL ERROR]: <" << error << ">");
		print_status("on file: " << __FILE__ << "\n At line: " << __LINE__);
		hadError = true;
	}
	return hadError;
}

#define clear_OpenGLError() clear_OpenGL_error()
#define check_OpenGLError() check_OpenGL_error()
//#define check_OpenGLError() if (check_OpenGL_error(__FILE__, __LINE__)) {__debugbreak();}

#else

#define throw_error(condition, message)
#define compile_error(message)
#define print_status(status)
#define check_OpenGLError()

#endif