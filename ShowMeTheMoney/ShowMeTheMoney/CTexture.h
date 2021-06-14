#pragma once
#include "CComponent.h"

class CTexture : public CComponent
{
public:
	CTexture();
	~CTexture();

public:
	const GLint Get_Width() { return m_iWidth; }
	const GLint Get_Height() { return m_iHeight; }

public:
	virtual HRESULT Initialize(string strTag, string strPath, bool bAlpha);
	virtual GLvoid Render();

private:
	GLuint m_iID;
	GLint m_iWidth;
	GLint m_iHeight;
	GLint m_iChannels;

private:
	GLvoid Release();

public:
	static CTexture* Create(string strTag, string strPath, bool bAlpha = true);
};

