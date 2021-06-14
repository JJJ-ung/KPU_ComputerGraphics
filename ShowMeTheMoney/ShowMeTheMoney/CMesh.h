#pragma once
#include "CComponent.h"

class CMesh : public CComponent
{
public:
	CMesh();
	~CMesh();

public:
	virtual HRESULT Initialize(string strPath);
	virtual GLvoid Render();

private:
	HRESULT Load_Mesh(string strPath);
	HRESULT Load_Material(string strPath);

private:
	MATERIAL* Get_Material(char* chMatName);

private:
	vector<vec3> m_vecVertices;
	vector<vec2> m_vecTexcoords;
	vector<vec3> m_vecNormals;

private:
	vector<SUBMESH*> m_vecSubMesh;
	vector<MATERIAL*> m_vecMaterials;

private:
	GLvoid Release();

public:
	static CMesh* Create(string strPath);
};

