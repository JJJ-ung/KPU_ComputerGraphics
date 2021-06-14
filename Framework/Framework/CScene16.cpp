#include "stdafx.h"
#include "CScene16.h"
#include "CShape.h"
#include "CMesh.h"
#include "CShaderLoader.h"

CScene16::CScene16()
{
}

CScene16::~CScene16()
{
	Release();
}

HRESULT CScene16::Initialize()
{
	if (FAILED(CShaderLoader::GetInstance()->Initialize_Shader("vertex.glsl", "pixel.glsl")))
		exit(EXIT_FAILURE);

	m_pCamera = CCamera::Create(vec3(1.f, 1.f, -3.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
	m_pCamera->Get_FovY() = 45.f;	m_pCamera->Get_Near() = 0.1f;	m_pCamera->Get_Far() = 50.f;
	m_pCamera->Get_Left() = -2.f;	m_pCamera->Get_Right() = 2.f;	m_pCamera->Get_Bottom() = -2.f;	m_pCamera->Get_Top() = 2.f;

	vector<vec3> vert = { vec3(-1.f, 0.f, 0.f), vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, -1.f, 0.f), vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, -1.f) };
	vector<vec3> col = { vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 1.f) };
	m_pLine = CShape::Create(vert, col, vert.size(), GL_LINES);

	Create_Cube();
	Create_Pyramid();

	return NOERROR;
}

GLuint CScene16::Update()
{
	switch (m_eAct)
	{
	case CScene16::TURN:
		if (m_bCube)
		{
			for (int i = 0; i < CUBE::END; ++i)
				m_pCube[i]->Revolate(vec3(0.f, 1.f, 0.f), 0.5f);
		}
		else
		{
			for (int i = 0; i < PYRAMID::END; ++i)
				m_pPyramid[i]->Revolate(vec3(0.f, 1.f, 0.f), 0.5f);
		}
	break;	

	case CScene16::CUBE_TOP:
		if (!m_bCube)
			break;
		m_pCube[CUBE::TOP]->Rotate(vec3(1.f, 0.f, 0.f), 0.5f);
	break;	

	case CScene16::CUBE_FRONT_OPEN:
		if (!m_bCube)
			break;
		if (m_fCubeAngle >= -90.f)
		{
			m_fCubeAngle -= 0.5f;
			m_pCube[CUBE::FRONT]->Rotate(vec3(1.f, 0.f, 0.f), -0.5f);
		}
	break;	

	case CScene16::CUBE_FRONT_CLOSE:
		if (!m_bCube)
			break;
		if (m_fCubeAngle < 0.f)
		{
			m_fCubeAngle += 0.5f;
			m_pCube[CUBE::FRONT]->Rotate(vec3(1.f, 0.f, 0.f), 0.5f);
		}
	break;

	case CScene16::PYRAMID_OPEN:
		if (m_bCube)
			break;
		if (m_fPyramidAngle > -110.f)
		{
			m_fPyramidAngle += -0.5f;
			for (int i = 0; i < PYRAMID::BOTTOM; ++i)
				m_pPyramid[i]->Rotate(vec3(1.f, 0.f, 0.f), -0.5f);
		}
	break;	

	case CScene16::PYRAMID_CLOSE:
		if (m_bCube)
			break;
		if (m_fPyramidAngle < 0.f)
		{
			m_fPyramidAngle += 0.5f;
			for (int i = 0; i < PYRAMID::BOTTOM; ++i)
				m_pPyramid[i]->Rotate(vec3(1.f, 0.f, 0.f), 0.5f);
		}
	break;	

	case CScene16::IDLE:
		break;
	default:
		break;
	}

	return GLuint();
}

GLvoid CScene16::Render()
{
	glEnable(GL_DEPTH_TEST);

	m_pLine->Render();

	if (m_bCube)
	{
		for (int i = 0; i < CUBE::END; ++i)
			m_pCube[i]->Render();
	}
	else
	{
		for (int i = 0; i < PYRAMID::END; ++i)
			m_pPyramid[i]->Render();
	}

	if (m_bOrtho)
		m_pCamera->Render_Ortho();
	else
		m_pCamera->Render();

	return GLvoid();
}

GLvoid CScene16::Input_Mouse(int button, int state, int x, int y)
{
	ScreenConvert(x, y);

	return GLvoid();
}

