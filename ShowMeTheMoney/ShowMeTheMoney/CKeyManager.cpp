#include "stdafx.h"
#include "CKeyManager.h"

IMPLEMENT_SINGLETON(CKeyManager)

CKeyManager::CKeyManager()
{
}

CKeyManager::~CKeyManager()
{
}

void CKeyManager::Update_Key()
{
	m_dwCurKey = 0;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwCurKey |= KEY_LB;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwCurKey |= KEY_RB;
}

void CKeyManager::Update_Mouse(int x, int y)
{
	m_vMouse = vec2(x, y);
	//m_vMouse.x = (x - WINCX * 0.5f) / WINCX * 0.5f;
	//m_vMouse.y = ((WINCY - y) - WINCY * 0.5f) / WINCY * 0.5f;
}

bool CKeyManager::KeyDown(DWORD dwCurKey)
{
	// ���� ������ ���� ���� ������ �� true
	if (!(m_dwKeyDown & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown |= dwCurKey;
		return true;
	}

	// m_dwKeyDown�� ����
	// ���� ������ �ְ� ���� ������ �ʾ��� ��
	else if ((m_dwKeyDown & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown ^= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyUp(DWORD dwCurKey)
{
	// ���� ������ �ְ� ���� ������ �ʾ��� �� true
	if ((m_dwKeyUp & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		// m_dwKeyUp�� ����
		m_dwKeyUp ^= dwCurKey;
		return true;
	}

	// ���� ������ ���� ���� ������ �� 
	else if (!(m_dwKeyUp & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyUp |= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyPressing(DWORD dwCurKey)
{
	if (m_dwCurKey & dwCurKey)
		return true;

	return false;
}

bool CKeyManager::KeyCombined(DWORD dwFistKey, DWORD dwSecondKey)
{
	if (KeyDown(dwSecondKey) && KeyPressing(dwFistKey))
		return true;

	return false;
}
