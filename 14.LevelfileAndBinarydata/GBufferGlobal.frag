#version 330

//从顶点着色器获得的输入（纹理坐标）
in vec2 fragTexCoord;

//输出到颜色缓冲区
layout(location=0) out vec4 outColor;

//从G缓冲区获取的贴图
uniform sampler2D uGDiffuse;
uniform sampler2D uGNormal;
uniform sampler2D uGWorldPos;

//为平行光创建的结构体
struct DirectionalLight
{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
}

//相机位置
uniform vec3 uCameraPos;
//环境光亮度
uniform vec3 uAmbientLight;
//平行光
uniform DirectionalLight uDirLight;

void main()
{
	vec3 gbufferDiffuse=texture(uGDiffuse,fragTexCoord).xyz;
	vec3 gbufferNorm = texture(uGNormal, fragTexCoord).xyz;
	vec3 gbufferWorldPos = texture(uGWorldPos, fragTexCoord).xyz;

	//表面法线
	vec3 N=normalize(gbufferNorm);
	//表面到光源的向量
	vec3 L=normalize(-uDirLight.mDirection);
	//表面到摄像机的向量
	vec3 V=normalize(uCameraPos-gbufferWorldPos);
	//计算反射光线向量
	vec3 R=normalize(reflect(-L,N));

	//计算phong反射
	vec3 Phong=uAmbientLight;
	float NdotL=dot(N, L);
	if(NdotL>0)
	{
		vec3 Diffuse=uDirLight.mDiffuseColor*dot(N, L);
		Phong += Diffuse;
	}
	Phong = clamp(Phong, 0.0, 1.0);

	//最终颜色输出为贴图颜色乘以phong光照
	outColor = vec4(gbufferDiffuse * Phong, 1.0);
}