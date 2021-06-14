#include "stdafx.h"
#include "CBackImage.h"

#include "CPlane.h"
#include "CTexture.h"

CBackImage::CBackImage()
{
}

CBackImage::~CBackImage()
{
}

HRESULT CBackImage::Initialize(string strTexTag, string strTexPath, bool bAlpha)
{
	CGameObj::Initialize();

	CTexture* pTexture = CTexture::Create(strTexTag, strTexPath, bAlpha);
	if(FAILED(Add_Component(COMPONENT::TEXTURE, pTexture)))
		return E_FAIL;

	CPlane* pPlane = CPlane::Create();
	if (FAILED(Add_Component(COMPONENT::BUFFER, pPlane)))
		return E_FAIL;

	return NOERROR;
}

GLint CBackImage::Update(const GLfloat fTimeDelta)
{
	CGameObj::Update_Component(fTimeDelta);

	m_pRenderer->Add_RenderObj(RENDER::BACK, this);

	return GLint();
}

GLvoid CBackImage::Render()
{
	m_pShaderLoader->Use_Shader("Back");

	CGameObj::Render_Component();
}

GLvoid CBackImage::Release()
{
	return GLvoid();
}

CBackImage* CBackImage::Create(string strTexTag, string strTexPath, bool bAlpha)
{
	CBackImage* pInstance = new CBackImage;

	if (FAILED(pInstance->Initialize(strTexTag, strTexPath, bAlpha)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
