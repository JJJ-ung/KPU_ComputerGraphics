#include "stdafx.h"
#include "CScene_Logo.h"

#include "CLogo.h"
#include "CSprite.h"
#include "CBackImage.h"

CScene_Logo::CScene_Logo()
{
}

CScene_Logo::~CScene_Logo()
{
	Release();
}

HRESULT CScene_Logo::Initialize()
{
	CScene::Initialize();

	CGameObj* pObj = nullptr;

	pObj = CBackImage::Create("Loading_Back", "../Bin/Resources/Sprite/Loading/Loading_Back.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	pObj = CLogo::Create(vec3(640.f, 500.f, 0.f), vec3(0.6f), "Logo", "../Bin/Resources/Sprite/Logo/Logo.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	pObj = CSprite::Create(vec3(640.f, 230.f, 0.f), vec3(1.f), "Press", "../Bin/Resources/Sprite/Logo/PressEnter.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	m_pSoundManager->Play_BGM(L"Welcome Horizons.mp3");

	return NOERROR;
}

GLint CScene_Logo::Update(const GLfloat fTimeDelta)
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_pSceneMgr->SceneChange(SCENE::INGAME);
		return OBJ_NOEVENT;
	}

	m_pGameMgr->Update(fTimeDelta);

	return GLint();
}

GLvoid CScene_Logo::Render()
{
	m_pRenderer->Render_Object();

	return GLvoid();
}

GLvoid CScene_Logo::Release()
{
	m_pGameMgr->Clear_ObjList();
}

CScene_Logo* CScene_Logo::Create()
{
	CScene_Logo* pInstance = new CScene_Logo;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
