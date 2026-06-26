// mashroa_7_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string FileNameCantrale = "Cilent.txt";
void ShowMainMenue();
void ShowMenueTransactions();

struct stCantrle
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phon;
    double AccountBalance;
    bool MarkForDelete = false;
};

// دالة قص النصوص المحدثة والآمنة من الـ Infinite Loops
vector <string> SplitString(string S1, string Delim)
{
    vector <string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

stCantrle ConvertLinetoRecord(string Line, string Seperator = "#\\#")
{
    stCantrle Clinte;
    vector <string> vClinteData = SplitString(Line, Seperator);

    // حماية في حال كان السطر فارغاً أو تالفاً بالملف لمنع الانهيار
    if (vClinteData.size() >= 5) {
        Clinte.AccountNumber = vClinteData[0];
        Clinte.PinCode = vClinteData[1];
        Clinte.Name = vClinteData[2];
        Clinte.Phon = vClinteData[3];
        Clinte.AccountBalance = stod(vClinteData[4]);
    }
    return Clinte;
}

string ConvertRecordToLine(stCantrle Clinte, string Seperator = "#\\#") {
    string stConvertRecord = "";
    stConvertRecord += Clinte.AccountNumber + Seperator;
    stConvertRecord += Clinte.PinCode + Seperator;
    stConvertRecord += Clinte.Name + Seperator;
    stConvertRecord += Clinte.Phon + Seperator;
    stConvertRecord += to_string(Clinte.AccountBalance);
    return stConvertRecord;
}

bool ClientExistsByAccountNumbe(string AccountNumber, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            stCantrle Clinte = ConvertLinetoRecord(Line);
            if (Clinte.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

// دالة قراءة عميل جديد بعد إصلاح موقع الـ return
stCantrle ReadNewClien() {
    stCantrle Clinte;
    cout << "Enter Account Number ?\n";
    getline(cin >> ws, Clinte.AccountNumber);

    while (ClientExistsByAccountNumbe(Clinte.AccountNumber, FileNameCantrale))
    {
        cout << "\nClient with [" << Clinte.AccountNumber << "] already exists, Enter another Account Number ? ";
        getline(cin >> ws, Clinte.AccountNumber);
    }

    cout << "Enter Pincode ?\n";
    getline(cin, Clinte.PinCode);
    cout << "Enter Name ?\n";
    getline(cin, Clinte.Name);
    cout << "Enter Phone ?\n";
    getline(cin, Clinte.Phon);
    cout << "Enter Account Balance ?\n";
    cin >> Clinte.AccountBalance;

    return Clinte; // مكانها الصحيح هنا خارج الـ while للـ حماية
}

vector <stCantrle> LoadCleintsDataFromFile(string FileName)
{
    vector <stCantrle> vClinte;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            stCantrle Clinte = ConvertLinetoRecord(Line);
            if (Clinte.AccountNumber != "") {
                vClinte.push_back(Clinte);
            }
        }
        MyFile.close();
    }
    return vClinte;
}

void PrintClientRecordLine(stCantrle Clinte) {
    cout << "| " << setw(15) << left << Clinte.AccountNumber;
    cout << "| " << setw(10) << left << Clinte.PinCode;
    cout << "| " << setw(40) << left << Clinte.Name;
    cout << "| " << setw(12) << left << Clinte.Phon;
    cout << "| " << setw(12) << left << Clinte.AccountBalance;
}
void PrintClientRecordBalanceLine(stCantrle Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScree() {
    vector <stCantrle> vClients = LoadCleintsDataFromFile(FileNameCantrale);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stCantrle Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    cout << "\n_______________________________________________________________________________________________________\n" << endl;
}
void ShowTotalBalance() {
    vector <stCantrle>vClients = LoadCleintsDataFromFile(FileNameCantrale);
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
        cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    double TotalBalance = 0;
    if (vClients.size()==0)
         cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stCantrle Clinte : vClients)
        {
            PrintClientRecordBalanceLine(Clinte);
            TotalBalance += Clinte.AccountBalance;
            cout << endl;
        }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t Total Balances = " << TotalBalance;

}

void PrintClientCard(stCantrle Clinte) {
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccount Number: " << Clinte.AccountNumber;
    cout << "\nPin Code       : " << Clinte.PinCode;
    cout << "\nName           : " << Clinte.Name;
    cout << "\nPhone          : " << Clinte.Phon;
    cout << "\nAccount Balance: " << Clinte.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumbe(string AccountNumber, vector <stCantrle> vClinte, stCantrle& Clinte) {
    for (stCantrle C : vClinte)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Clinte = C;
            return true;
        }
    }
    return false;
}

