#version 330

in vec2 fragTexCoord;

layout(location=0) out vec4 outColor;

uniform sampler2D uGDiffuse;
uniform sampler2D uGNormal;
uniform sampler2D uGWorldPos;

struct PointLight
{
	vec3 mWorldPos;
	vec3 mDiffuseColor;
	float mInnerRadius;
	float mOuterRadius;
};

uniform PointLight uPointLight;
//记录屏幕的宽/高
uniform vec2 uScreenDimensions;

void main()
{
	//计算正确的坐标去采样G-Buffer贴图
	vec2 gbufferCoord=gl_FragCoord.xy/uScreenDimensions;

	vec3 gbufferDiffuse=texture(uGDiffuse,gbufferCoord).xyz;
	vec3 gbufferNorm=texture(uGNormal,gbufferCoord).xyz;
	vec3 gbufferWorldPos=texture(uGWorldPos,gbufferCoord).xyz;

	vec3 N=normalize(gbufferNorm);
	vec3 L=normalize(uPointLight.mWorldPos-gbufferWorldPos);

	vec3 Phong=vec3(0.f,0.f,0.f);
	float NdotL=dot(N,L);
	if(NdotL>0)
	{
		//计算表面到点光源的距离
		float dist=distance(uPointLight.mWorldPos,gbufferWorldPos);
		//利用smoothstep函数计算强度，范围为[0,1]
		float intensity=smoothstep(uPointLight.mInnerRadius,
									uPointLight,mOuterRadius,dist);
		vec3 DiffuseColor=mix(uPointLight.mDiffuseColor,
								vec3(0.f,0.f,0.f),intensity);
		Phong=DiffuseColor*NdotL;
	}
	outColor=vec4(gbufferDiffuse*Phong,1.0);
}