#pragma once
#include <string>
#include <Windows.h>

class CSyncPrimitiveHandler
{
public:
	CSyncPrimitiveHandler(const std::string & syncPrimitiveType);
	~CSyncPrimitiveHandler();

	void EnterSyncPrimitiveArea();
	void LeaveSyncPrimitiveArea();

private:
	std::string m_syncPrimitiveType;
	HANDLE m_syncPrimitive;
	CRITICAL_SECTION m_criticalSection;

};
