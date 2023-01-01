#define GLEW_STATIC
#include <GL/glew.h>

#include "Renderer.h"
#include "Shader/ShaderProgram.h"
#include "Utils/Buffers/VertexArray.h"

using namespace Render;
using namespace Graphics;
using namespace BufferUtils;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::dispose() {

}

void Renderer::render(const VertexArray& _vao, const ShaderProgram& _shader) {
	// binds Shader before using it
	_shader.bind();

	_vao.bind();
	_vao.enableAttribs();

	glEnable(GL_DEPTH_TEST);

	glDrawElements(GL_TRIANGLES, _vao.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	glDisable(GL_DEPTH_TEST);

	_vao.disableAttribs();
	_vao.unbind();

	_shader.unbind();
}