#include "stdafx.h"
#include "CLogo.h"

#include "CPlane.h"
#include "CTexture.h"
#include "CTransform.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Initialize(vec3 vPos, vec3 vScale, string strTexTag, string strTexPath, bool bAlpha)
{
	CGameObj::Initialize();						// 게임 오브젝트 공통 이니셜라이즈 **필수**

	CPlane* pPlane = CPlane::Create();
	if (FAILED(Add_Component(COMPONENT::BUFFER, pPlane)))
		return E_FAIL;

	CTexture* pTexture = CTexture::Create(strTexTag, strTexPath, bAlpha);
	if (FAILED(Add_Component(COMPONENT::TEXTURE, pTexture)))
		return E_FAIL;

	m_pTransform = CTransform::Create();
	if (FAILED(Add_Component(COMPONENT::UPDATE, m_pTransform)))
		return E_FAIL;

	m_pTransform->Get_Position() = vPos;
	m_pTransform->Get_Scale() = vScale * vec3(pTexture->Get_Width() * 0.5f, pTexture->Get_Height() * 0.5f, 1.f);

	m_matProj = ortho(0.f, (float)WINCX, 0.f, (float)WINCY, 0.f, 100.0f);					// 직교투영하는것임

	m_matView = mat4(1.f);

	return NOERROR;
}

GLint CLogo::Update(const GLfloat fTimeDelta)
{
	m_pTransform->Get_Rotation().z += m_fAngle * fTimeDelta;
	if (m_pTransform->Get_Rotation().z > 10.f)
		m_fAngle *= -1.f;
	if (m_pTransform->Get_Rotation().z < -10.f)
		m_fAngle *= -1.f;

	CGameObj::Update_Component(fTimeDelta);					

	m_pRenderer->Add_RenderObj(RENDER::UI, this);						// ** 필수

	return GLint();
}

GLvoid CLogo::Render()
{
	GLuint program = m_pShaderLoader->Use_Shader("UI");
	int viewLoc = glGetUniformLocation(program, "matView");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));
	int ProjLoc = glGetUniformLocation(program, "matProj");
	glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

	CGameObj::Render_Component();

	return GLvoid();
}

GLvoid CLogo::Release()
{
	CGameObj::Release();
}

CLogo* CLogo::Create(vec3 vPos, vec3 vScale, string strTexTag, string strTexPath, bool bAlpha)
{
	CLogo* pInstance = new CLogo;

	if (FAILED(pInstance->Initialize(vPos, vScale, strTexTag, strTexPath, bAlpha)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
