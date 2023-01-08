//#shader vertex
#version 460 core
//#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 textCoord;

out vec4 pass_color;
out vec2 pass_position;

void main(void) {

	pass_color = color;
	
	pass_position = textCoord;

	gl_Position = vec4(position, 1.0);
}