GLvoid CScene16::Input_KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'p' || key == 'P')
		m_bOrtho = !m_bOrtho;
	else if (key == 'y' || key == 'Y')
	{
		if (m_eAct == TURN)
			m_eAct = IDLE;
		else
			m_eAct = TURN;
	}
	else if (key == 't' || key == 'T')
	{
		if (m_bCube)
		{
			if (m_eAct == CUBE_TOP)
				m_eAct = IDLE;
			else
				m_eAct = CUBE_TOP;
		}
	}
	else if (key == 'f' || key == 'F')
	{
		if (m_bCube)
		{
			if (m_eAct == CUBE_FRONT_OPEN)
				m_eAct = CUBE_FRONT_CLOSE;
			else
				m_eAct = CUBE_FRONT_OPEN;
		}
	}
	else if (key == 'o' || key == 'O')
	{
		if (!m_bCube)
		{
			if (m_eAct == PYRAMID_OPEN)
				m_eAct = PYRAMID_CLOSE;
			else
				m_eAct = PYRAMID_OPEN;
		}
	}
	else
	{
		m_bCube = !m_bCube;
	}

	return GLvoid();
}

GLvoid CScene16::Create_Cube()
{
	vector<vec3> ver0 = { vec3(-0.5f, 1.f, 0.f),	vec3(0.5f, 0.f, 0.f), vec3(-0.5f, 0.f, 0.f),
										  vec3(-0.5f, 1.f, 0.f), vec3(0.5f, 1.f, 0.f), vec3(0.5f, 0.f, 0.f) };
	vector<vec3> col0 = { vec3(1.0f, 0.f, 0.0f),	vec3(1.0f, 0.f, 0.0f), vec3(1.0f, 0.f, 0.0f), vec3(1.0f, 0.f, 0.0f), vec3(1.0f, 0.f, 0.0f), vec3(1.0f, 0.f, 0.0f) };
	m_pCube[CUBE::FRONT] = CShape::Create(ver0, col0, ver0.size(), GL_TRIANGLES);
	m_pCube[CUBE::FRONT]->Move(vec3(0.f, -0.5f, -0.5f));

	//

	vector<vec3> ver1 = { vec3(-0.5f, 0.f, -0.5f),	vec3(0.5f, 0.f, 0.5f), vec3(-0.5f, 0.f, 0.5f),
										  vec3(-0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, 0.5f) };
	vector<vec3> col1 = { vec3(0.f, 0.f, 1.f),	vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, 1.f) };
	m_pCube[CUBE::BACK] = CShape::Create(ver1, col1, ver1.size(), GL_TRIANGLES);
	m_pCube[CUBE::BACK]->Rotate(vec3(1.f, 0.f, 0.f), 270.f);
	m_pCube[CUBE::BACK]->Move(vec3(0.f, 0.f, 0.5f));

	//

	vector<vec3> ver2 = { vec3(-0.5f, 0.f, -0.5f),	vec3(0.5f, 0.f, 0.5f), vec3(-0.5f, 0.f, 0.5f),
										  vec3(-0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, 0.5f) };
	vector<vec3> col2 = { vec3(0.f, 1.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 0.f) };
	m_pCube[CUBE::LEFT] = CShape::Create(ver2, col2, ver2.size(), GL_TRIANGLES);
	m_pCube[CUBE::LEFT]->Rotate(vec3(0.f, 0.f, 1.f), 90.f);
	m_pCube[CUBE::LEFT]->Move(vec3(-0.5f, 0.f, 0.f));

	//

	vector<vec3> ver3 = { vec3(-0.5f, 0.f, -0.5f),	vec3(0.5f, 0.f, 0.5f), vec3(-0.5f, 0.f, 0.5f),
										  vec3(-0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, 0.5f) };
	vector<vec3> col3 = { vec3(1.f, 1.f, 0.f),	vec3(1.f, 1.f, 0.f), vec3(1.f, 1.f, 0.f), vec3(1.f, 1.f, 0.f), vec3(1.f, 1.f, 0.f), vec3(1.f, 1.f, 0.f) };
	m_pCube[CUBE::RIGHT] = CShape::Create(ver3, col3, ver3.size(), GL_TRIANGLES);
	m_pCube[CUBE::RIGHT]->Rotate(vec3(0.f, 0.f, 1.f), 270.f);
	m_pCube[CUBE::RIGHT]->Move(vec3(0.5f, 0.f, 0.f));

	//

	vector<vec3> ver4 = { vec3(-0.5f, 0.f, -0.5f),	vec3(0.5f, 0.f, 0.5f), vec3(-0.5f, 0.f, 0.5f),
										  vec3(-0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, 0.5f) };
	vector<vec3> col4 = { vec3(0.f, 1.f, 1.f),	vec3(0.f, 1.f, 1.f), vec3(0.f, 1.f, 1.f), vec3(0.f, 1.f, 1.f), vec3(0.f, 1.f, 1.f), vec3(0.f, 1.f, 1.f) };
	m_pCube[CUBE::TOP] = CShape::Create(ver4, col4, ver4.size(), GL_TRIANGLES);
	m_pCube[CUBE::TOP]->Move(vec3(0.f, 0.5f, 0.f));

	//

	vector<vec3> ver5 = { vec3(-0.5f, 0.f, -0.5f),	vec3(0.5f, 0.f, 0.5f), vec3(-0.5f, 0.f, 0.5f),
										  vec3(-0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, -0.5f), vec3(0.5f, 0.f, 0.5f) };
	vector<vec3> col5 = { vec3(1.f, 0.f, 1.f),	vec3(1.f, 0.f, 1.f), vec3(1.f, 0.f, 1.f), vec3(1.f, 0.f, 1.f), vec3(1.f, 0.f, 1.f), vec3(1.f, 0.f, 1.f) };
	m_pCube[CUBE::BOTTOM] = CShape::Create(ver5, col5, ver5.size(), GL_TRIANGLES);
	m_pCube[CUBE::BOTTOM]->Move(vec3(0.f, -0.5f, 0.f));

	return GLvoid();
}

