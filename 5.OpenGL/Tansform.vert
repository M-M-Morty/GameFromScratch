

#version 330 

uniform mat4 uWorldtransform;
uniform mat4 uViewProj;

//∂•µ„ Ù–‘
in vec3 inPosition;

void main()
{
	vec4 pos=vec4(inPosition,1.0);
	gl_Position=pos*uWorldtransform*uViewProj;
}
