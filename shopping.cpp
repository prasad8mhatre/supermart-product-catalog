#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include "cart.cpp"
using namespace std;

class Shopping{
    public:
    Shopping(){}
    void loginUser()
    {
        int menuOption = 0;
        string name;
        string address;
        llist cart;

        cout << "==========================================================================\n";
        cout << "2.Login\n";
        cout << "==========================================================================\n";
        cout << "What is your name? \n";
        cin >> name;
        //search in file
        if (searchInfileForPresence("buyers.csv", name) != -1)
        {
            cout << "\n==========================================================================\n";
            cout << "\nUser Logined!\n";
            cout << "\n==========================================================================\n";
            while (1)
            {
                cout << "\n==========================================================================\n";
                cout << "Start shopping\n";
                cout << "==========================================================================\n";
                cout << "Shopping Menu:\n";
                cout << "1. Search Product\n";
                cout << "2. Buy product\n";
                cout << "3. Watch shopping cart\n";
                cout << "4. Remove Product\n";
                cout << "5. Checkout\n";
                cout << "6. Go back\n";
                cout << "**************************************************************\n";
                cin >> menuOption;

                switch (menuOption)
                {
                case 1:
                    searchProduct();
                    break;
                case 2:
                    buyProduct(&cart);
                    break;
                case 3:
                    watchShoppingCart(&cart);
                    break;
                case 4:
                    removeProduct(&cart);
                    break;
                case 5:
                    checkout(&cart);
                    break;
                case 6:
                    goto EndWhile;
                default:
                    cout << "Invalid input\n";
                    break;
                }
            }
        }
        else
        {
            cout << "\nLog in failed! No user found";
        }
    EndWhile:;
    }

    void searchProduct()
    {
        string product;
        cout << "Enter the product";
        cin >> product;
        string line = findProduct(product);
        cout << "\nProduct details";
        cout << "\n-==========================================================================\n";
        cout << "line,category, productId, product,best-before-date, price, qty\n";
        cout << line;
    }

    string findProduct(string product)
    {
        string line = searchInfile("assets.csv", product);
        return line;
    }
    void buyProduct(llist *cart)
    {
        int productId, qty;
        cout << "Enter productId:";
        cin >> productId;
        cout << "Enter quantity:";
        cin >> qty;
        //search for product in list
        //create product object
        string line = findProduct(to_string(productId));
        char *pch;
        char *cstr = &line[0u];
        pch = strtok(cstr, ",");
        int i = 0;
        string prod, bbd;
        double price, pid, totalQty;

        while (pch != NULL)
        {
            if (i == 2)
            {
                sscanf(pch, "%lf", &pid);
            }
            else if (i == 3)
            {
                prod = pch;
            }
            else if (i == 4)
            {
                bbd = pch;
            }
            else if (i == 5)
            {
                sscanf(pch, "%lf", &price);
            }
            else if (i == 6)
            {
                sscanf(pch, "%lf", &totalQty);
            }
            i++;
            pch = strtok(NULL, ",");
        }
        if (totalQty < qty)
        {
            cout << "Qty exceeds the stock";
        }
        else
        {
            Goods a(pid, prod, bbd, price, qty);
            cart->insert_start(a);
        }
    }
    void watchShoppingCart(llist *cart)
    {
        cart->display();
    }
    void removeProduct(llist *cart)
    {
        int productId, pos = 1;
        cout << "Enter productId:";
        cin >> productId;

        pos = cart->find(productId);
        if (pos == 1)
        {
            cart->delete_first();
        }
        else
        {
            cart->delete_position(pos);
        }
    }
    void checkout(llist *cart)
    {
        watchShoppingCart(cart);
        string clubId;
        int clubPoints;
        cout << "\n==========================================================================";
        cout << "\nEnter WalmartId:";
        cin >> clubId;
        //find in file and get clubpoints
        string line = searchInfile("buyers.csv", clubId);
        char *pch;
        char *cstr = &line[0u];
        pch = strtok(cstr, ",");
        int i = 0;
        while (pch != NULL)
        {
            if (i == 3)
            {
                sscanf(pch, "%lf", &clubPoints);
            }

            i++;
            pch = strtok(NULL, ",");
        }

        double totalPrice = cart->computeFinalPrice();
        if (clubPoints > 100)
        {
            totalPrice = totalPrice - (totalPrice * 0.10);
            clubPoints = clubPoints - 100;
        }
        else
        {
            clubPoints += totalPrice;
        }
        //update in file
        cart->updateInFile(totalPrice);

        printReceipt(cart, totalPrice);
        cart->delete_all();
    }

    void printReceipt(llist *cart, double totalPrice)
    {
        watchShoppingCart(cart);
        cout << "\n==========================================================================";
        cout << "\n Checkout completed!";
        cout<<"\nThank you for shopping with us, Visit again!";
        cout << "\nTotal price: " << totalPrice;
        cout << "\n==========================================================================";
    }

    string searchInfile(string fileName, string key)
    {
        ifstream readFile(fileName);
        string line;
        int pos;
        int i = 0;
        string foundLine;
        while (getline(readFile, line))
        {

            pos = line.find(key);
            if (pos != string::npos)
            {
                foundLine = line;
            }
            i++;
        }
        return foundLine;
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
};