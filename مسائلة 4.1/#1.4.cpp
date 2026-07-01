// #1.4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <string>
using namespace std;

string NumberToTixt(int Number) {
    if (Number == 0) 
        return "";
    if (Number >= 1 && Number <= 19)
    {
        string arr[]=  {"", "One", "Two", "Three", "Four", "Five", "Six", "Eight", "Nine","Ten",
            "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
        return  arr[Number] + " ";
    }
    if (Number >= 20 && Number <= 99)
    {
        string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
        return arr[Number / 10] + " " + NumberToTixt(Number % 10);
    }
    if (Number >= 100 && Number <= 199) {
        return "One Hundred " + NumberToTixt(Number % 100);
    }
    if (Number >= 200 && Number <= 999)
    {
        return NumberToTixt(Number / 100) + "Hundred " + NumberToTixt(Number % 100);
    }
    if (Number >= 1000 && Number <= 1999)
    {
        return "One Thousand " + NumberToTixt(Number % 1000);
    }
    if (Number >= 2000 && Number <= 999999)
    {
        return NumberToTixt(Number / 1000) + "Thousand " + NumberToTixt(Number % 1000);
    }
    if (Number >= 1000000 && Number <= 1999999)
    {
        return "One Million " + NumberToTixt(Number % 1000000);
    }
    if (Number >= 2000000 && Number <= 9999999)
    {
        return NumberToTixt(Number / 1000000) + "Million" + NumberToTixt(Number % 1000000);
    }
    if (Number >= 1000000000 && Number <= 199999999)
    {
        return "One Billion" + NumberToTixt(Number % 1000000000);
    }
    else
    {
        return NumberToTixt(Number / 1000000000) + "Billion" + NumberToTixt(Number % 1000000000);
    }
  
    

}

int ReadNumber() {
    int Num;
    cout << "Plaes Enter Number ?";
    cin >> Num;
    return Num;
}

int main()
{
    int Number = ReadNumber();
    cout << NumberToTixt(Number) << endl;
    system("pause>0");
   
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
