#include "stdafx.h"
#include "CScene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	Release();
}

HRESULT CScene::Initialize()
{
	return NOERROR;
}

GLuint CScene::Update()
{
	return GLuint();
}

GLvoid CScene::Render()
{
	return GLvoid();
}

GLvoid CScene::Input_Mouse(int button, int state, int x, int y)
{
	return GLvoid();
}

GLvoid CScene::Input_KeyBoard(unsigned char key, int x, int y)
{
	return GLvoid();
}

GLvoid CScene::Input_KeyBoardDir(int key, int x, int y)
{
	return GLvoid();
}

vec2 CScene::ScreenConvert(GLint x, GLint y)
{
	vec2 Output = {};
	Output.x = (x - g_iWinCX * 0.5f) / g_iWinCX * 0.5f;
	Output.y = ((g_iWinCY - y) - g_iWinCY * 0.5f) / g_iWinCY * 0.5f;

	return Output;
}

GLvoid CScene::Release()
{
	return GLvoid();
}
