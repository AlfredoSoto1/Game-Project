//#shader fragment
//#version 460 core
#version 330 core

layout(location = 0) out vec4 color;

in vec4 pass_color;
in vec2 pass_position;

uniform vec4 u_Color;

uniform sampler2D albedo;

void main(void) {
	
	vec4 textColor = texture(albedo, pass_position);

	color = pass_color;

//	color = textColor;

//	color = u_Color;
}
