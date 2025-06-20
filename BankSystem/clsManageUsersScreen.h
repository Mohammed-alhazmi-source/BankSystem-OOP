#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUserListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"


class clsManageUsersScreen : protected clsScreen
{
private:

	enum enManageUsersMenueOptions
	{
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
	};

	static short _ReadManageUsersMenueOption()
	{
		short Choice = 0;
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number Between 1 To 6? ");

		return Choice;
	}

	static void _ShowListUsersScreen()
	{
		clsUsersListScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _GoBackToManageUsersMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menue...\n";
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _PerfromManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
	{
		switch (ManageUsersMenueOption)
		{
		case clsManageUsersScreen::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		}

		case clsManageUsersScreen::eAddNewUser:
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case clsManageUsersScreen::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case clsManageUsersScreen::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case clsManageUsersScreen::eFindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case clsManageUsersScreen::eMainMenue:
		{
			break;
		}
		}
	}



public:

	static void ShowManageUsersMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::eManageUsers))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t Manage Users Screen");
		//ShowLoggedInUserWithDate();

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Users List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
	}
};

