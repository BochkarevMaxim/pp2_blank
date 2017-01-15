#include "CBank.h"
#include "SyncPrimitiveHandler.h"

CBank::CBank(int clientsCount, CSyncPrimitiveHandler & syncPrimitive)
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
	m_threads = std::vector<HANDLE>();
	m_syncPrimitive = syncPrimitive;

	for (int i = 0; i < clientsCount; i++)
	{
		CreateClient();
	}
}

CBankClient* CBank::CreateClient()
{
	size_t clientId = m_clients.size();
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	m_threads.emplace_back(CreateThread(NULL, 0, &client->ThreadFunction, &*client, 0, NULL));
	return client;
}

void CBank::UpdateClientBalance(CBankClient &client, int value)
{	
	m_syncPrimitive.EnterSyncPrimitiveArea();

	std::cout << std::endl << "Client " << client.GetId() << " initiates reading total balance. Current total balance = " << GetTotalBalance() << ".";
	
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

	m_syncPrimitive.LeaveSyncPrimitiveArea();
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
	Sleep(LONG_OPERATIONS_TIMEOUT);
}

DWORD CBank::WaitForThreadsComplited()
{
	return WaitForMultipleObjects(m_threads.size(), m_threads.data(), TRUE, INFINITE);
}