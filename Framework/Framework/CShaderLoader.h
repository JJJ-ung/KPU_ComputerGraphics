#pragma once

class CShaderLoader
{
	DECLARE_SINGLETON(CShaderLoader)

private:
	CShaderLoader();
	~CShaderLoader();

public:
	HRESULT Initialize_Shader(string strVertex, string strPixel);

private:
	char* FileToBuf(const char* file);
	HRESULT Create_VertexShader(string strVertexShader);
	HRESULT Create_PixelShader(string strPixelShader);

public:
	GLuint s_program;
	GLchar* vertexsource, * fragmentsource; // �ҽ��ڵ� ���� ����
	GLuint vertexshader, fragmentshader; // ���̴� ��ü
};

