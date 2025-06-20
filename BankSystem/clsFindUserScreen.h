#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsUpdateUserScreen.h"

class clsFindUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Info.:\n";
		cout << "-----------------------\n";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFullName    : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUserName    : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n-----------------------\n";
	}

public:
	static void ShowFindUserScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Find User Screen");
		//ShowLoggedInUserWithDate();

		string UserName = "";
		cout << "\nPlease Enter User UserName : ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Is Not Found, Choose Another one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
		{
			cout << "\nUser Found:-)\n";
		}
		else
		{
			cout << "\nUser Was Not Found:-(";
		}

		_PrintUser(User);
	}
};

