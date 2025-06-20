#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";
    }

public:
    static void ShowDeleteUserScreen()
    {
        system("cls");
        _DrawScreenHeader("\t Delete User Screen");
        //ShowLoggedInUserWithDate();

        string UserName = "";
        cout << "\nPlease Enter UserName : ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Is Not Found, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);

        char Answer = 'n';
        cout << "\nDo You Sure You Want To Delete This User y/n? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully\n";
                _PrintUser(User);
            }

            else
            {
                cout << "\nError User Was Not Deleted";
            }
        }
    }
};