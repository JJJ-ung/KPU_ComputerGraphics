#include "stdafx.h"
#include "CRenderer.h"
#include "CGameObj.h"

IMPLEMENT_SINGLETON(CRenderer)

CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
}

GLvoid CRenderer::Render_Object()
{
	for (int i = 0; i < RENDER::END; ++i)
	{
		if (i == RENDER::BACK)
			glDisable(GL_DEPTH_TEST);
		if (i == RENDER::UI)
			glDisable(GL_DEPTH_TEST);

		for (auto pObj : m_lstRenderObj[i])
			pObj->Render();

		glEnable(GL_DEPTH_TEST);
	}

	Clear_Renderer();
}

HRESULT CRenderer::Add_RenderObj(RENDER::ID eID, CGameObj* pObj)
{
	if (!pObj)
		return E_FAIL;

	m_lstRenderObj[eID].emplace_back(pObj);

	return NOERROR;
}

GLvoid CRenderer::Clear_Renderer()
{
	for (int i = 0; i < RENDER::END; ++i)
		m_lstRenderObj[i].clear();
}
