#pragma once

class CMesh;
class CObject17
{
public:
	CObject17();
	~CObject17();

public:
	vec3& Get_Position() { return m_vPos; }

public:
	HRESULT Initialize();
	GLuint Update();
	GLvoid Render();

public:
	GLvoid Move(vec3 vDir, float fSpeed);
	GLvoid Rotate(float fAngle);
	GLvoid Arm();

private:
	CMesh* m_pBase = nullptr;
	CMesh* m_pBody = nullptr;
	CMesh* m_pArmR = nullptr;
	CMesh* m_pArmL = nullptr;

private:
	float m_fAngle = 0.f;
	float m_fArmAngle = 0.f;
	float m_fAdd = 0.3f;
	vec3 m_vPos = vec3(0.f);

public:
	static CObject17* Create();
};

