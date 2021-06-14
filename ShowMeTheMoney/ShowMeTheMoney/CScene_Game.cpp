#include "stdafx.h"
#include "CScene_Game.h"

#include "CLogo.h"
#include "CSprite.h"
#include "CBackImage.h"

#include "CCamera.h"
#include "CPlatform.h"
#include "CPlayer.h"
#include "CRullet.h"

#include "CNumber.h"

CScene_Game::CScene_Game()
{
}

CScene_Game::~CScene_Game()
{
	Release();
}

HRESULT CScene_Game::Initialize()
{
	CScene::Initialize();

	m_pGameMgr->Add_Camera(CCamera::Create());

	CGameObj* pObj = nullptr;

	pObj = CBackImage::Create("Loading_Back", "../Bin/Resources/Sprite/UI/BackGround.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	for (int i = 0; i < PLATFORM::END; ++i)
	{
		pObj = CPlatform::Create((PLATFORM::TYPE)i);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ::MAP, pObj)))
			return E_FAIL;
	}

	pObj = CPlayer::Create(0);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::PLAYER1, pObj)))
		return E_FAIL;

	pObj = CPlayer::Create(1);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::PLAYER2, pObj)))
		return E_FAIL;

	pObj = CRullet::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::RULLET, pObj)))
		return E_FAIL;

	//pObj = CSprite::Create(vec3(640.f, 645.f, 0.f), vec3(0.8f), "Selection", "../Bin/Resources/Sprite/Rullet/Selection.png");
	pObj = CSprite::Create(vec3(640.f, 385.f, 0.f), vec3(0.5f), "Selection", "../Bin/Resources/Sprite/Rullet/Selection.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::RULLET, pObj))) // OBJ SELECTON && RULLET 추가함 SELECTION PNG 추가함
		return E_FAIL;

	pObj = CSprite::Create(vec3(160.f, 645.f, 0.f), vec3(0.65f), "UI1", "../Bin/Resources/Sprite/UI/PlayerInfo0.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	pObj = CSprite::Create(vec3(1100.f, 55.f, 0.f), vec3(0.65f), "UI2", "../Bin/Resources/Sprite/UI/PlayerInfo1.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	pObj = CNumber::Create(0);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	pObj = CNumber::Create(1);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj)))
		return E_FAIL;

	pObj = CSprite::Create(vec3(640.f, 645.f, 0.f), vec3(0.8f), "Selection", "../Bin/Resources/Sprite/PlayerIcon/SelectText0.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI1, pObj))) // OBJ SELECTON && RULLET 추가함 SELECTION PNG 추가함
		return E_FAIL;

	pObj = CSprite::Create(vec3(640.f, 645.f, 0.f), vec3(0.8f), "Selection", "../Bin/Resources/Sprite/PlayerIcon/SelectText1.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI2, pObj))) // OBJ SELECTON && RULLET 추가함 SELECTION PNG 추가함
		return E_FAIL;

	pObj = CSprite::Create(vec3(55.f, 720.f - 75.f, 0.f), vec3(0.7f), "Selection", "../Bin/Resources/Sprite/PlayerIcon/Player0.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj))) // OBJ SELECTON && RULLET 추가함 SELECTION PNG 추가함
		return E_FAIL;

	pObj = CSprite::Create(vec3(997.f, 720.f - 667.f, 0.f), vec3(0.7f), "Selection", "../Bin/Resources/Sprite/PlayerIcon/Player2.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ::UI, pObj))) // OBJ SELECTON && RULLET 추가함 SELECTION PNG 추가함
		return E_FAIL;

	m_pSoundManager->Stop_All();
	m_pSoundManager->Play_BGM(L"Resident Services Tent.mp3");

	return NOERROR;
}

GLint CScene_Game::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_Winner() >= 0)
	{
		m_fTime += fTimeDelta * 2.f;
		if (m_fTime >= 2.f)
			m_bSceneChange = true;
	}

	m_pGameMgr->Update(fTimeDelta);

	return GLint();
}

GLvoid CScene_Game::Render()
{
	m_pRenderer->Render_Object();

	if (m_bSceneChange)
		m_pSceneMgr->SceneChange(SCENE::RESULT);

	return GLvoid();
}

GLvoid CScene_Game::Release()
{
	m_pGameMgr->Clear_ObjList();
}

CScene_Game* CScene_Game::Create()
{
	CScene_Game* pInstance = new CScene_Game;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
