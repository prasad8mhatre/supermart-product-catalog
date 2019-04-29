#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

class Signup{
    public:
      Signup(){

      };

      void signup()
      {
          string name;
          string address;
          int randomNumber = (rand() % 10000) + 1;
          string walmartId = to_string(randomNumber) + "";
          string line;
          cout << "==========================================================================\n";
          cout << "1.Signup\n";
          cout << "==========================================================================\n";
          cout << "What is your name? \n";
          cin >> name;
          cout << "Where do you stay?\n ";
          cin >> address;
          cout << "==========================================================================\n";
          cout << "name:" << name << "\naddress:" << address << "\nwalmartId:" << walmartId;
          cout << "\nUser Successfully Signup !, Go and login for shopping\n";
          cout << "==========================================================================\n";

          string val = "\n\"" + name + "\", \"" + address + "\", \"" + walmartId + "\", 0";
          apendToFile("buyers.csv", val);
    }

    void apendToFile(string filename, string key)
    {
        ofstream a_file(filename, std::ios_base::app);
        a_file << key;
        a_file.close();
    }
};