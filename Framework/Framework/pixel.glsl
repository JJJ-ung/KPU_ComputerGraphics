#version 330 core

in vec3 out_Color;

out vec4 out_FragColor;

void main(void)
{
	out_FragColor = vec4(out_Color,1.0);
}