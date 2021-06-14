#include "stdafx.h"
#include "CScene_Result.h"

#include "CBackImage.h"
#include "CResultMesh.h"

CScene_Result::CScene_Result()
{
}

CScene_Result::~CScene_Result()
{
	Release();
}

HRESULT CScene_Result::Initialize()
{
	CScene::Initialize();


	CGameObj* pObj = nullptr;

	if (m_pGameMgr->Get_Winner() == 0)
		pObj = CBackImage::Create("Loading_Back", "../Bin/Resources/Sprite/Loading/Win0.png", false);
	else if (m_pGameMgr->Get_Winner() == 1)
		pObj = CBackImage::Create("Loading_Back", "../Bin/Resources/Sprite/Loading/Win1.png", false);

	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	pObj = CResultMesh::Create(m_pGameMgr->Get_Winner());
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::MAP, pObj)))
		return E_FAIL;

	m_pSoundManager->Stop_All();
	m_pSoundManager->Play_BGM(L"Crafting Complete.mp3");

	return NOERROR;
}

GLint CScene_Result::Update(const GLfloat fTimeDelta)
{
	m_pGameMgr->Update(fTimeDelta);

	return GLint();
}

GLvoid CScene_Result::Render()
{
	m_pRenderer->Render_Object();

	return GLvoid();
}

GLvoid CScene_Result::Release()
{
	m_pGameMgr->Clear_ObjList();
}

CScene_Result* CScene_Result::Create()
{
	CScene_Result* pInstance = new CScene_Result;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
