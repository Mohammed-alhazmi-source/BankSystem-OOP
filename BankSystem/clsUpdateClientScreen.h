#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nFirstName      : ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "LastName       : ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Phone          : ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Email          : ";
        Client.Email = clsInputValidate::ReadString();

        cout << "PinCode        : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "AccountBalance : ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

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

public:
    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::eUpdateClient))
        {
            return;
        }

        _DrawScreenHeader("\t Update Client Screen\n");
        //ShowLoggedInUserWithDate();

        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";

            _ReadClientInfo(Client1);

            clsBankClient::enSaveResults SaveResults;

            SaveResults = Client1.Save();

            switch (SaveResults)
            {
            case clsBankClient::svSucceeded:
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClient(Client1);
                break;

            case clsBankClient::svFaildEmptyObject:
                cout << "\nError account was not saved because it's Empty";
                break;
            }
        }
    }
};