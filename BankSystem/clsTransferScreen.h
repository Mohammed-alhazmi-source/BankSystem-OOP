#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : clsScreen
{
private:
	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n----------------------\n\n";
		cout << "Full Name   : " << Client.FullName() << endl;
		cout << "Acc. Number : " << Client.AccountNumber() << endl;
		cout << "Balance     : " << Client.AccountBalance << endl;
		cout << "\n----------------------\n\n";
	}

	static string _ReadAccountNumber(string Message = "")
	{
		string AccountNumber = "";
		cout << Message;
		cin >> AccountNumber;

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Not Found, Enter Another Again : ";
			cin >> AccountNumber;
		}

		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient SourceClient)
	{
		double Amount = 0;
		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds The Available Balance, Enter Another Again? ";
			Amount = clsInputValidate::ReadDblNumber();
		}

		return Amount;
	}

public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t Transfer Screen");

		string Message = "\nPlease Enter Account Number To Transfer From : ";

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber(Message));
		_PrintClientCard(SourceClient);

		Message = "\nPlease Enter Account Number To Transfer To : ";

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber(Message));

		while (DestinationClient.AccountNumber() == SourceClient.AccountNumber())
		{
			cout << " the same account, Enter Another AccountNumber : ";
			DestinationClient = clsBankClient::Find(_ReadAccountNumber(Message));
		}

		_PrintClientCard(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		cout << "\nAre You Sure You Want To Perform This Operation? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient))
			{
				cout << "\nTransfer Done Successfully";
				_PrintClientCard(SourceClient);
				_PrintClientCard(DestinationClient);
			}
			else
			{
				cout << "\nTransfer Failed";
			}
		}
		else
		{
			cout << "\nOperation Was Cancelled.\n";
		}
	}
};