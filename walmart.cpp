#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <list>
#include <iterator>
#include<random>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include "goods.h"
#include "storage.cpp"
#include "signup.cpp"
#include "shopping.cpp"
#include <windows.h>
#include <cwchar>
#define RED "\033[31m" /* Red */
#define RESET "\033[0m"
using namespace std;

void admin();

void addLine(Inventory* inventory);
void addCategory(Inventory* inventory);
void addProduct(Inventory* inventory);
void watchInvertory();
void watchLine(Inventory *inventory);
void watchCategory(Inventory *inventory);
void removeProductFromInvertory();
void report();


string random_string(size_t);
int searchInfileForPresence(string fileName, string key);
void printFile(string filename);
void removeLineFromFile(string fileName, int lineNumber);
void printReceipt(llist *cart, double totalPrice);
string findProduct(string product);
string searchInfile(string file, string product);

int main()
{
    Signup sign;
    Shopping shop;
    while(true)
    {
        int mainOption = 0;
        cout << RED << "\n==========================Walmart Mini store===============================\n"
             << RESET;
        cout << RED << "\n\n==========================================================================\n"<< RESET;
        cout << RED << "1.Signup|";
        cout << RED << "2.Login|";
        cout << RED << "3.Admin|";
        cout << RED << "4.Exit|";
        cout << "\n==========================================================================\n";
        cout << "Enter Option\n";
        cin >> mainOption;
        switch (mainOption)
        {
        case 1:
            sign.signup();
            break;
        case 2:
            shop.loginUser();
            break;
        case 3:
            admin();
            break;
        case 4:
            exit(0);
            break;
        default :
            cout<<"Invalid input\n";
            break;
        }
    }

}





void admin()
{
    int menuOption = 0;
    Inventory inventory;
    while (1)
    {
        cout << "\n==========================================================================\n";
        cout << "Administration\n";
        cout << "==========================================================================\n";
        cout << "Administration Menu:\n";
        cout << "1. Add Line\n";
        cout << "2. Add Category\n";
        cout << "3. Add Goods\n";
        cout << "4. Watch line list\n";
        cout << "5. Watch Category list\n";
        cout << "6. Watch Goods list\n";
        cout << "7. Remove Goods\n";
        cout << "8. Report\n";
        cout << "9. Go back\n";
        cout << "==========================================================================\n";
        cin >> menuOption;

        switch (menuOption)
        {
        case 1:
            addLine(&inventory);
            break;
        case 2:
            addCategory(&inventory);
            break;
        case 3:
            addProduct(&inventory);
            break;
        case 4:
            watchLine(&inventory);
            break;
        case 5:
            watchCategory(&inventory);
            break;
        case 6:
            watchInvertory();
            break;
        case 7:
            removeProductFromInvertory();
            break;
        case 8:
            report();
            break;
        case 9:
            goto EndWhile;
        default:
            cout << "Invalid input\n";
            break;
        }
    }
EndWhile:
    ;
}


void addLine(Inventory* inventory){
    inventory->addLine();
}

void addCategory(Inventory* inventory){
    inventory->addCategory();
}

void addProduct(Inventory* inventory)
{
    inventory->addGoods();
}

void watchLine(Inventory *inventory)
{
    inventory->watchLine();
}

void watchCategory(Inventory *inventory)
{
    string name;
    cout<<"\n Enter Line name:";
    cin>>name;
    inventory->watchCategory(name);
}

void watchInvertory()
{
    printFile("assets.csv");
}
void removeProductFromInvertory()
{
    string product;
    cout << "Enter Goods name:\n";
    cin >> product;
    int lineNumber = searchInfileForPresence("assets.csv", product);
    removeLineFromFile("assets.csv", lineNumber);
}
void report()
{
    printFile("paybook.txt");
}





void printFile(string filename)
{
    ifstream readFile(filename);
    string line;
    cout << "\n\n\n\n\n==========================================================================\n";
    cout<<"Administrator\n";
    while (getline(readFile, line))
    {
        cout << "==========================================================================\n";
        cout<<line<<"\n";
    }
    cout << "\n==========================================================================\n\n\n\n";
}

int searchInfileForPresence(string fileName, string key)
{
    ifstream readFile(fileName);
    string line;
    int pos;
    int i = 0;
    int position = -1;
    while (getline(readFile, line))
    {

        pos = line.find(key);
        if (pos != string::npos)
        {
            position = i;
        }
        i++;
    }
    return position;
}



void removeLineFromFile(string fileName, int lineNumber)
{
    string line;
    int i = 0;

    ifstream fin;
    fin.open(fileName);
    ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        if(i != lineNumber)
        {
            temp << line << endl;
        }
        i++;
    }

    temp.close();
    fin.close();
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());
}