stCantrle ChangeClientRecord(string AccountNumber) {
    stCantrle Clinte;
    Clinte.AccountNumber = AccountNumber; // تم تعديلها من == إلى =
    cout << "\n Enter Pin Code \n";
    getline(cin >> ws, Clinte.PinCode);
    cout << "\n  Enter Name \n";
    getline(cin, Clinte.Name);
    cout << "\n Enter Phone \n";
    getline(cin, Clinte.Phon);
    cout << "\n Enter Account Balance \n";
    cin >> Clinte.AccountBalance;
    return Clinte;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stCantrle>& vClinte) {
    for (stCantrle& C : vClinte)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector <stCantrle> SaveCleintsDataToFile(string FileName, vector <stCantrle> vClinte)
{
    fstream Myfile;
    Myfile.open(FileName, ios::out);
    string DateLine;
    if (Myfile.is_open())
    {
        for (stCantrle C : vClinte)
        {
            if (!C.MarkForDelete)
            {
                DateLine = ConvertRecordToLine(C);
                Myfile << DateLine << endl;
            }
        }
        Myfile.close();
    }
    return vClinte;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream Myfile;
    Myfile.open(FileName, ios::out | ios::app);
    if (Myfile.is_open())
    {
        Myfile << stDataLine << endl;
        Myfile.close();
    }
}

void AddNewClien()
{
    stCantrle Clinte = ReadNewClien();
    AddDataLineToFile(FileNameCantrale, ConvertRecordToLine(Clinte));
}

void AddNewClient() {
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "Adding New Client:\n\n";
        AddNewClien();
        cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y'); // تعديل towupper إلى toupper القياسية
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stCantrle>& vClinte)
{
    stCantrle Clinte;
    char Anser = 'n';
    if (FindClientByAccountNumbe(AccountNumber, vClinte, Clinte))
    {
        PrintClientCard(Clinte);
        cout << "\nAre you sure you want delete this client? y/n?";
        cin >> Anser;
        if (Anser == 'y' || Anser == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClinte);
            SaveCleintsDataToFile(FileNameCantrale, vClinte);
            vClinte = LoadCleintsDataFromFile(FileNameCantrale);
            cout << "\n\nClient Deleted Successfully";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
    return false;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stCantrle>& vClinte) {
    stCantrle Clinte;
    char Anser = 'n';
    if (FindClientByAccountNumbe(AccountNumber, vClinte, Clinte))
    {
        PrintClientCard(Clinte);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Anser;
        if (Anser == 'y' || Anser == 'Y')
        {
            for (stCantrle& C : vClinte)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(FileNameCantrale, vClinte);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
    return false;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber,
    double Amount, vector <stCantrle>&vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y / n ? ";
        cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (stCantrle& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(FileNameCantrale, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        }
        return false;
    }
}

string ReadClientAccountNumbe() {
    string AccountNumber = "";
    cout << "Please Enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void ShowDeleteClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector <stCantrle> vClinte = LoadCleintsDataFromFile(FileNameCantrale);
    string AccountNumber = ReadClientAccountNumbe();
    DeleteClientByAccountNumber(AccountNumber, vClinte);
}

void ShowUpdateClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    vector <stCantrle> vClinte = LoadCleintsDataFromFile(FileNameCantrale);
    string AccountNumber = ReadClientAccountNumbe();
    UpdateClientByAccountNumber(AccountNumber, vClinte);
}

void ShowAddNewClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Client Screen";
    cout << "\n-----------------------------------\n";
    AddNewClient();
}

void ShowFindClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector <stCantrle> vClinte = LoadCleintsDataFromFile(FileNameCantrale);
    stCantrle Clinte;
    string AccountNumber = ReadClientAccountNumbe();
    if (FindClientByAccountNumbe(AccountNumber, vClinte, Clinte))
    {
        PrintClientCard(Clinte);
    }
    else
    {
        cout << "\nClient with Account Number [" << AccountNumber << "] is not found!";
    }
}

void ShowEndScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}
void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    stCantrle Client;
    vector <stCantrle> vClients = LoadCleintsDataFromFile(FileNameCantrale);
    string AccountNumber = ReadClientAccountNumbe();
    while (!FindClientByAccountNumbe(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does notexist.\n";
            AccountNumber = ReadClientAccountNumbe();
    }
    PrintClientCard(Client);
    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount,
        vClients);
}
void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";
    stCantrle Client;
    vector <stCantrle> vClients =
        LoadCleintsDataFromFile(FileNameCantrale);
    string AccountNumber = ReadClientAccountNumbe();
    while (!FindClientByAccountNumbe(AccountNumber, vClients,
        Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = ReadClientAccountNumbe();
    }
    PrintClientCard(Client);
    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;
    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
            cout << "Please enter another amount? ";
        cin >> Amount;
    }
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount *
        -1, vClients);
}
void ShowTotalBalancesScreen()
{
    ShowTotalBalance();
}

enum enMainMenueOptions {
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eTransactions = 6,eExit = 7
};
enum enMenueTransactions {
    eDeposit = 1, eWithdraw = 2,
    eTotalBalances = 3, eMainMenue = 4,
    
};
void GoBackTransactions() {
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMenueTransactions();
}
void GoBackToMainMenu() {
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}
short ReadMenueTransactions() {
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
short ReadMainMenueOptio() {
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
void PerfromMenueTransactions(enMenueTransactions eMenueTransactions) {
    switch (eMenueTransactions)
    {
    case enMenueTransactions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackTransactions();
        break;
    }
       
    case enMenueTransactions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackTransactions();
        break;
    }
        
    case enMenueTransactions::eTotalBalances:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackTransactions();
        break;
    }
        
    case enMenueTransactions::eMainMenue:
    {
        ShowMainMenue();
        break;
    }
    }
    
   
    
}
void ShowMenueTransactions()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\t Menue Transactions Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Blanaces.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromMenueTransactions((enMenueTransactions)ReadMenueTransactions());
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOptions) {
    switch (MainMenueOptions)
    {
    case enMainMenueOptions::eListClients:
        system("cls");
        ShowAllClientsScree();
        GoBackToMainMenu();
        break;
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenu();
        break;
        case enMainMenueOptions::eTransactions:
        system("cls");
        ShowMenueTransactions();
        break;
    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;
    }
}


void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOptio());
}

int main()
{
    ShowMainMenue();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
