//#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 pass_color;

void main(void) {
	
	color = pass_color;
}
