#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsLoginRegisterScreen.h"


using namespace std;
class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;



    string  _PrepareTransferLogRecord(double Amount, clsBankClient DestinationClient, string Separator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Separator;
        TransferLogRecord += AccountNumber() + Separator;
        TransferLogRecord += DestinationClient.AccountNumber() + Separator;
        TransferLogRecord += to_string(Amount) + Separator;
        TransferLogRecord += to_string(AccountBalance) + Separator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Separator;
        TransferLogRecord += CurrentUser.UserName;

        return TransferLogRecord;
    }

    void _RegisterTransferLog(double Amount, clsBankClient DestinationClient)
    {
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);
        string DataLine = _PrepareTransferLogRecord(Amount, DestinationClient);

        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;

        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);
        string Line;
        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

    string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
    {
        string ClientLine = "";
        ClientLine += Client.FirstName + Separator;
        ClientLine += Client.LastName + Separator;
        ClientLine += Client.Email + Separator;
        ClientLine += Client.Phone + Separator;
        ClientLine += Client.AccountNumber() + Separator;
        ClientLine += Client.PinCode + Separator;
        ClientLine += to_string(Client.AccountBalance);

        return ClientLine;
    }

    void _SaveClientsDataToFile(vector<clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        if (MyFile.is_open())
        {
            string DataLine = "";

            for (clsBankClient C : vClients)
            {
                if (C._MarkedForDelete == false)
                {
                    DataLine = _ConvertClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsBankClient> vClients;
        vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }

        _SaveClientsDataToFile(vClients);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string Line)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << Line << endl;
            MyFile.close();
        }
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    struct stTransferLogRecord;
    static stTransferLogRecord _ConvertRegisterTransferLineToRecord(string DataLine, string Separator = "#//#")
    {
        stTransferLogRecord RegisterTransferRecord;
        vector<string> vRegisterTransferRecord = clsString::Split(DataLine, Separator);

        RegisterTransferRecord.DateTime = vRegisterTransferRecord[0];
        RegisterTransferRecord.SourceAccountNumber = vRegisterTransferRecord[1];
        RegisterTransferRecord.DestinationAccountNumber = vRegisterTransferRecord[2];
        RegisterTransferRecord.Amount = stod(vRegisterTransferRecord[3]);
        RegisterTransferRecord.SourceBalanceAfterTransfer = stod(vRegisterTransferRecord[4]);
        RegisterTransferRecord.DestinationBalanceAfterTransfer = stod(vRegisterTransferRecord[5]);
        RegisterTransferRecord.UserName = vRegisterTransferRecord[6];

        return RegisterTransferRecord;
    }

public:

    struct stTransferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double SourceBalanceAfterTransfer;
        double DestinationBalanceAfterTransfer;
        string UserName;
    };

    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDelete()
    {
        return _MarkedForDelete;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case clsBankClient::EmptyMode: // 1
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
            break;
        }

        case clsBankClient::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
        }

        case clsBankClient::AddNewMode: // 2
        {
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                // change Mode Object After Add To UpdateMode 
                _Mode = clsBankClient::enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
        }
    }


    bool Delete()
    {
        vector<clsBankClient> vClients;
        vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                _SaveClientsDataToFile(vClients);
                *this = _GetEmptyClientObject();
                return true;
            }
        }
        return false;
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }


    static double GetTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        double TotalBalances = 0;

        for (clsBankClient C : vClients)
        {
            TotalBalances += C.AccountBalance;
        }
        return TotalBalances;
    }

    static double GetTotalBalances(vector<clsBankClient> vClients)
    {
        double TotalBalances = 0;

        for (clsBankClient C : vClients)
        {
            TotalBalances += C.AccountBalance;
        }
        return TotalBalances;
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
            return false;

        _AccountBalance -= Amount;
        Save();
    }

    bool Transfer(double Amount, clsBankClient& DestinationClient)
    {
        if (Amount > AccountBalance)
            return false;

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient);
        return true;
    }


    static vector<stTransferLogRecord> GetTransferLogList()
    {
        fstream MyFile;
        vector<stTransferLogRecord> vTransferLogRecord;

        MyFile.open("TransferLog.txt", ios::in);


        if (MyFile.is_open())
        {
            stTransferLogRecord TransferRecord;
            string DataLine = "";

            while (getline(MyFile, DataLine))
            {
                TransferRecord = _ConvertRegisterTransferLineToRecord(DataLine);
                vTransferLogRecord.push_back(TransferRecord);
            }
            MyFile.close();
        }
        return vTransferLogRecord;
    }
};