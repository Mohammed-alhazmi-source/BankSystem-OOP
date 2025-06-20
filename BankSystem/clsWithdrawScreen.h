#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsTransactionsScreen.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter AccountNumber : ";
        AccountNumber = clsInputValidate::ReadString();

        return AccountNumber;
    }

public:

    static void ShowWithdrawScreen()
    {
        system("cls");
        _DrawScreenHeader("\t     Withdraw Screen");
        //ShowLoggedInUserWithDate();

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client With [" << AccountNumber << "] Does Not Exist.";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nPlease Enter Withdraw Amount : ";
        Amount = clsInputValidate::ReadDblNumber();

        char Answer = 'n';
        cout << "\nAre You Sure You Want To Perfrom This Transaction? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdraw Successfully.\n";
                cout << "\nNew Balance Is : " << Client.AccountBalance << endl;
            }
            else
            {
                cout << "\nCannot Withdraw, Insufficient Balance!\n";
                cout << "\nAmount To Withdraw Is : " << Amount;
                cout << "\nYour Balance Is : " << Client.AccountBalance << endl;
            }
        }
        else
        {
            cout << "\nOperation Was Cancelled.\n";
        }

    }
};