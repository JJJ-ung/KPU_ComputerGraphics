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
	// 전에 누른적 없고 현재 눌렸을 때 true
	if (!(m_dwKeyDown & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown |= dwCurKey;
		return true;
	}

	// m_dwKeyDown을 원복
	// 전에 누른적 있고 현재 누르지 않았을 때
	else if ((m_dwKeyDown & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown ^= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyUp(DWORD dwCurKey)
{
	// 전에 누른적 있고 현재 누르지 않았을 때 true
	if ((m_dwKeyUp & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		// m_dwKeyUp을 원복
		m_dwKeyUp ^= dwCurKey;
		return true;
	}

	// 전에 누른적 없고 현재 눌렸을 때 
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
