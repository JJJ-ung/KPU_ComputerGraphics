#pragma once

#define BLUE vec3(0.f, 0.635f, 0.909f)
#define YELLOW vec3(0.909f, 0.749f, 0.f)

class CMesh;
class CShape;
class CPlanet15
{
public:
	enum TYPE { PARENT, CHILD, END };

public:
	CPlanet15();
	~CPlanet15();

public:
	HRESULT Initialize(float fRot, float fSpeed);
	GLuint Update();
	GLvoid Render();

public:
	GLvoid WireFrame();
	GLvoid Move(vec3 vDir);
	GLvoid Rot(float fAngle);

private:
	CShape* Create_Circle(float fRadius);
	vec3 Circle_Position(float fRadius, float fAngle);

private:
	CShape* m_pLine[END];
	CMesh* m_pMesh[END];

	float m_fSpeed = 1.f;
	bool m_bWire = false;

public:
	static CPlanet15* Create(float fRot, float fSpeed);
};

