#include "CGameObj.h"

class CObject;
class CPlatform : public CGameObj
{
public:
	CPlatform();
	~CPlatform();

public:
	virtual HRESULT Initialize(PLATFORM::TYPE eType);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	HRESULT Initialize_Tree();
	HRESULT Initialize_DIY();
	HRESULT Initialize_Fish();
	HRESULT Initialize_Fossil();
	HRESULT Initialize_Grass();
	HRESULT Initialize_Insect();
	HRESULT Initialize_Stone();
	HRESULT Initialize_Fruit();
	HRESULT Initialize_NPC();

private:
	list<CObject*> m_lstRenderObj;

private:
	GLvoid Release();

public:
	static CPlatform* Create(PLATFORM::TYPE eType);
};

