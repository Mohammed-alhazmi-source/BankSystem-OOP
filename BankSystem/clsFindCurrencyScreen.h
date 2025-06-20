#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "\n______________________________\n\n";
		cout << "Country     : " << Currency.Country() << endl;
		cout << "Code        : " << Currency.CurrencyCode() << endl;
		cout << "Name        : " << Currency.CurrencyName() << endl;
		cout << "Rate/(1$) = : " << Currency.Rate() << endl;
		cout << "\n______________________________\n\n";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)";
			_PrintCurrency(Currency);
		}

		else
			cout << "\nCurrency Was Not Found :-(";
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");

		cout << "\n\nFind By : [1] Code or [2] Country ? ";

		short Answer = 1;
		cin >> Answer;

		if (Answer == 1)
		{
			cout << "\nPlease Enter CurrencyCode : ";
			string Code = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(Code);
			_ShowResults(Currency);
		}
		else
		{
			cout << "\nPlease Enter Country : ";
			string Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}
	}

};

