#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAddNewClientScreen.h"
#include <vector>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsUtil.h"

class clsAddNewUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card: \n";
		cout << "UserName    : " << User.UserName << endl;
		cout << "FirstName   : " << User.FirstName << endl;
		cout << "LastName    : " << User.LastName << endl;
		cout << "Email       : " << User.Email << endl;
		cout << "Phone       : " << User.Phone << endl;
		cout << "Password    : " << User.Password << endl;
		cout << "Permissions : " << User.Permissions << endl;
	}

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = 'n';


		cout << "\nDo You Want To Give Full Access? y/n? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
			return Permissions = -1;

		cout << "\nDo You Want To Give Access To : \n";

		cout << "\nShow Clients List ? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eShowClientList;

		cout << "\nAdd New Client ? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eAddNewClient;

		cout << "\nDelete Client ? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eDeleteClient;

		cout << "\nUpdate Client ? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eUpdateClient;

		cout << "\nFind Client ? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eFindClient;

		cout << "\nTransactions ? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::eTransactions;

		cout << "\nManage Users ? y/n? ";
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
		cout << "\nFirstName : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nLastName  : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEmail     : ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nPhone     : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nPassword  : ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions\n";
		User.Permissions = _ReadPermissionsToSet();
	}


public:

	static void ShowAddNewUserScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Add New User Screen");
		//ShowLoggedInUserWithDate();

		cout << "\nPlease Enter UserName : ";
		string UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name Is Already Used, Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResults;
		SaveResults = NewUser.Save();

		switch (SaveResults)
		{
		case clsUser::svSucceeded:
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;

		case clsUser::svFaildEmptyObject:
			cout << "\nError account was not saved because it's Object Empty";
			break;

		case clsUser::svFaildUserExists:
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}
	}
};