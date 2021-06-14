#version 330 core

in vec3 vPosition;
in vec3 vColor;

out vec3 out_Color;

uniform mat4 matWorld = mat4(1.f);
uniform mat4 matView = mat4(1.f);
uniform mat4 matProj = mat4(1.f);

void main(void)
{
	gl_Position = matProj * matView * matWorld * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0) ;
	out_Color = vColor;
}