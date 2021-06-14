#include "stdafx.h"
#include "CPlayer.h"

#include "CMesh.h"
#include "CTransform.h"
#include "CCamera.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Initialize(GLint iIndex)
{
	CGameObj::Initialize();
	CMesh* pMesh = nullptr;

	if(iIndex == 0)
		pMesh = CMesh::Create("../Bin/Resources/Player/1Ho/1Ho.obj");
	if(iIndex == 1)
		pMesh = CMesh::Create("../Bin/Resources/Player/KK/KK.obj");

	m_pTransform = CTransform::Create();

	if (iIndex == 0)
	{
		m_pTransform->Get_Scale() = vec3(0.02f);
		m_pTransform->Get_Position() = vec3(-0.2f, 0.f, 0.2f);
	}
	if (iIndex == 1)
	{
		m_pTransform->Get_Scale() = vec3(0.02f);
		m_pTransform->Get_Position() = vec3(0.2f, 0.f, 0.2f);
	}

	m_iIndex = iIndex;

	if (FAILED(Add_Component(COMPONENT::BUFFER, pMesh)))
		return E_FAIL;
	if (FAILED(Add_Component(COMPONENT::UPDATE, m_pTransform)))
		return E_FAIL;

	return NOERROR;
}

GLint CPlayer::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_CurrTurn() == m_iIndex)
	{
		if (m_pGameMgr->Get_GameState() == GAME::SELECT)
		{
			if (m_pKeyMgr->KeyDown(KEY_LB))
				Select_Platform();
		}

		if (m_pGameMgr->Get_GameState() == GAME::ANIMATION)
		{
			m_fTime += fTimeDelta;
			bool bCheck = m_pGameMgr->Play_MoneyAnimation(fTimeDelta, m_iIndex);
			if (bCheck && m_fTime > 1.f)
			{
				m_fTime = 0.f;
				m_pGameMgr->Progress_State();
			}
		}
	}

	CGameObj::Update_Component(fTimeDelta);

	m_pRenderer->Add_RenderObj(RENDER::NONALPHA, this);

	return GLint(OBJ_NOEVENT);
}

GLvoid CPlayer::Render()
{
	m_pShaderLoader->Use_Shader("Platform");
	m_pGameMgr->Render_Camera();

	CGameObj::Render_Component();

	return GLvoid();
}

GLvoid CPlayer::Select_Platform()
{
	if (m_pGameMgr->Get_CurrTurn() != m_iIndex
		&& m_pGameMgr->Get_GameState() != GAME::SELECT)
		return;

	for (int i = 0; i < 9; ++i)
	{
		if (Check_Selection(i))
		{
			m_pTransform->Get_Position() = m_pGameMgr->Get_PlatformPos((PLATFORM::TYPE)i) 
				+ vec3(0.2f, 0.f, 0.f) * (m_iIndex * 2 - 1) + vec3(0.f, 0.f, 0.2f);
			m_pGameMgr->Progress_State();
			return;
		}
	}
}

bool CPlayer::Check_Selection(int iIndex)
{
	if (m_pGameMgr->Get_GameState() != GAME::SELECT)
		return false;

	float fCheck = 80.f;
	vec2 vPoint = vec2(0.f);
	vec2 vMouse = m_pKeyMgr->Get_Mouse();

	if (iIndex == 0)
	{
		vPoint = vec2(360.f, 284.f);
		fCheck = 80.f;
	}
	if (iIndex == 1)
	{
		vPoint = vec2(514.f, 199.f);
		fCheck = 65.f;
	}
	if (iIndex == 2)
	{
		vPoint = vec2(644.f, 135.f);
		fCheck = 60.f;
	}
	if (iIndex == 3)
	{
		vPoint = vec2(483.f, 385.f);
		fCheck = 90.f;
	}
	if (iIndex == 4)
	{
		fCheck = -10.f;
		vPoint = vec2(639.f, 281.f);
	}
	if (iIndex == 5)
	{
		vPoint = vec2(766.f, 201.f);
		fCheck = 65.f;
	}
	if (iIndex == 6)
	{
		fCheck = 125.f;
		vPoint = vec2(640.f, 513.f);
	}
	if (iIndex == 7)
	{
		vPoint = vec2(800.f, 383.f);
		fCheck = 90.f;
	}
	if (iIndex == 8)
	{
		vPoint = vec2(921.f, 281.f);
		fCheck = 80.f;
	}

	vec2 vDist = vMouse - vPoint;
	float fDist = sqrt(pow(vDist.x, 2) + pow(vDist.y, 2));

	if (fDist < fCheck)
		return true;

	return false;
}

GLvoid CPlayer::Release()
{
	CGameObj::Release();
}

CPlayer* CPlayer::Create(GLint iIndex)
{
	CPlayer* pInstance = new CPlayer;

	if (FAILED(pInstance->Initialize(iIndex)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
