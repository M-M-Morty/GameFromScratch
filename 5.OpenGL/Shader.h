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