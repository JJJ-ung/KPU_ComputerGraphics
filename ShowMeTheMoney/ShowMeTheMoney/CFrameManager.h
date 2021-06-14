#pragma once

class CFrameManager
{
	DECLARE_SINGLETON(CFrameManager)

private:
	CFrameManager();
	~CFrameManager();

public:
	bool Frame_Limit(float fLimit);

private:
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime;
	LARGE_INTEGER	m_CpuTick;
	float			m_fTimeCount = 0.f;
};

