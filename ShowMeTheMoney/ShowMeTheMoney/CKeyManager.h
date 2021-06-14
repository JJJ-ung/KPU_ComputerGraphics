#pragma once

const DWORD KEY_LB = 0x00000001;
const DWORD KEY_RB = 0x00000002;

class CKeyManager
{
	DECLARE_SINGLETON(CKeyManager)

private:
	CKeyManager();
	~CKeyManager();

public:
	const vec2 Get_Mouse() { return m_vMouse; }

public:
	void Update_Key();
	void Update_Mouse(int x, int y);

public:
	bool KeyDown(DWORD dwCurKey);
	bool KeyUp(DWORD dwCurKey);
	bool KeyPressing(DWORD dwCurKey);
	bool KeyCombined(DWORD dwFistKey, DWORD dwSecondKey);

private:
	vec2 m_vMouse = vec2(0.f);

private:
	DWORD m_dwCurKey = 0;
	DWORD m_dwKeyUp = 0;
	DWORD m_dwKeyDown = 0;
};

