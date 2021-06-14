#pragma once
#include "CComponent.h"

class CTransform : public CComponent
{
public:
	CTransform();
	~CTransform();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

public:
	mat4 Get_World();

public:
	vec3& Get_Scale() { return m_vScale; }
	vec3& Get_Position() { return m_vPos; }
	vec3& Get_Rotation() { return m_vRot; }
	vec3& Get_Direction() { return m_vDir; }
	vec3& Get_Revolution() { return m_vRev; }

public:
	GLvoid Update_World();

private:
	GLfloat m_fTimeDelta = 0.f;

private:
	vec3 m_vPos = vec3(0.f);						// ��ġ
	vec3 m_vScale = vec3(1.f);					// ũ��
	vec3 m_vRot = vec3(0.f);						// ����
	vec3 m_vRev = vec3(0.f);						// ����

private:
	vec3 m_vDir = vec3(0.f);

private:
	mat4 m_matScale = mat4(1.f);			//������ ���
	mat4 m_matRot = mat4(1.f);				//���� ���
	mat4 m_matTrans = mat4(1.f);			//�̵� ���
	mat4 m_matRev = mat4(1.f);				//���� ���
	mat4 m_matParent = mat4(1.f);		//�θ� ���

private:
	mat4 m_matWorld = mat4(1.f);

private:
	GLvoid Release();

public:
	static CTransform* Create();
};

