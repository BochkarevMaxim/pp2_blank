#include "stdafx.h"
#include <iostream>
#include "CBank.h"
#include "CBankClient.h"

enum executionCode
{
	SUCCESS,
	ERR
};

using namespace std;
void PrintHelp();
bool ReadCommandLineParams(int argc, char *argv[], int& clientsCount, string& primitiveType);

int main(int argc, char *argv[])
{
	int clientsCount = 0;
	string primitiveType = "";

	if(!ReadCommandLineParams(argc, argv, clientsCount, primitiveType)){ 
		return ERR;
	}

	cout << clientsCount << endl;
	cout << primitiveType.c_str();

	CBank* bank = new CBank();
	CBankClient* client1 = bank->CreateClient();
	CBankClient* client2 = bank->CreateClient();

	// TODO: WaitForMultipleObjects
	bank->WaitForThreadsComplited();

    return 0;
}

void PrintHelp()
{
	//cout << "pp2.exe <bankClientsNumber> <syncPrimitive>\n\tmutex\n\tsemaphore\n\tevent\n\tcritical_section\nif syncPrimitive don`t specified or incorrect, primitive won`t use";
	cout << "Application takes 2 parametres: \n - clients amount \n - synchronization primitive (you can choose one):\n";
	cout << "    cs (critical section)\n    mutex\n    semaphore\n    event\n    none(app will work without any synchronization primitive\n";

}

bool ReadCommandLineParams(int argc, char *argv[], int& clientsCount, string& primitiveType)
{
	if (argc > 1)
	{
		if (string(argv[1]) == "?" || string(argv[1]) == "/?" || string(argv[1]) == "--help")
		{
			PrintHelp();
			return false;
		}
		else if (argc == 3) {
			try {
				clientsCount = atoi(argv[1]);
				primitiveType = string(argv[2]);
				return true;
			}
			catch (exception e) {
				cout << "Command line parse error, check your input!\n";
				return false;
			}
		}
		else {
			cout << "Incorrect amount of parametres. Use /? for help. " << endl;
			return false;
		}
	}
	else {
		cout << "Incorrect amount of parametres. Use /? for help. " << endl;
		return false;
	}
}
