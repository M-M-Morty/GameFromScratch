#pragma once

#include <string>
#include <GL/glew.h>
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	//根据文件名加载着色器
	bool Load(const std::string& vertName, const std::string& fragName);

	void SetMatrixUniform(const char* name, const Matrix4& matrix);
	void SetVectorUniform(const char* name, const Vector3& vector);
	void SetFloatUniform(const char* name, float value);
	//激活着色程序
	void SetActive();

	void Unload();

private:
	// 尝试编译具体程序
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	// 检测是否编译成功
	bool IsCompiled(GLuint shader);
	//测试程序是否连接成功
	bool IsValidProgram();
private:
	// 存储着色器的应用
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;

};