#include "Shader.h"
#include <SDL/SDL.h>
#include <fstream>
#include <sstream>

Shader::Shader()
    : mShaderProgram(0)
    , mVertexShader(0)
    , mFragShader(0)
{
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
    if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) ||
        !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
    {
        return false;
    }
    //创建shader程序，并链接相关shader
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragShader);
    glLinkProgram(mShaderProgram);

    // 验证程序是否链接成功
    if (!IsValidProgram())
    {
        return false;
    }

    return true;
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
    //根据uniform变量名找到该变量
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    //将矩阵数据传输给该uniform
    glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

void Shader::SetMatrixUniforms(const char* name, Matrix4* matrices, unsigned count)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    // Send the matrix data to the uniform
    glUniformMatrix4fv(loc, count, GL_TRUE, matrices->GetAsFloatPtr());
}

void Shader::SetVectorUniform(const char* name, const Vector3& vector)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    glUniform3fv(loc, 1, vector.GetAsFloatPtr());
}

void Shader::SetVector2Uniform(const char* name, const Vector2& vector)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    glUniform2fv(loc, 1, vector.GetAsFloatPtr());
}

void Shader::SetFloatUniform(const char* name, float value)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    glUniform1f(loc, value);
}

void Shader::SetIntUniform(const char* name, int value)
{
}

void Shader::SetActive()
{
    glUseProgram(mShaderProgram);
}

void Shader::Unload()
{
    glDeleteProgram(mShaderProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}


bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
    std::ifstream shaderFlie(fileName);
    if (shaderFlie.is_open())
    {
        std::stringstream sstream;
        sstream << shaderFlie.rdbuf();
        std::string contents = sstream.str();
        const char* contentsChar = contents.c_str();

        // 创建特定类型的shader
        outShader = glCreateShader(shaderType);
        // 设置shader源文件并尝试编译
        glShaderSource(outShader, 1, &(contentsChar), nullptr);
        glCompileShader(outShader);

        if (!IsCompiled(outShader))
        {
            SDL_Log("Failed to compile shader %s", fileName.c_str());
            return false;
        }
    }
    else
    {
       SDL_Log("Shader file not found: %s", fileName.c_str());
        return false;
    }
    return true;
}

bool Shader::IsCompiled(GLuint shader)
{
    GLint status;
    // 查询着色器编译状态
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL Compile Failed:\n%s", buffer);
        return false;
    }

    return true;
}

bool Shader::IsValidProgram()
{
    GLint status;
    // 查询链接状态
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
        SDL_Log("GLSL Link Status:\n%s", buffer);
        return false;
    }

    return true;
}
