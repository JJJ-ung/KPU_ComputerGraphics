#include "stdafx.h"
#include "CRullet.h"

#include "CTexture.h"
#include "CTransform.h"
#include "Cplane.h"

// 룰렛 헤더파일에 private 추가됨.

CRullet::CRullet()
{
}

CRullet::~CRullet()
{
}

HRESULT CRullet::Initialize()
{
    CGameObj::Initialize();

    srand((unsigned int)time(NULL));

    CPlane* pPlane = CPlane::Create();
    if (FAILED(Add_Component(COMPONENT::BUFFER, pPlane)))
        return E_FAIL;

    CTexture* pTexture = CTexture::Create("Rullet", "../Bin/Resources/Sprite/Rullet/Rullet1.png");

    m_pTransform = CTransform::Create();
    //m_pTransform->Get_Position() = vec3(640.f, 360.f, 0.0f);
    m_pTransform->Get_Position() = vec3(640.f, 100.f, 0.0f);
    m_pTransform->Get_Scale() = vec3(pTexture->Get_Width() * 0.45f, pTexture->Get_Height() * 0.45f, 1.f);

    m_matProj = ortho(0.f, (float)WINCX, 0.f, (float)WINCY, 0.f, 100.0f);               // 직교투영하는것임

    m_matView = mat4(1.f);

    speed_limit = (rand() % 3001 + 1000) * 1.f;

    if (FAILED(Add_Component(COMPONENT::TEXTURE, pTexture)))
        return E_FAIL;
    if (FAILED(Add_Component(COMPONENT::UPDATE, m_pTransform)))
        return E_FAIL;

    return NOERROR;
}

GLint CRullet::Update(const GLfloat fTimeDelta)
{
    m_pTransform->Get_Rotation().z += speed * fTimeDelta;
    if (speed > speed_limit)
        speed_delta *= -1;
    if (speed > 0.0f)
    {
        speed += speed_delta;
    }
    else if (speed < 0.0f)
    {
        speed = 0.0f;
    }
    if (m_pTransform->Get_Rotation().z >= 360.f)
        m_pTransform->Get_Rotation().z = 0.f;

    if (speed == 0.0f)
    {
        if (m_pTransform->Get_Rotation().z > 0.f && m_pTransform->Get_Rotation().z < 90.f)
        {
            result = Fail;
        }
        if (m_pTransform->Get_Rotation().z > 90.f && m_pTransform->Get_Rotation().z < 180.f)
        {
            result = Great_Success;
        }
        if (m_pTransform->Get_Rotation().z > 180.f && m_pTransform->Get_Rotation().z < 270.f)
        {
            result = Great_Fail;
        }
        if (m_pTransform->Get_Rotation().z > 270.f && m_pTransform->Get_Rotation().z < 360.f)
        {
            result = Success;
        }
        if (Get_Result == FALSE)
        {
            m_fTime += fTimeDelta * 1.f;
            if (m_fTime > 1.f)
            {
                Get_Result = TRUE;
                if (result == 0)
                {
                    cout << "Success";
                    int iRand = 500 + rand() % 500;
                    m_pGameMgr->Set_AddMoney(m_pGameMgr->Get_CurrTurn(), iRand);
                    m_pGameMgr->Progress_State();
                    m_pSoundManager->Play_Sound(L"Success.mp3", CSoundManager::JUMP);
                    Reset();
                }
                else if (result == 1)
                {
                    cout << "Fail";
                    int iRand = 250 + rand() % 250;
                    m_pGameMgr->Set_AddMoney(m_pGameMgr->Get_CurrTurn(), -iRand);
                    m_pGameMgr->Progress_State();
                    m_pSoundManager->Play_Sound(L"Fail.mp3", CSoundManager::EFFECT);
                    Reset();
                }
                else if (result == 2)
                {
                    cout << "Great_Success";
                    int iRand = 1000 + rand() % 1000;
                    m_pGameMgr->Set_AddMoney(m_pGameMgr->Get_CurrTurn(), iRand);
                    m_pGameMgr->Progress_State();
                    m_pSoundManager->Play_Sound(L"Success.mp3", CSoundManager::DJUMP);
                    Reset();
                }
                else if (result == 3)
                {
                    cout << "Great_Fail";
                    int iRand = 500 + rand() % 250;
                    m_pGameMgr->Set_AddMoney(m_pGameMgr->Get_CurrTurn(), -iRand);
                    m_pGameMgr->Progress_State();
                    m_pSoundManager->Play_Sound(L"Fail.mp3", CSoundManager::JATTACK);
                    Reset();
                }
            }
        }
    }
    CGameObj::Update_Component(fTimeDelta);

    m_pRenderer->Add_RenderObj(RENDER::UI, this);

    return GLint(OBJ_NOEVENT);
}

GLvoid CRullet::Render()
{
    GLuint program = m_pShaderLoader->Use_Shader("UI");
    int viewLoc = glGetUniformLocation(program, "matView");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));
    int ProjLoc = glGetUniformLocation(program, "matProj");
    glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

    CGameObj::Render_Component();

    return GLvoid();
}

GLvoid CRullet::Release()
{
    return GLvoid();
}

HRESULT CRullet::Reset()
{
    m_pTransform->Get_Rotation().z = 0.f;
    speed_limit = (rand() % 3001 + 1000) * 1.f;
    Get_Result = FALSE;
    speed = 10.f;
    speed_delta = 13.f;
    m_fTime = 0.f;

    return NOERROR;
}

CRullet* CRullet::Create()
{
    CRullet* pInstance = new CRullet;

    if (FAILED(pInstance->Initialize()))
    {
        SafeDelete(pInstance);
        return nullptr;
    }

    return pInstance;
}