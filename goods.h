#ifndef GOODS_H
#define GOODS_H
#include <iostream>
#include <string>
using namespace std;

class Goods
{
  private:
    int goodsId;
    string name;
    string bbd;
    double price;
    double quantity;

  public:
    Goods();
    Goods(int goodsId, string name, string bbd, double price, double quantity);
    string getName();
    string getBBD();
    double getPrice();
    double getQuantity();
    int getGoodsId();
};

#endif