#pragma once

class CGameObj;
class CRenderer
{
	DECLARE_SINGLETON(CRenderer)

private:
	CRenderer();
	~CRenderer();

public:
	GLvoid Render_Object();

public:
	HRESULT Add_RenderObj(RENDER::ID eID, CGameObj* pObj);
	GLvoid Clear_Renderer();

private:
	list<CGameObj*> m_lstRenderObj[RENDER::END];
};

