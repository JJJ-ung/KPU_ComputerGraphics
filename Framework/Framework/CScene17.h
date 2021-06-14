#pragma once
#include "CScene.h"

class CShape;
class CObject17;
class CScene17 : public CScene
{
public:
	CScene17();
	~CScene17();

public:
	HRESULT Initialize();
	GLuint Update();
	GLvoid Render();

public:
	GLvoid Input_Mouse(int button, int state, int x, int y);
	GLvoid Input_KeyBoard(unsigned char key, int x, int y);

private:
	CShape* m_pTerrain;
	CObject17* m_pObject;

private:
	bool m_bRot = false;
	vec3 m_vCameraOffset = vec3(0.f);

public:
	GLvoid Release();
	static CScene17* Create();
};

