#version 330 

uniform mat4 uWorldtransform;
uniform mat4 uViewProj;

//����Ķ������ԣ�ͨ������ָ�룩
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location=2) in vec2 inTexCoord;

//����Ķ�������
out vec2 fragTexCoord;
//���ߣ�����ռ䣩
out vec3 fragNormal;
//λ�ã�����ռ䣩
out vec3 fragWorldPos;

void main()
{
	//ת��Ϊ�������
	vec4 pos=vec4(inPosition,1.0);
	pos=pos*uWorldtransform;
	fragWorldPos=pos.xyz;
	gl_Position=pos*uViewProj;
	//������ת��Ϊ����ռ�
	fragNormal = (vec4(inNormal, 0.0f) * uWorldtransform).xyz;

	fragTexCoord=inTexCoord;
}