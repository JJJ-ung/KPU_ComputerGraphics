#include "stdafx.h"
#include "CTimeManager.h"

IMPLEMENT_SINGLETON(CTimeManager)

CTimeManager::CTimeManager()
{
	// 하드웨어에 있는 고해상도 타이머 값을 얻어오는 함수.
	// 타이머 값은 Cpu의 Clock을 기반으로 한다.
	// 결국 타이머 값은 누적 진동수다.
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);

	// Cpu의 Clock의 초당 진동수(Hz)를 얻어오는 함수.
	QueryPerformanceFrequency(&m_CpuTick);
}

CTimeManager::~CTimeManager()
{
}

const float& CTimeManager::Get_Delta() const
{
	return m_fDeltaTime;
}

void CTimeManager::Update_Time()
{
	QueryPerformanceCounter(&m_CurTime);

	if (m_CurTime.QuadPart - m_OldTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceCounter(&m_CurTime);
		QueryPerformanceCounter(&m_OldTime);
		QueryPerformanceFrequency(&m_CpuTick);
	}

	m_fDeltaTime =
		float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;

	m_OldTime.QuadPart = m_CurTime.QuadPart;
}
