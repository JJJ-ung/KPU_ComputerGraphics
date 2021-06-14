#include "stdafx.h"
#include "CCamera.h"
#include "CTransform.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

HRESULT CCamera::Initialize()
{
	CGameObj::Initialize();

	m_matProj = perspective(radians(m_fFovY), (float)WINCX / (float)WINCY, m_fNear, m_fFar);

	m_vDir = normalize(vec3(0.f, -1.f, -1.f));

	m_vAt = vec3(0.f, 0.f, 1.f);

	return NOERROR;
}

GLint CCamera::Update(const GLfloat fTimeDelta)
{
	if(m_pGameMgr->Get_GameState() == GAME::SELECT)
		Change_State(CAMERA::FULL);
	if (m_pGameMgr->Get_GameState() == GAME::RULLET)
	{
		if (m_pGameMgr->Get_CurrTurn() == 0)
			Change_State(CAMERA::PLAYER1);
		if (m_pGameMgr->Get_CurrTurn() == 1)
			Change_State(CAMERA::PLAYER2);
	}
	if (m_pGameMgr->Get_GameState() == GAME::ANIMATION)
	{
		if (m_pGameMgr->Get_CurrTurn() == 0)
			Change_State(CAMERA::PLAYER1_ANI);
		if (m_pGameMgr->Get_CurrTurn() == 1)
			Change_State(CAMERA::PLAYER2_ANI);
	}

	switch (m_eState)
	{
	case CAMERA::FULL:
		m_fDistance = 6.f;
		m_vDir = normalize(vec3(0.f, -1.f, -1.f));
		m_vAt = vec3(0.f, 0.f, 1.f);
		m_fAngle = 0.f;
		break;
	case CAMERA::PLAYER1:
		m_fDistance = 3.f;
		m_vDir = normalize(vec3(0.f, -1.f, -1.f));
		m_vAt = m_pGameMgr->Get_Transform(OBJ::PLAYER1)->Get_Position() + vec3(0.f, -0.2f, 0.f);
		m_fAngle += fTimeDelta * 20.f;
		break;
	case CAMERA::PLAYER2:
		m_fDistance = 3.f;
		m_vDir = normalize(vec3(0.f, -1.f, -1.f));
		m_vAt = m_pGameMgr->Get_Transform(OBJ::PLAYER2)->Get_Position() + vec3(0.f, -0.2f, 0.f);
		m_fAngle += fTimeDelta * 20.f;
		break;
	case CAMERA::PLAYER1_ANI:
		m_vAt = m_pGameMgr->Get_Transform(OBJ::PLAYER1)->Get_Position();
		break;
	case CAMERA::PLAYER2_ANI:
		m_vAt = m_pGameMgr->Get_Transform(OBJ::PLAYER2)->Get_Position();
		break;
	default:
		break;
	}

	//mat4 matTrans = translate(mat4(1.f), m_vEye);
	mat4 matRot = rotate(mat4(1.f), radians(m_fAngle), vec3(0.f, 1.f, 0.f));
	vec3 vDir = vec3(matRot * vec4(m_vDir, 1.f));

	m_vEye = m_vAt - vDir * m_fDistance;

	m_vLightDir = vDir;
	m_matView = lookAt(m_vEye, m_vAt, m_vUp);
	return GLint();
}

GLvoid CCamera::Render()
{
	GLuint program = CShaderLoader::GetInstance()->Get_CurrProgram();

	int viewLoc = glGetUniformLocation(program, "matView");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));

	int ProjLoc = glGetUniformLocation(program, "matProj");
	glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

	int PosLoc = glGetUniformLocation(program, "vCameraPos");
	glUniform3fv(PosLoc, 1, value_ptr(m_vEye));

	int DirLoc = glGetUniformLocation(program, "vLightDir");
	glUniform3fv(DirLoc, 1, value_ptr(vec3(m_vLightDir)));
}

GLvoid CCamera::Update_Matrix()
{
	m_matView = lookAt(m_vEye, m_vAt, m_vUp);
}

GLvoid CCamera::Change_State(CAMERA::STATE eState)
{
	if (eState == m_eState)
		return;

	m_eState = eState;
	m_fAngle = 0.f;
}

GLvoid CCamera::Release()
{
	return GLvoid();
}

CCamera* CCamera::Create()
{
	CCamera* pInstance = new CCamera;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
