#pragma once

#include <string>
#include <GL/glew.h>
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	//�����ļ���������ɫ��
	bool Load(const std::string& vertName, const std::string& fragName);

	void SetMatrixUniform(const char* name, const Matrix4& matrix);
	// Sets an array of matrix uniforms
	void SetMatrixUniforms(const char* name, Matrix4* matrices, unsigned count);
	void SetVectorUniform(const char* name, const Vector3& vector);
	void SetVector2Uniform(const char* name, const Vector2& vector);
	void SetFloatUniform(const char* name, float value);
	void SetIntUniform(const char* name, int value);
	//������ɫ����
	void SetActive();

	void Unload();

private:
	// ���Ա���������
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	// ����Ƿ����ɹ�
	bool IsCompiled(GLuint shader);
	//���Գ����Ƿ����ӳɹ�
	bool IsValidProgram();
private:
	// �洢��ɫ����Ӧ��
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;

};