GLvoid CScene16::Create_Pyramid()
{
	vector<vec3> ver0 = { vec3(-0.5f, 0.f, 0.f), vec3(0.f, 1.f, 0.5f), vec3(0.5f, 0.f, 0.f) };
	vector<vec3> col0 = { vec3(1.f, 0.f, 0.f),	vec3(1.0f, 0.f, 0.f), vec3(1.f, 0.f, 0.f) };
	m_pPyramid[PYRAMID::FRONT] = CShape::Create(ver0, col0, ver0.size(), GL_TRIANGLES);
	m_pPyramid[PYRAMID::FRONT]->Move(vec3(0.f, -0.5f, -0.5f));
	
	vector<vec3> ver1 = { vec3(-0.5f, 0.f, 0.f), vec3(0.f, 1.f, 0.5f), vec3(0.5f, 0.f, 0.f) };
	vector<vec3> col1 = { vec3(0.f, 0.f, 1.f),	vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, 1.f) };
	m_pPyramid[PYRAMID::BACK] = CShape::Create(ver1, col1, ver1.size(), GL_TRIANGLES);
	m_pPyramid[PYRAMID::BACK]->Rotate(vec3(0.f, 1.f, 0.f), 180.f);
	m_pPyramid[PYRAMID::BACK]->Move(vec3(0.f, -0.5f, 0.5f));

	vector<vec3> ver2 = { vec3(-0.5f, 0.f, 0.f), vec3(0.f, 1.f, 0.5f), vec3(0.5f, 0.f, 0.f) };
	vector<vec3> col2 = { vec3(0.f, 1.f, 0.f),	vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 0.f) };
	m_pPyramid[PYRAMID::LEFT] = CShape::Create(ver2, col2, ver2.size(), GL_TRIANGLES);
	m_pPyramid[PYRAMID::LEFT]->Rotate(vec3(0.f, 1.f, 0.f), 90.f);
	m_pPyramid[PYRAMID::LEFT]->Move(vec3(-0.5f, -0.5f, 0.f));

	vector<vec3> ver3 = { vec3(-0.5f, 0.f, 0.f), vec3(0.f, 1.f, 0.5f), vec3(0.5f, 0.f, 0.f) };
	vector<vec3> col3 = { vec3(1.f, 1.f, 0.f),	vec3(1.f, 1.f, 0.f), vec3(1.f, 1.f, 0.f), vec3(1.f, 1.f, 0.f), vec3(1.f, 1.f, 0.f), vec3(1.f, 1.f, 0.f) };
	m_pPyramid[PYRAMID::RIGHT] = CShape::Create(ver3, col3, ver3.size(), GL_TRIANGLES);
	m_pPyramid[PYRAMID::RIGHT]->Rotate(vec3(0.f, 1.f, 0.f), 270.f);
	m_pPyramid[PYRAMID::RIGHT]->Move(vec3(0.5f, -0.5f, 0.f));

	vector<vec3> ver4 = { vec3(-0.5f, -0.5f, -0.5f),	vec3(0.5f, -0.5f, 0.5f), vec3(-0.5f, -0.5f, 0.5f),
										  vec3(-0.5f, -0.5f, -0.5f), vec3(0.5f, -0.5f, -0.5f), vec3(0.5f, -0.5f, 0.5f) };
	vector<vec3> col4 = { vec3(0.f, 1.f, 1.f),	vec3(0.f, 1.f, 1.f), vec3(0.f, 1.f, 1.f), vec3(0.f, 1.f, 1.f), vec3(0.f, 1.f, 1.f), vec3(0.f, 1.f, 1.f) };
	m_pPyramid[PYRAMID::BOTTOM] = CShape::Create(ver4, col4, ver4.size(), GL_TRIANGLES);

	return GLvoid();
}

GLvoid CScene16::Release()
{
	return GLvoid();
}

CScene16* CScene16::Create()
{
	CScene16* pInstance = new CScene16();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
