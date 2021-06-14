#include "stdafx.h"
#include "CFrameManager.h"

IMPLEMENT_SINGLETON(CFrameManager)

CFrameManager::CFrameManager()
{
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceFrequency(&m_CpuTick);
}

CFrameManager::~CFrameManager()
{
}

bool CFrameManager::Frame_Limit(float fLimit)
{
	QueryPerformanceCounter(&m_CurTime);

	if (m_CurTime.QuadPart - m_OldTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceCounter(&m_CurTime);
		QueryPerformanceCounter(&m_OldTime);
		QueryPerformanceFrequency(&m_CpuTick);
	}

	m_fTimeCount += float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;
	m_OldTime.QuadPart = m_CurTime.QuadPart;

	if ((1.f / fLimit) <= m_fTimeCount)
	{
		m_fTimeCount = 0.f;
		return true;
	}

	return false;
}
