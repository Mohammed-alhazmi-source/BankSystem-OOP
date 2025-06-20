#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsUser.h"
#include "Globla.h"
using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << endl << endl;
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n\n";
        cout << "\t\t\t\t\tUser: " << CurrentUser.UserName << endl;
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermissions(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }

        else
            return true;
    }
};