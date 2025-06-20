#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsString.h"
#include "clsUser.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginsRegisterRecord)
	{
		cout << setw(8) << left << "" << "| " << setw(25) << left << LoginsRegisterRecord.DateTime;
		cout << "| " << setw(20) << left << LoginsRegisterRecord.UserName;
		cout << "| " << setw(20) << left << LoginsRegisterRecord.Password;
		cout << "| " << setw(20) << left << LoginsRegisterRecord.Permissions;
	}



public:
	static void ShowListLoginsRegister()
	{
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::eShowLoginRegisterList))
		{
			return;
		}

		vector<clsUser::stLoginRegisterRecord> vLoginsRegister = clsUser::GetLoginRegisterList();


		string Title = "\t Login Register List Screen\n";
		string SubTitle = "\t (" + to_string(vLoginsRegister.size()) + ") Record(s).\n";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(20) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;


		if (vLoginsRegister.size() == 0)
			cout << "\t\t\t\tNo Login Register Available In the System!";

		else
			for (clsUser::stLoginRegisterRecord LoginRegisterRecord : vLoginsRegister)
			{
				_PrintLoginRegisterRecordLine(LoginRegisterRecord);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
};