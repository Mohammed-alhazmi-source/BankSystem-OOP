#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private:
	static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
	{
		cout << setw(8) << left << "" << "| " << setw(25) << left << TransferLogRecord.DateTime;
		cout << "| " << setw(10) << left << TransferLogRecord.SourceAccountNumber;
		cout << "| " << setw(10) << left << TransferLogRecord.DestinationAccountNumber;
		cout << "| " << setw(10) << left << TransferLogRecord.Amount;
		cout << "| " << setw(10) << left << TransferLogRecord.SourceBalanceAfterTransfer;
		cout << "| " << setw(10) << left << TransferLogRecord.DestinationBalanceAfterTransfer;
		cout << "| " << setw(10) << left << TransferLogRecord.UserName;
	}


public:
	static void ShowTransferLogScreen()
	{
		vector<clsBankClient::stTransferLogRecord> vRegisterTransferRecord = clsBankClient::GetTransferLogList();

		string Title = "\t Transfer Log List Screen\n";
		string SubTitle = "\t (" + to_string(vRegisterTransferRecord.size()) + ") Record(s).\n";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "S.Acct";
		cout << "| " << left << setw(10) << "D.Acct";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "S.Balance";
		cout << "| " << left << setw(10) << "D.Balance";
		cout << "| " << left << setw(10) << "User";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;


		if (vRegisterTransferRecord.size() == 0)
			cout << "\t\t\t\tNo Transfer Available In the System!";

		else
			for (clsBankClient::stTransferLogRecord RegisterTransferRecord : vRegisterTransferRecord)
			{
				_PrintTransferLogRecordLine(RegisterTransferRecord);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}

};