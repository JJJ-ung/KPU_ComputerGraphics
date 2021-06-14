#pragma once

class CTimeManager
{
	DECLARE_SINGLETON(CTimeManager)

private:
	CTimeManager();
	~CTimeManager();

public:
	const float& Get_Delta() const;

public:
	void Update_Time();

private:
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime;
	LARGE_INTEGER	m_CpuTick;
	float			m_fDeltaTime = 0.f;
};

