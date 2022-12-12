#version 330
//�Ӷ�����ɫ����õ�����
in vec2 fragTexCoord; //��������
in vec3 fragNormal;//���ߣ�����ռ䣩
in vec3 fragWorldPos��//λ�ã�����ռ䣩

//�����֡��������
layout(location=0) out vec3 outDiffuse;
layout(location=1) out vec3 outNormal;
layout(location=2) out vec3 outWorldPos;

uniform sampler2D uTexture;

void main()
{
	//����ͼ������ȡ��������ɫ
	outDiffuse=texture(uTexture,fragTexCoord).xyz;
	//ֱ�ӽ�λ��/�������
	outNormal=fragNormal;
	outWorldPos=fragWorldPos;
}