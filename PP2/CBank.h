#pragma once
#include <iostream>
#include <vector>
#include "CBankClient.h"
class CBankClient;

const float TIMEOUT = 5.0f;

class CBank
{
public:
	CBank();
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();
};