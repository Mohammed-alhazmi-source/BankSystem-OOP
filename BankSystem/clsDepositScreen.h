#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsTransactionsScreen.h"

using namespace std;
class clsDepositScreen : protected clsScreen
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

    static void ShowDepositScreen()
    {
        system("cls");
        _DrawScreenHeader("\t     Deposit Screen");
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
        cout << "\nPlease Enter Deposit Amount : ";
        Amount = clsInputValidate::ReadDblNumber();

        char Answer = 'n';
        cout << "\nAre You Sure You Want To Perfrom This Transaction? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is : " << Client.AccountBalance << endl;
        }
        else
        {
            cout << "\nOperation Was Cancelled.\n";
        }

    }
};

