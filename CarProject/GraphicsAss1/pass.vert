#version 330

uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProj;

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 color;

out vec4 colorV;

void main()
{
	gl_Position = vProj * vView * vModel * vec4(vPosition, 1.0);

	colorV = color;
	
	//gl_Position = vec4(vPosition, 1.0);
}