#include "stdafx.h"
#include <iostream>
#include "CBank.h"
#include "SyncPrimitiveHandler.h"
#include "CBankClient.h"

using namespace std;



void PrintHelp();
bool ReadCommandLineParams(int argc, char *argv[], int& clientsCount, string& primitiveType);
bool isPrimitiveTypeCorrect(string primitiveType);

int main(int argc, char *argv[])
{
	int clientsCount = 0;
	string primitiveType = "";

	if(!ReadCommandLineParams(argc, argv, clientsCount, primitiveType)){ 
		cout << "Command line parametres read error. Run app with /? to help.\n";
		return ERR;
	}

	if (!isPrimitiveTypeCorrect(primitiveType)) {
		cout << "Incorrect synchronising primitive type. Use /? for help.\n";
		return ERR;
	}
	else if (clientsCount < 1) {
		cout << "Clients amount must be more or equal than 1!\n";
		return ERR;
	}

	if (clientsCount > 0)
	{
		CSyncPrimitiveHandler syncPrimitive("mutex");
		CBank* bank = new CBank(clientsCount, syncPrimitive);

		// TODO: WaitForMultipleObjects
		bank->WaitForThreadsComplited();
	}

	return SUCCESS;
}

void PrintHelp()
{
	cout << "Application takes 2 parametres: \n - clients amount \n - synchronization primitive (you can choose one):\n";
	cout << "    critical_section\n    mutex\n    semaphore\n    event\n    none(app will work without any synchronization primitive\n";
}

bool isPrimitiveTypeCorrect(string primitiveType) {
	if ((primitiveType == "semaphore") ||
		(primitiveType == "critical_section") ||
		(primitiveType == "mutex") ||
		(primitiveType == "event") ||
		(primitiveType == "none"))
		return true;
	else {
		return false;
	}
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
