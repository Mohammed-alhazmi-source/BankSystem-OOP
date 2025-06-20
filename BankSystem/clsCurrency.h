#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "clsString.h"
#include <string>
using namespace std;

class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdatedMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;


	static clsCurrency _ConvertLineToCurrencyObject(string DataLine, string Separator = "#//#")
	{
		vector<string> vCurrencyData = clsString::Split(DataLine, Separator);

		return clsCurrency
		(
			enMode::UpdatedMode, vCurrencyData[0], vCurrencyData[1],
			vCurrencyData[2], stof(vCurrencyData[3])
		);
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
	{
		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.Country() + Separator;
		stCurrencyRecord += Currency.CurrencyCode() + Separator;
		stCurrencyRecord += Currency.CurrencyName() + Separator;
		stCurrencyRecord += to_string(Currency.Rate());

		return stCurrencyRecord;
	}

	static vector<clsCurrency> _LoadCurrenysDataFromFile()
	{
		fstream MyFile;
		vector<clsCurrency> vCurrencyData;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrencyData.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencyData;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencyData)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		string DataLine = "";

		if (MyFile.is_open())
		{
			for (clsCurrency C : vCurrencyData)
			{
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> vCurrencyData = _LoadCurrenysDataFromFile();

		for (clsCurrency& C : vCurrencyData)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				_SaveCurrencyDataToFile(vCurrencyData);
				break;
			}
		}
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}


	//float _GetCurrencyRateToUSD(float Amount)
	//{
	//	return (Amount / _Rate);
	//}

	//static float _GetUSDRateToCurrencyRate(float Amount, clsCurrency CurrencyTo)
	//{
	//	return (Amount * CurrencyTo.Rate());
	//}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string Country() { return _Country; }
	string CurrencyCode() { return _CurrencyCode; }
	string CurrencyName() { return _CurrencyName; }
	void UpdateRate(float Rate)
	{
		_Rate = Rate;
		_Update();
	}
	float Rate() { return _Rate; }

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsCurrency FindByCode(string Code)
	{
		Code = clsString::UpperAllString(Code);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.CurrencyCode()) == Code)
				{
					MyFile.close();
					return Currency;
				}
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}
	//static bool IsCurrencyExistByCountry(string Country)
	//{
	//	clsCurrency Currency = clsCurrency::FindByCountry(Country);
	//	return (!Currency.IsEmpty());
	//}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenysDataFromFile();
	}

	static vector <clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrenysDataFromFile();
	}


	float ConvertToUSD(float Amount)
	{
		return (Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency CurrencyTo)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (CurrencyTo.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (AmountInUSD * CurrencyTo.Rate());
	}
};