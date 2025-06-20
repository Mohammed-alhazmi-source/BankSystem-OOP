#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
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

	static string _ReadCurrencyCode()
	{
		cout << "\n\nPlease Enter Currency Code : ";
		string Code = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(Code))
		{
			cout << "\nCurrency Code Is Not Found, Enter Another Again : ";
			Code = clsInputValidate::ReadString();
		}
		return Code;
	}

	static float _ReadRate()
	{
		cout << "\n\nEnter New Rate : ";
		float NewRate = clsInputValidate::ReadFloatNumber();

		return NewRate;
	}

public:
	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\t Update Currency Screen");

		string CurrencyCode = _ReadCurrencyCode();

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		_PrintCurrency(Currency);

		cout << "\n Are You Sure You Want To Update The Rate Of This Currency y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			cout << "\n\nUpdate Currency Rate:";
			cout << "\n____________________\n\n";

			Currency.UpdateRate(_ReadRate());

			cout << "\n\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);
		}
	}
};