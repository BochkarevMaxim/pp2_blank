#include "CBank.h"



CBank::CBank()
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
	m_threads = std::vector<HANDLE>();
}


CBankClient* CBank::CreateClient()
{
	unsigned int clientId = m_clients.size();
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	m_threads.emplace_back(CreateThread(NULL, 0, &client->ThreadFunction, &*client, 0, NULL));
	return client;
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{	
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << GetTotalBalance() << "." << std::endl;
	
	SomeLongOperations();
	int totalBalance = GetTotalBalance() + value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	if ((totalBalance < 0) || (totalBalance != GetTotalBalance() + value)) {
		std::cout << "! ERROR ! Balance will not be changed!" << std::endl;
	}
	else {
		SetTotalBalance(totalBalance);
	}
}


int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
	Sleep(TIMEOUT);
}

DWORD CBank::WaitForThreadsComplited()
{
	return WaitForMultipleObjects(m_threads.size(), m_threads.data(), TRUE, INFINITE);
}