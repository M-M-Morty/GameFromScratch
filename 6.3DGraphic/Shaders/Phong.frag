#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

out vec4 outColor;

uniform sampler2D uTexture;

struct DirectionalLight
{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};

//������������uniform
uniform vec3 uCameraPos;
uniform float uSpecPower;
uniform vec3 uAmbientLight;

// ƽ�й�
uniform DirectionalLight uDirLight;

void main()
{	
	//���淨��
	vec3 N=normalize(fragNormal);
	//���浽��Դ������
	vec3 L = normalize(-uDirLight.mDirection);
	//���浽�����������
	vec3 V=normalize(uCameraPos-fragWorldPos);
	//������������ķ�������
	vec3 R=normalize(reflect(-L,N));

	//����phong����
	vec3 Phong=uAmbientLight;
	float NdotL=dot(N,L);
	if(NdotL>0)
	{
		vec3 Diffuse=uDirLight.mDiffuseColor*NdotL;
		vec3 Specular=uDirLight.mSpecColor*pow(max(0.0,dot(R,V)),uSpecPower);
		Phong+=Diffuse+Specular;
	}

	outColor=texture(uTexture,fragTexCoord)*vec4(Phong,1.0f);
}