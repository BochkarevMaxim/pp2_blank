#pragma once
#include "stdafx.h"
#include "CBankClient.h"
#include "SyncPrimitiveHandler.h"
class CBankClient;

const float LONG_OPERATIONS_TIMEOUT = 5.0f;

class CBank
{
public:
	CBank(int clientsCount, CSyncPrimitiveHandler & syncPrimitive);
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	DWORD WaitForThreadsComplited();

private:
	CSyncPrimitiveHandler m_syncPrimitive;
	std::vector<CBankClient> m_clients;
	std::vector<HANDLE>	m_threads;
	int m_totalBalance;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();
};