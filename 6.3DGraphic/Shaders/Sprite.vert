#version 330 

uniform mat4 uWorldtransform;
uniform mat4 uViewProj;

//����Ķ������ԣ�ͨ������ָ�룩
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location=2) in vec2 inTexCoord;

//����Ķ�������
out vec2 fragTexCoord;

void main()
{
	//ת��Ϊ�������
	vec4 pos=vec4(inPosition,1.0);
	gl_Position=pos*uWorldtransform*uViewProj;

	fragTexCoord=inTexCoord;
}
