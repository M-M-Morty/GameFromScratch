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

//计算光照所需的uniform
uniform vec3 uCameraPos;
uniform float uSpecPower;
uniform vec3 uAmbientLight;

// 平行光
uniform DirectionalLight uDirLight;

void main()
{	
	//表面法线
	vec3 N=normalize(fragNormal);
	//表面到光源的向量
	vec3 L = normalize(-uDirLight.mDirection);
	//表面到摄像机的向量
	vec3 V=normalize(uCameraPos-fragWorldPos);
	//计算光线向量的反射向量
	vec3 R=normalize(reflect(-L,N));

	//计算phong反射
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