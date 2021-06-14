#include "stdafx.h"
#include "CTransform.h"

CTransform::CTransform()
{
}

CTransform::~CTransform()
{
}

HRESULT CTransform::Initialize()
{
	CComponent::Initialize();

	return NOERROR;
}

GLint CTransform::Update(const GLfloat fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;

	return GLint(OBJ_NOEVENT);
}

GLvoid CTransform::Render()
{
	Update_World();

	int iProgram = m_pShaderLoader->Get_CurrProgram();
	GLuint iLocation = glGetUniformLocation(iProgram, "matWorld");
	glUniformMatrix4fv(iLocation, 1, GL_FALSE, value_ptr(m_matWorld));
}

mat4 CTransform::Get_World()
{
	Update_World();

	return m_matWorld;
}

GLvoid CTransform::Update_World()
{
	m_matWorld = mat4(1.f);
	m_matTrans = translate(mat4(1.f), m_vPos);
	m_matScale = scale(mat4(1.f), m_vScale);

	m_matRot = mat4(1.f);
	m_matRot *= rotate(mat4(1.f), radians(m_vRot.x), vec3(1.f, 0.f, 0.f));
	m_matRot *= rotate(mat4(1.f), radians(m_vRot.y), vec3(0.f, 1.f, 0.f));
	m_matRot *= rotate(mat4(1.f), radians(m_vRot.z), vec3(0.f, 0.f, 1.f));

	m_matRev = mat4(1.f);
	m_matRev *= rotate(mat4(1.f), radians(m_vRev.x), vec3(1.f, 0.f, 0.f));
	m_matRev *= rotate(mat4(1.f), radians(m_vRev.y), vec3(0.f, 1.f, 0.f));
	m_matRev *= rotate(mat4(1.f), radians(m_vRev.z), vec3(0.f, 0.f, 1.f));

	m_matWorld = m_matParent * m_matRev * m_matTrans * m_matRot * m_matScale;
}

GLvoid CTransform::Release()
{
	return GLvoid();
}

CTransform* CTransform::Create()
{
	CTransform* pInstance = new CTransform;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
