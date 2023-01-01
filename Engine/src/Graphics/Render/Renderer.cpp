#define GLEW_STATIC
#include <GL/glew.h>

#include "Renderer.h"
#include "Utils/Buffers/VertexArray.h"

using namespace Render;
using namespace BufferUtils;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::render(const VertexArray& _vao) {
	// binds Shader before using it
	//shader->bind();

	_vao.bind();
	_vao.enableAttribs();

	glEnable(GL_DEPTH_TEST);

	glDrawElements(GL_TRIANGLES, _vao.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	glDisable(GL_DEPTH_TEST);

	_vao.disableAttribs();
	_vao.unbind();

	//shader->unbind();
}