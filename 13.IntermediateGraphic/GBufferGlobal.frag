#version 330

//�Ӷ�����ɫ����õ����루�������꣩
in vec2 fragTexCoord;

//�������ɫ������
layout(location=0) out vec4 outColor;

//��G��������ȡ����ͼ
uniform sampler2D uGDiffuse;
uniform sampler2D uGNormal;
uniform sampler2D uGWorldPos;

//Ϊƽ�йⴴ���Ľṹ��
struct DirectionalLight
{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
}

//���λ��
uniform vec3 uCameraPos;
//����������
uniform vec3 uAmbientLight;
//ƽ�й�
uniform DirectionalLight uDirLight;

void main()
{
	vec3 gbufferDiffuse=texture(uGDiffuse,fragTexCoord).xyz;
	vec3 gbufferNorm = texture(uGNormal, fragTexCoord).xyz;
	vec3 gbufferWorldPos = texture(uGWorldPos, fragTexCoord).xyz;

	//���淨��
	vec3 N=normalize(gbufferNorm);
	//���浽��Դ������
	vec3 L=normalize(-uDirLight.mDirection);
	//���浽�����������
	vec3 V=normalize(uCameraPos-gbufferWorldPos);
	//���㷴���������
	vec3 R=normalize(reflect(-L,N));

	//����phong����
	vec3 Phong=uAmbientLight;
	float NdotL=dot(N, L);
	if(NdotL>0)
	{
		vec3 Diffuse=uDirLight.mDiffuseColor*dot(N, L);
		Phong += Diffuse;
	}
	Phong = clamp(Phong, 0.0, 1.0);

	//������ɫ���Ϊ��ͼ��ɫ����phong����
	outColor = vec4(gbufferDiffuse * Phong, 1.0);
}