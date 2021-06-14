#pragma once

class CCamera;
class CGameObj;
class CTransform;
class CGameManager
{
	DECLARE_SINGLETON(CGameManager)

private:
	CGameManager();
	~CGameManager();

public:
	GLint& Get_CurrTurn() { return m_iCurrTurn; }
	GLint& Get_Money(int iIndex) { return m_iPlayerMoney[iIndex]; }
	GAME::STATE& Get_GameState() { return m_eGameState; }
	GLint Get_Winner() { return m_iWinner; }

public:
	HRESULT Add_GameObj(OBJ::ID eID, CGameObj* pObj);
	GLvoid Update(const GLfloat fTimeDelta);
	HRESULT Clear_ObjList();
	HRESULT Clear_Obj(OBJ::ID eID);

public:
	GLvoid Progress_State();
	CTransform* Get_Transform(OBJ::ID eID, int iIndex = 0);
	vec3 Get_PlatformPos(PLATFORM::TYPE eType);

public:
	GLvoid Set_AddMoney(int iIndex, int iMoney);
	bool Play_MoneyAnimation(const GLfloat fTimeDelta, int iIndex);

public:
	HRESULT Add_Camera(CCamera* pCamera);
	GLvoid Render_Camera();
	CCamera* Get_Camera() { return m_pCamera; }

private:
	GLint m_iCurrTurn = 0;
	GLint m_iWinner = -1;
	GAME::STATE m_eGameState = GAME::SELECT;
	GLint m_iPlayerMoney[2] = { 3000, 3000 };
	GLint m_iAddMoney[2] = { 0 };

private:
	vec3 m_arrPlatformPos[PLATFORM::END];

private:
	CCamera* m_pCamera;
	list<CGameObj*> m_lstGameObj[OBJ::END];
};

