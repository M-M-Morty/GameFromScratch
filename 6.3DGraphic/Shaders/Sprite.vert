#version 330 

uniform mat4 uWorldtransform;
uniform mat4 uViewProj;

//输入的顶点属性（通过属性指针）
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location=2) in vec2 inTexCoord;

//输出的顶点属性
out vec2 fragTexCoord;

void main()
{
	//转化为齐次坐标
	vec4 pos=vec4(inPosition,1.0);
	gl_Position=pos*uWorldtransform*uViewProj;

	fragTexCoord=inTexCoord;
}
