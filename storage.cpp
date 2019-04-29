#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "goods.h"

struct node
{
    Goods data;
    node *next;
};

struct Category
{
    string categoryName;
    node *products;
    Category *next;
    Category *prev;
};

struct Line
{
    string lineName;
    Category *categories;
    Line *next;
};

class Inventory{
    private:
    Line *head, *tail;
    public:
      Inventory()
      {
          head = NULL;
          tail = NULL;
      }

      void watchLine(){
          Line *temp = new Line;
          temp = head;
          while (temp != NULL)
          {
              cout<< "line:" <<temp->lineName;
              temp = temp->next;
          }
      }

      void watchCategory(string lineName){
          Line *temp = new Line;
          temp = head;
          while (temp != NULL)
          {
              if(temp->lineName == lineName){
                  Category *tempCat = new Category;
                  tempCat = temp->categories;
                  while(tempCat != NULL){
                      cout<<"\ncategory:" << tempCat->categoryName;
                      tempCat = tempCat->next;
                  }
              }
              temp = temp->next;
          }
      }

      void watchProduct(){

      }

      void addLine(){
        cout<<"\n==========================================================================";
        cout<<"\nAdd line";
        cout << "\n==========================================================================";
        string name;
        cout<<"\nEnter Line name:";
        cin>>name;

        Line *line = new Line;
        line->categories = NULL;
        line->next=NULL;
        line->lineName = name;

        if (head == NULL)
        {
            head = line;
            tail = line;
            line = NULL;
        }
        else
        {
            tail->next = line;
            tail = line;
        }
      }

      void addCategory(){
          cout << "\n==========================================================================";
          cout<<"\nAdd Category";
          cout << "\n==========================================================================";

          string name;
          string lineName;
          cout << "\nEnter Line name:";
          cin>>lineName;
          cout << "\nEnter Category name:";
          cin>>name;
          cout<<"Searching in line";
          int pos = searchLine(lineName);
          if( pos != -1){
              Line *temp = new Line;
              temp = head;
              int i =1 ;
              while (temp != NULL)
              {
                  if (pos == i)
                  {
                      Category *cat = new Category;
                      cat->products = NULL;
                      cat->next = NULL;
                      cat->categoryName = name;
                      if(temp->categories == NULL){
                          cat->prev = NULL;
                          temp->categories = cat;
                      }else{
                          temp->categories->next = cat;
                          cat->prev = temp->categories;
                      }
                  }
                  temp = temp->next;
                  i++;
              }
          }else{
              cout<<"Line not found!";
          }

      }

      void addGoods()
      {
          cout<<"\n==========================================================================";
          cout<<"\nAdd Product";
          cout << "\n==========================================================================";
          string name;
          string lineName, categoryName, goodsName;
          cout << "\nEnter line name:";
          cin>>lineName;
          cout << "\nEnter category name:";
          cin>>categoryName;
          cout<<"\n---------\nsearching for line";

          int pos = searchLine(lineName);
          if (pos != -1)
          {
              Line *temp = new Line;
              temp = head;
              int i = 1;
              while (temp != NULL)
              {
                  if (pos == i)
                  {
                      int y= 1;
                      int catPos = searchCategoryInLine(lineName, categoryName);
                      Category *tempCat = new Category;
                      tempCat = temp->categories;
                      if(catPos != -1){
                        while (tempCat != NULL)
                        {
                            if (y == catPos)
                            {

                                node *product = new node;
                                product = tempCat->products;

                                string bbd;
                                int productId;
                                double price, qty;
                                cout<<"\nEnter goodsId";
                                cin>>productId;
                                cout << "\nEnter Product name:";
                                //getline(cin, name);
                                cin >> goodsName;
                                cout << "\nEnter bbd name:";
                                //getline(cin, bbd);
                                cin>>bbd;
                                cout<<"\nEnter price:";
                                cin>>price;
                                cout<<"\n Enter qty:";
                                cin>>qty;
                                Goods a(productId, goodsName, bbd, price, qty);
                                if(product == NULL){
                                    node *newnode = new node;
                                    newnode->data = a;
                                    newnode->next =NULL;
                                    tempCat->products = newnode;
                                }else{
                                    node *current = new node;
                                    node *previous = new node;
                                    node *newnode = new node;
                                    current = product;
                                    previous = product;
                                    while(current != NULL){
                                        previous=current;
                                        current = current->next;

                                    }
                                    newnode->data = a;
                                    newnode->next = NULL;
                                    previous->next = newnode;
                                }
                                string content = "\n\"" + lineName + "\", \"" + categoryName + "\"," +
                                                 to_string(productId) + ", \"" + goodsName + "\", \"" +
                                                 bbd + "\"," + to_string(price) + +", " + to_string(qty);

                                addToFile("assets.csv", content);

                            }
                            y++;
                            tempCat = tempCat->next;
                        }
                      }
                      else
                      {
                          cout << "Category not found!";
                      }
                  }
                  temp = temp->next;
                  i++;
              }
          }
          else
          {
              cout << "Line not found!";
          }
      }

