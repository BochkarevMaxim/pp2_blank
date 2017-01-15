#pragma once
#include <iostream>
#include <vector>
#include "CBankClient.h"
class CBankClient;

const float TIMEOUT = 5.0f;

enum executionCode
{
	SUCCESS,
	ERR
};

class CBank
{
public:
	CBank(int clientsCount);
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	DWORD WaitForThreadsComplited();
private:
	std::vector<CBankClient> m_clients;
	std::vector<HANDLE>	m_threads;
	int m_totalBalance;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();
};