#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Globla.h"
#include "clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		bool LoginFailed = false;
		short FailedLoginCount = 0;

		do
		{
			if (LoginFailed)
			{
				FailedLoginCount++;

				cout << "\n\t\t\t\t\tInvalid UserName/Password!\n";
				cout << "\t\t\t\t\tYou Have " << (3 - FailedLoginCount) << " Trials To Login.\n";
			}

			if (FailedLoginCount == 3)
			{
				cout << "\n\n\t\t\t\t\tYour Are Locked After 3 Failed Trails\n";
				return false;
			}

			cout << "\n\t\t\t\t\tEnter UserName? ";
			string UserName = clsInputValidate::ReadString();

			cout << "\t\t\t\t\tEnter Password? ";
			string Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();
		} while (LoginFailed);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}
public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     Login Screen");
		return _Login();
	}
};