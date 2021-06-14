#pragma once
#include "CScene.h"

class CScene18 : public CScene
{
public:
	CScene18();
	~CScene18();

public:
	HRESULT Initialize();
	GLuint Update();
	GLvoid Render();

public:
	GLvoid Input_Mouse(int button, int state, int x, int y);
	GLvoid Input_KeyBoard(unsigned char key, int x, int y);

public:
	GLvoid Release();
	static CScene18* Create();
};

