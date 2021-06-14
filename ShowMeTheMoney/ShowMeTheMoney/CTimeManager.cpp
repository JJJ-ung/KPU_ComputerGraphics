#include "stdafx.h"
#include "CTimeManager.h"

IMPLEMENT_SINGLETON(CTimeManager)

CTimeManager::CTimeManager()
{
	// �ϵ��� �ִ� ���ػ� Ÿ�̸� ���� ������ �Լ�.
	// Ÿ�̸� ���� Cpu�� Clock�� ������� �Ѵ�.
	// �ᱹ Ÿ�̸� ���� ���� ��������.
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);

	// Cpu�� Clock�� �ʴ� ������(Hz)�� ������ �Լ�.
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
