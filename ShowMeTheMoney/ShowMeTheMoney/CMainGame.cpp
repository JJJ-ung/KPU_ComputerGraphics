#include "stdafx.h"
#include "CMainGame.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
}

HRESULT CMainGame::Initialize()
{
	if(FAILED(Initialize_Manager()))
		return E_FAIL;
	if (FAILED(Initialize_Shader()))
		return E_FAIL;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_pSoundManager->Ready_SoundManager();
	m_pSoundManager->Load_SoundFile("..\\Bin\\Resources\\Sound\\");

	m_pSceneMgr->SceneChange(SCENE::LOGO);

	return NOERROR;
}

GLint CMainGame::Update()
{
	GLfloat fTimeDelta = m_pTimeMgr->Get_Delta();

	m_pSceneMgr->Update(fTimeDelta);

	return GLint();
}

GLvoid CMainGame::Render()
{
	m_pSceneMgr->Render();

	return GLvoid();
}

HRESULT CMainGame::Initialize_Manager()
{
	m_pGameMgr = CGameManager::GetInstance();
	if (!m_pGameMgr)
		return E_FAIL;
	m_pRenderer = CRenderer::GetInstance();
	if (!m_pRenderer)
		return E_FAIL;
	m_pSceneMgr = CSceneManager::GetInstance();
	if (!m_pSceneMgr)
		return E_FAIL;
	m_pKeyMgr = CKeyManager::GetInstance();
	if (!m_pKeyMgr)
		return E_FAIL;
	m_pTimeMgr = CTimeManager::GetInstance();
	if (!m_pTimeMgr)
		return E_FAIL;
	m_pShaderLoader = CShaderLoader::GetInstance();
	if (!m_pShaderLoader)
		return E_FAIL;
	m_pSoundManager = CSoundManager::GetInstance();
	if (!m_pSoundManager)
		return E_FAIL;

	return NOERROR;
}

HRESULT CMainGame::Initialize_Shader()
{
	if (FAILED(m_pShaderLoader->Add_Shader("Default", "../Bin/Shader/Vertex_Default.glsl", "../Bin/Shader/Pixel_Default.glsl")))
		return E_FAIL;
	if (FAILED(m_pShaderLoader->Add_Shader("Back", "../Bin/Shader/Vertex_BackImage.glsl", "../Bin/Shader/Pixel_BackImage.glsl")))
		return E_FAIL;
	if (FAILED(m_pShaderLoader->Add_Shader("UI", "../Bin/Shader/Vertex_UI.glsl", "../Bin/Shader/Pixel_UI.glsl")))
		return E_FAIL;
	if (FAILED(m_pShaderLoader->Add_Shader("Platform", "../Bin/Shader/Vertex_Platform.glsl", "../Bin/Shader/Pixel_Platform.glsl")))
		return E_FAIL;

	return NOERROR;
}

GLvoid CMainGame::Release()
{
	return GLvoid();
}

CMainGame* CMainGame::Create()
{
	CMainGame* pInstance = new CMainGame;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