      void addToFile(string filename, string key)
        {
            ofstream a_file(filename, std::ios_base::app);
            a_file << key;
            a_file.close();
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
      int searchLine(string lineName){
          //cout << "in searchLine ";
          Line *temp = new Line;
          temp = head;
          int pos = -1;
          int i=1;
          //cout<<"starting search";
          while (temp != NULL)
          {
              //cout<<"temp:" << temp ->lineName;
              if(temp->lineName == lineName){
                  pos = i;
              }
              temp = temp->next;
              i++;
          }
          //cout << "in searchLine pos:" + pos ;
          return pos;
      }

      int searchCategoryInLine(string lineName, string categoryName)
      {
          //cout<<"in searchCategoryInLine ";
          Line *temp = new Line;
          temp = head;
          int pos = -1;
          int i = 1;
          while (temp != NULL)
          {
              if (temp->lineName == lineName)
              {
                  Category *tempCat = new Category;
                  tempCat = temp ->categories;
                  while(tempCat != NULL){
                      if (tempCat->categoryName == categoryName){
                          pos = i;
                      }
                      i++;
                      tempCat = tempCat->next;
                  }
              }
              temp = temp->next;
          }
          //cout<<"pos of cate:" + pos;
          return pos;
      }


    void displayInvertory(){
        cout<<"\n==========================================================================";
        cout<<"\n Display Inventory";
        cout << "\n==========================================================================";
        Line *temp=new Line;
        temp = head;
        while (temp != NULL)
        {
            cout<<"\nLine:" << temp->lineName;
            Category *cat = new Category;
            cat = temp->categories;
            while( cat != NULL){
                cout<<"\n line :" << temp->lineName << " Category:" << cat->categoryName;
                node *product = new node;
                product = cat->products;
                while(product != NULL){

                    cout<<"\n";
                    cout << "Name:" << product->data.getName() << "\t";
                    cout << "GoodsId:" << product->data.getGoodsId() << "\t";
                    cout << "Price:" << product->data.getPrice() << "\t";
                    cout << "Quantity:" << product->data.getQuantity() << "\t";
                    cout << "Best Before Date:" << product->data.getBBD() << "\t";
                    product = product-> next;
                }
                cat = cat->next;
            }
            temp = temp->next;
        }
    }
    void removeFromInvertory(string lineName, string categoryName, int productId){
        int pos = searchForProduct(lineName, categoryName, productId);
        if(pos == 1){
            delete_first(lineName,categoryName);
        }else{
            delete_position(lineName,categoryName, pos);
        }
        int lineNumber = searchInfileForPresence("assets.csv", to_string(productId));
        removeLineFromFile("assets.csv", lineNumber);
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

    int searchForProduct(string lineName, string categoryName, int productId){
      Line *temp = new Line;
      temp = head;
      int pos = -1;
      int i = 1;
      while (temp != NULL)
      {
          if (temp->lineName == lineName){
              Category *tempCat = new Category;
              tempCat = temp ->categories;
              while(tempCat != NULL){
                  if (tempCat->categoryName == categoryName){
                      node *product = new node;
                      product = tempCat->products;
                      while(product!=NULL){
                        if(product->data.getGoodsId() == productId){
                            pos=i;
                        }
                        product = product ->next;
                        i++;
                      }
                  }
                  tempCat = tempCat->next;
              }
          }

          temp = temp->next;
      }
      //cout<<"pos of cate:" + pos;
      return pos;
    }

    void delete_first(string lineName, string categoryName)
    {
          Line *temp = new Line;
          temp = head;
          int pos = -1;
          int i = 1;
          while (temp != NULL)
          {
              if (temp->lineName == lineName){
                  Category *tempCat = new Category;
                  tempCat = temp ->categories;
                  while(tempCat != NULL){
                      if (tempCat->categoryName == categoryName){
                          node *product = new node;
                          product = tempCat->products;
                          tempCat->products = tempCat->products->next;
                          delete product;
                      }
                      tempCat = tempCat->next;
                  }
              }

              temp = temp->next;
          }


    }

    void delete_position(string lineName, string categoryName, int pos)
    {

        Line *temp = new Line;
          temp = head;
         int i = 1;
          while (temp != NULL)
          {
              if (temp->lineName == lineName){
                  Category *tempCat = new Category;
                  tempCat = temp ->categories;
                  while(tempCat != NULL){
                      if (tempCat->categoryName == categoryName){

                        node *current=new node;
                        node *previous=new node;
                        current=tempCat->products;
                        for(int i=1;i<pos;i++)
                        {
                            previous=current;
                            current=current->next;
                        }
                        previous->next=current->next;

                      }
                      tempCat = tempCat->next;
                  }
              }

              temp = temp->next;
          }


    }
};
