#version 330
//从顶点着色器获得的输入
in vec2 fragTexCoord; //纹理坐标
in vec3 fragNormal;//法线（世界空间）
in vec3 fragWorldPos；//位置（世界空间）

//输出到帧缓冲区上
layout(location=0) out vec3 outDiffuse;
layout(location=1) out vec3 outNormal;
layout(location=2) out vec3 outWorldPos;

uniform sampler2D uTexture;

void main()
{
	//从贴图采样获取漫反射颜色
	outDiffuse=texture(uTexture,fragTexCoord).xyz;
	//直接将位置/法线输出
	outNormal=fragNormal;
	outWorldPos=fragWorldPos;
}