
//OpenGL3.3版本对应的GLSL版本
#version 330

in vec3 inPosition;

void main()
{
	gl_Position=vec4(inPosition,1.0);
}