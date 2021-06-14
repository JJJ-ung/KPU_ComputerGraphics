#include "stdafx.h"
#include "CGameManager.h"
#include "CGameObj.h"
#include "CSoundManager.h"

#include "CCamera.h"

IMPLEMENT_SINGLETON(CGameManager)

CGameManager::CGameManager()
{
	m_arrPlatformPos[PLATFORM::TREE] = vec3(-2.5f, 0.f, 0.f);
	m_arrPlatformPos[PLATFORM::DIY] = vec3(0.f, 0.f, -2.5f);
	m_arrPlatformPos[PLATFORM::FISH] = vec3(0.f, 0.f, 2.5f);
	m_arrPlatformPos[PLATFORM::FOSSIL] = vec3(1.25f, 0.f, 1.25f);
	m_arrPlatformPos[PLATFORM::GRASS] = vec3(-1.25f, 0.f, 1.25f);
	m_arrPlatformPos[PLATFORM::INSECT] = vec3(2.5f, 0.f, 0.f);
	m_arrPlatformPos[PLATFORM::STONE] = vec3(-1.25f, 0.f, -1.25f);
	m_arrPlatformPos[PLATFORM::FRUIT] = vec3(1.25f, 0.f, -1.25f);
	m_arrPlatformPos[PLATFORM::NPC] = vec3(0.f, 0.f, 0.f);
}

CGameManager::~CGameManager()
{
}

HRESULT CGameManager::Add_GameObj(OBJ::ID eID, CGameObj* pObj)
{
	if (!pObj)
		return E_FAIL;

	m_lstGameObj[eID].emplace_back(pObj);

	return NOERROR;
}

GLvoid CGameManager::Update(const GLfloat fTimeDelta)
{
	list<CGameObj*>::iterator iter_begin;
	list<CGameObj*>::iterator iter_end;

	for (int i = 0; i < OBJ::END; ++i)
	{
		iter_begin = m_lstGameObj[i].begin();
		iter_end = m_lstGameObj[i].end();

		if (m_eGameState == GAME::SELECT)
		{
			if (m_iCurrTurn == 0 && i == OBJ::UI2)
				continue;
			if (m_iCurrTurn == 1 && i == OBJ::UI1)
				continue;
		}
		else
		{
			if (i == OBJ::UI1 || i == OBJ::UI2)
				continue;
		}

		if (m_eGameState != GAME::RULLET && i == OBJ::RULLET)
			continue;

		for (; iter_begin != iter_end; )
		{
			int iEvent = (*iter_begin)->Update(fTimeDelta);

			if (OBJ_DEAD == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_lstGameObj[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}

	if(m_pCamera)
		m_pCamera->Update(fTimeDelta);

	return GLvoid();
}

HRESULT CGameManager::Clear_ObjList()
{
	for (int i = 0; i < OBJ::END; ++i)
		Clear_Obj((OBJ::ID)i);
	SafeDelete(m_pCamera);

	return NOERROR;
}

HRESULT CGameManager::Clear_Obj(OBJ::ID eID)
{
	for (auto pObj : m_lstGameObj[eID])
		SafeDelete(pObj);
	m_lstGameObj[eID].clear();

	return NOERROR;
}

GLvoid CGameManager::Progress_State()
{
	m_eGameState = GAME::STATE(m_eGameState + 1);
	if (m_eGameState >= GAME::END)
	{
		++m_iCurrTurn;
		if (m_iCurrTurn > 1)
			m_iCurrTurn = 0;
		m_eGameState = GAME::SELECT;
	}

	if (m_eGameState == GAME::RULLET)
		CSoundManager::GetInstance()->Play_Sound(L"Drum Roll.mp3", CSoundManager::ATTACK);
	else
		CSoundManager::GetInstance()->Stop_Sound(CSoundManager::ATTACK);

	return GLvoid();
}

CTransform* CGameManager::Get_Transform(OBJ::ID eID, int iIndex)
{
	if (iIndex >= m_lstGameObj[eID].size())
		return nullptr;

	list<CGameObj*>::iterator iter = m_lstGameObj[eID].begin();
	for (int i = 0; i < iIndex; ++i)
		++iter;

	return (*iter)->Get_Transform();
}

vec3 CGameManager::Get_PlatformPos(PLATFORM::TYPE eType)
{
	return m_arrPlatformPos[eType];
}

GLvoid CGameManager::Set_AddMoney(int iIndex, int iMoney)
{
	m_iAddMoney[iIndex] = m_iPlayerMoney[iIndex] - iMoney;
	if (m_iAddMoney[iIndex] < 0)
		m_iAddMoney[iIndex] = 0;
}

bool CGameManager::Play_MoneyAnimation(GLfloat fTimeDelta, int iIndex)
{
	bool bReturn = false;

	int iAdd = 0;
	int iGap = m_iAddMoney[iIndex] - m_iPlayerMoney[iIndex];

	if (abs(iGap) <= 100)
	{
		iGap = 0;
		bReturn = true;
	}

	if (iGap == 0)
		m_iPlayerMoney[iIndex] = m_iAddMoney[iIndex];
	else if (iGap < 0)
	{
		iAdd = -1 * 1000 * fTimeDelta;
		m_iPlayerMoney[iIndex] += iAdd;
		CSoundManager::GetInstance()->Play_Sound(L"Coin.wav", CSoundManager::UI);
	}
	else
	{
		iAdd = 1 * 1000 * fTimeDelta;
		m_iPlayerMoney[iIndex] += iAdd;
		CSoundManager::GetInstance()->Play_Sound(L"Coin.wav", CSoundManager::UI);
	}

	if (m_iPlayerMoney[iIndex] == 0)
	{
		// 게임종료
		m_iAddMoney[iIndex] = 0;
		m_iPlayerMoney[iIndex] = 0;
		m_iWinner = iIndex;
		bReturn = false;
	}

	return bReturn;
}

HRESULT CGameManager::Add_Camera(CCamera* pCamera)
{
	if (!pCamera)
		return E_FAIL;

	if (m_pCamera)
		SafeDelete(m_pCamera);
	m_pCamera = pCamera;

	return NOERROR;
}

GLvoid CGameManager::Render_Camera()
{
	if (m_pCamera)
		m_pCamera->Render();
}
