#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionsMenueOptions
	{
		eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3,
		eTransfer = 4, eShowTransferLog = 5, eShowMainMenue = 6
	};

	static short _ReadTransactionMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choose = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number Between 1 To 4? ");
		return Choose;
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transaction Menue...\n";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _PerfromTransactionMenueOption(enTransactionsMenueOptions TransactionMenueOption)
	{
		switch (TransactionMenueOption)
		{
		case clsTransactionsScreen::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionMenue();
			break;

		case clsTransactionsScreen::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionMenue();
			break;

		case clsTransactionsScreen::eShowTotalBalance:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionMenue();
			break;

		case clsTransactionsScreen::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionMenue();
			break;

		case clsTransactionsScreen::eShowTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionMenue();
			break;

		case clsTransactionsScreen::eShowMainMenue:
			// ��� �������� �� ���� ������ �������
			break;
		}
	}


public:

	static void ShowTransactionsMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::eTransactions))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t Transaction Screen");
		//ShowLoggedInUserWithDate();

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transaction Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromTransactionMenueOption((enTransactionsMenueOptions)_ReadTransactionMenueOption());
	}
};