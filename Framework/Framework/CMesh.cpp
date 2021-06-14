#include "stdafx.h"
#include "CMesh.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
	Release();
}

HRESULT CMesh::Initialize(string path, bool bCol, vec3 vCol)
{
	if (path == "")
		return E_FAIL;

	if (FAILED(LoadMesh(path)))
		return E_FAIL;

	m_iCnt = m_vecVertices.size();

	if (!bCol)
	{
		if (FAILED(SetDefaultColor()))
			return E_FAIL;
	}
	else
	{
		if (FAILED(SetVertexColor(vCol)))
			return E_FAIL;
	}

	glGenVertexArrays(1, &m_Vao); //--- VAO 를 지정하고 할당하기
	glGenBuffers(2, m_Vbo); //--- 2개의 VBO를 지정하고 할당하기

	glBindVertexArray(m_Vao); //--- VAO를 바인드하기

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_iCnt, &m_vecVertices.front() , GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_iCnt, &m_vecColors.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	m_pShaderLoader = CShaderLoader::GetInstance();

	return NOERROR;
}

GLuint CMesh::Update()
{
	return GLuint();
}

GLvoid CMesh::Render()
{
	m_matWorld = mat4(1.f);
	m_matTrans = translate(mat4(1.f), m_vPos);
	m_matScale = scale(mat4(1.f), m_vScale);
	m_matWorld = m_matParent * m_matRev * m_matTrans * m_matRot * m_matScale;

	glUseProgram(m_pShaderLoader->s_program);
	GLuint iLocation = glGetUniformLocation(m_pShaderLoader->s_program, "matWorld");
	glUniformMatrix4fv(iLocation, 1, GL_FALSE, value_ptr(m_matWorld));

	glBindVertexArray(m_Vao);
	glDrawArrays(GL_TRIANGLES, 0, m_iCnt);

	return GLvoid();
}

HRESULT CMesh::LoadMesh(string path)
{
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< vec3 > temp_vertices;
	vector< vec2 > temp_uvs;
	vector< vec3 > temp_normals;

	FILE* file = nullptr;
	if (FAILED(fopen_s(&file, path.c_str(), "r")))
	{
		cout << "Impossible to open the file !" << endl;
		return E_FAIL;
	}

	while (true)
	{
		char chLineHeader[128];
		int res = fscanf_s(file, "%s", chLineHeader, 128);
		if (res == EOF)
			break;

		if (strcmp(chLineHeader, "v") == 0)
		{
			vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(chLineHeader, "vt") == 0)
		{
			vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(chLineHeader, "vn") == 0)
		{
			vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(chLineHeader, "f") == 0)
		{
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				cout << "File can't be read by our simple parser : ( Try exporting with other options" << endl;
				return E_FAIL;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		vec3 vertex = temp_vertices[vertexIndex - 1];
		m_vecVertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		vec2 uv = temp_uvs[uvIndex - 1];
		m_vecUV.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		vec3 normal = temp_normals[normalIndex - 1];
		m_vecNormals.push_back(normal);
	}

	return NOERROR;
}

HRESULT CMesh::SetDefaultColor()
{
	for (GLuint i = 0; i < m_iCnt / 3; ++i)
	{
		m_vecColors.emplace_back(vec3(1.f, 0.f, 0.f));
		m_vecColors.emplace_back(vec3(0.f, 1.f, 0.f));
		m_vecColors.emplace_back(vec3(0.f, 0.f, 1.f));
	}

	return NOERROR;
}

HRESULT CMesh::SetVertexColor(vec3 vCol)
{
	m_vecColors.clear();

	for (GLuint i = 0; i < m_iCnt; ++i)
		m_vecColors.emplace_back(vCol);

	return NOERROR;
}

HRESULT CMesh::ChangeVertexColor(vec3 col)
{
	for (GLuint i = 0; i < m_vecColors.size(); ++i)
		m_vecColors[i] = col;

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_iCnt, &m_vecColors.front(), GL_STATIC_DRAW);

	return NOERROR;
}

GLvoid CMesh::Update_World()
{
	m_matWorld = mat4(1.f);
	m_matTrans = translate(mat4(1.f), m_vPos);
	m_matScale = scale(mat4(1.f), m_vScale);
	m_matWorld = m_matParent * m_matRev * m_matTrans * m_matRot * m_matScale;

	return GLvoid();
}

GLvoid CMesh::Rotate(vec3 Axis, float fAngle)
{
	mat4 matRot = rotate(mat4(1.f), ToRadian(fAngle), Axis);
	m_matRot *= matRot;

	return GLvoid();
}

GLvoid CMesh::Revolate(vec3 Axis, float fAngle)
{
	mat4 matRot = rotate(mat4(1.f), ToRadian(fAngle), Axis);
	m_matRev *= matRot;

	return GLvoid();
}

GLvoid CMesh::RotateX(float fAngle)
{
	vec3 axis = vec3(m_vPos.x, 0.f, 0.f);
	if (m_vPos.x <= 0.f)
		axis.x = 1.f;
	normalize(axis);

	mat4 matRot = rotate(mat4(1.f), ToRadian(fAngle), axis);
	m_matRot *= matRot;

	return GLvoid();
}

GLvoid CMesh::RotateY(float fAngle)
{
	vec3 axis = vec3(0.f, m_vPos.y, 0.f);
	if (m_vPos.y <= 0.f)
		axis.y = 1.f;
	normalize(axis);

	mat4 matRot = rotate(mat4(1.f), ToRadian(fAngle), axis);
	m_matRot *= matRot;

	return GLvoid();
}

GLvoid CMesh::Release()
{
	return GLvoid();
}

CMesh* CMesh::Create(string path, bool bCol, vec3 vCol)
{
	CMesh* pInstance = new CMesh;

	if (FAILED(pInstance->Initialize(path, bCol, vCol)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
