#include "SyncPrimitiveHandler.h"



CSyncPrimitiveHandler::CSyncPrimitiveHandler(const std::string & syncPrimitiveType)
{
	m_syncPrimitiveType == syncPrimitiveType;
	if (syncPrimitiveType == "mutex")
	{
		m_syncPrimitive = CreateMutex(NULL, false, NULL);
	}
	else if (syncPrimitiveType == "semaphore")
	{
		m_syncPrimitive = CreateSemaphore(NULL, 1, 1, NULL);
	}
	else if (syncPrimitiveType == "event")
	{
		m_syncPrimitive = CreateEvent(NULL, false, true, NULL);
	}
	else if (syncPrimitiveType == "critical_section")
	{
		InitializeCriticalSection(&m_criticalSection);
	}
}


CSyncPrimitiveHandler::~CSyncPrimitiveHandler()
{
	if (m_syncPrimitiveType == "critical_section")
	{
		DeleteCriticalSection(&m_criticalSection);
	}
}

void CSyncPrimitiveHandler::EnterSyncPrimitiveArea()
{
	if (m_syncPrimitiveType == "critical_section")
	{
		EnterCriticalSection(&m_criticalSection);
	}
	else {
		WaitForSingleObject(m_syncPrimitive, INFINITE);
	}
}

void CSyncPrimitiveHandler::LeaveSyncPrimitiveArea()
{
	if (m_syncPrimitiveType == "critical_section")
	{
		EnterCriticalSection(&m_criticalSection);
	}
	else if (m_syncPrimitiveType == "event")
	{
		SetEvent(m_syncPrimitive);
	}
	else if (m_syncPrimitiveType == "mutex")
	{
		ReleaseMutex(m_syncPrimitive);
	}
	else if (m_syncPrimitiveType == "semaphore")
	{
		ReleaseSemaphore(m_syncPrimitive, 1, NULL);
	}
}
