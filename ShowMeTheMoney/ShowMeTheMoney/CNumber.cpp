#include "stdafx.h"
#include "CNumber.h"

#include "CPlane.h"
#include "CTexture.h"
#include "CTransform.h"

CNumber::CNumber()
{
}

CNumber::~CNumber()
{
}

HRESULT CNumber::Initialize(GLuint iIndex)
{
    CGameObj::Initialize();

    srand((unsigned int)time(NULL));

    m_iPlayerIndex = iIndex;

    char szTmp[MAX_STR];
    for (int i = 0; i < 10; ++i)
    {
        sprintf_s(szTmp, "../Bin/Resources/Sprite/Number/Num%d.png", i);
        CTexture* pTex = CTexture::Create("Num", string(szTmp), true);
        if (!pTex)
            return E_FAIL;
        m_vecNumTexture.push_back(pTex);
    }

    for (int i = 0; i < m_iMaxNumCnt; ++i)
    {
        m_arrNumber[i].buffer = CPlane::Create();
        if (!m_arrNumber[i].buffer)
            return E_FAIL;
        m_arrNumber[i].transform = CTransform::Create();
        if (!m_arrNumber[i].transform)
            return E_FAIL;
        m_arrNumber[i].transform->Get_Scale() = vec3(38.f * 0.4f, 65.f * 0.4f, 1.f);
        m_arrNumber[i].transform->Get_Position() = vec3(275.f + 950 * m_iPlayerIndex - (25.f * i), 620.f - 590.f * m_iPlayerIndex, 0.f);
    }

    m_matProj = ortho(0.f, (float)WINCX, 0.f, (float)WINCY, 0.f, 100.0f);               // 직교투영하는것임
    m_matView = mat4(1.f);

    return NOERROR;
}

GLint CNumber::Update(const GLfloat fTimeDelta)
{
    // 해당하는 숫자에 따른 텍스쳐 바꿔치기
    int iMoney = m_pGameMgr->Get_Money(m_iPlayerIndex);

    // 계산을 위해 플레이어의 돈을 저장해줌.
    int Money = iMoney;
    int i = 0;

    for (int j = 0; j < 5; j++)
    {
        m_arrNumber[j].texture = {};
    }
    while (Money > 0)
    {
        int k = Money % 10;
        m_arrNumber[i].texture = m_vecNumTexture[k];
        Money /= 10;
        i++;
    }
    if (Money == 0)
    {
        m_arrNumber[0].texture = m_vecNumTexture[0];
    }
    CGameObj::Update_Component(fTimeDelta);
    m_pRenderer->Add_RenderObj(RENDER::UI, this);                  // ** 필수

    return GLint();
}

GLvoid CNumber::Render()
{
    GLuint program = m_pShaderLoader->Use_Shader("UI");
    int viewLoc = glGetUniformLocation(program, "matView");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));
    int ProjLoc = glGetUniformLocation(program, "matProj");
    glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

    for (int i = 0; i < m_iMaxNumCnt; ++i)
    {
        if (m_arrNumber[i].texture == nullptr)
            continue;

        m_arrNumber[i].transform->Render();
        m_arrNumber[i].texture->Render();
        m_arrNumber[i].buffer->Render();
    }

    return GLvoid();
}

GLvoid CNumber::Release()
{
    return GLvoid();
}

CNumber* CNumber::Create(GLuint iIndex)
{
    CNumber* pInstance = new CNumber;

    if (FAILED(pInstance->Initialize(iIndex)))
    {
        SafeDelete(pInstance);
        return nullptr;
    }

    return pInstance;
}