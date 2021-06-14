#pragma once

class CShaderLoader
{
	DECLARE_SINGLETON(CShaderLoader)

private:
	CShaderLoader();
	~CShaderLoader();

public:
	HRESULT Add_Shader(string strTag, string strVertex, string strPixel);
	GLuint Use_Shader(string strTag);
	GLuint Get_CurrProgram();

private:
	GLuint m_iCurrProgram = -1;

private:
	char* FileToBuf(const char* file);
	HRESULT Create_VertexShader(SHADER* pShader, string strVertexShader);
	HRESULT Create_PixelShader(SHADER* pShader, string strPixelShader);

private:
	map<string, SHADER*> m_mapShader;
};
