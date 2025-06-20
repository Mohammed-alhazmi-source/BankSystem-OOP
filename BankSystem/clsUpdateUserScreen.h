#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
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

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = 'n';

		cout << "\nDo You Want To Give Full Access? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			return Permissions = clsUser::enPermissions::eAll;

		cout << "\nDo You Want To Give Access To : \n";

		cout << "\nShow Client List y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eShowClientList;

		cout << "\nAdd New Client y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eAddNewClient;

		cout << "\nDelete Client y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eDeleteClient;

		cout << "\nUpdate Client Info y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eUpdateClient;

		cout << "\nFind Client y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eFindClient;

		cout << "\nTransactions y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eTransactions;

		cout << "\nManage Users y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eManageUsers;

		cout << "\nShow Login Register y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eShowLoginRegisterList;

		return Permissions;
	}

	static void _ReadUserInfo(clsUser& User)
	{
		//char Answer = 'n';

		cout << "\nFirsName    : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nLastName    : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEmail       : ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nPhone       : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nPassword    : ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nPermissions : ";
		User.Permissions = _ReadPermissionsToSet();
	}


public:
	static void ShowUpdateUserScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Update User Screen");
		//ShowLoggedInUserWithDate();

		cout << "\nPlease Enter UserName : ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Is Not Found, Choose Another one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'n';
		cout << "\nDo You Want Updated This User y/n? ";
		cin >> Answer;


		if (Answer == 'Y' || Answer == 'y')
		{
			cout << "\n\nUpdate User Info:";
			cout << "\n____________________\n";

			_ReadUserInfo(User);
			clsUser::enSaveResults SaveResults;
			SaveResults = User.Save();

			switch (SaveResults)
			{
			case clsUser::enSaveResults::svSucceeded:
				cout << "\nAccount Updated Successfully :-)\n";
				_PrintUser(User);
				break;

			case clsUser::enSaveResults::svFaildEmptyObject:
				cout << "\nError account was not saved because it's Empty";
				break;
			}
		}

		else
			cout << "\nOperation Was Cancelled";
	}
};

