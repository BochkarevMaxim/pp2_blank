#pragma once
#include "stdafx.h"
#include "CBank.h"
class CBank;

class CBankClient
{
public:
	unsigned int GetId();

private:
	unsigned m_id;
	CBank *m_bank;

	CBankClient(CBank *bank, unsigned int id);
	static unsigned int GetSleepDuration(CBankClient *client);
	static unsigned int GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

	friend CBank;
};