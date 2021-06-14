#pragma once
#include "CScene.h"
#include "CPlanet15.h"

class CMesh;
class CScene15 : public CScene
{
public:
	CScene15();
	~CScene15();

public:
	HRESULT Initialize();
	GLuint Update();
	GLvoid Render();

public:
	GLvoid Input_Mouse(int button, int state, int x, int y);
	GLvoid Input_KeyBoard(unsigned char key, int x, int y);

private:
	CMesh* m_pMain;
	CPlanet15* m_pPlanet[3];

public:
	GLvoid Release();
	static CScene15* Create();
};

