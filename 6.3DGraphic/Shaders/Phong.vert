#version 330 

uniform mat4 uWorldtransform;
uniform mat4 uViewProj;

//输入的顶点属性（通过属性指针）
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location=2) in vec2 inTexCoord;

//输出的顶点属性
out vec2 fragTexCoord;
//法线（世界空间）
out vec3 fragNormal;
//位置（世界空间）
out vec3 fragWorldPos;

void main()
{
	//转化为齐次坐标
	vec4 pos=vec4(inPosition,1.0);
	pos=pos*uWorldtransform;
	fragWorldPos=pos.xyz;
	gl_Position=pos*uViewProj;
	//将法线转化为世界空间
	fragNormal = (vec4(inNormal, 0.0f) * uWorldtransform).xyz;

	fragTexCoord=inTexCoord;
}