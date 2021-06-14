#include "stdafx.h"
#include "CScene_Select.h"

#include "CLogo.h"
#include "CSprite.h"
#include "CBackImage.h"

CScene_Select::CScene_Select()
{
}

CScene_Select::~CScene_Select()
{
	Release();
}

HRESULT CScene_Select::Initialize()
{
	CScene::Initialize();

	CGameObj* pObj = nullptr;

	pObj = CBackImage::Create("Select_Back", "../Bin/Resources/Sprite/PlayerIcon/Select.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	//pObj = CLogo::Create(vec3(640.f, 550.f, 0.f), vec3(0.6f), "Logo", "../Bin/Resources/Sprite/Logo/Logo.png");
	//if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
	//	return E_FAIL;

	//pObj = CSprite::Create(vec3(640.f, 230.f, 0.f), vec3(1.f), "Press", "../Bin/Resources/Sprite/Logo/PressEnter.png");
	//if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
	//	return E_FAIL;

	return NOERROR;
}

GLint CScene_Select::Update(const GLfloat fTimeDelta)
{
	m_pGameMgr->Update(fTimeDelta);

	return GLint();
}

GLvoid CScene_Select::Render()
{
	m_pRenderer->Render_Object();

	return GLvoid();
}

GLvoid CScene_Select::Release()
{
	m_pGameMgr->Clear_ObjList();
}

CScene_Select* CScene_Select::Create()
{
	CScene_Select* pInstance = new CScene_Select;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
