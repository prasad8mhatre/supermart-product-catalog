#include "goods.h"
#include <iostream>
using namespace std;

Goods::Goods(int id, string n, string b, double p, double qty)
{
    name = n;
    bbd = b;
    price = p;
    quantity = qty;
    goodsId = id;
}

Goods::Goods()
{
    
}

string Goods::getName(){
    return name;
}
string Goods::getBBD(){
    return bbd;
}
double Goods::getPrice(){
    return price;
}
double Goods::getQuantity()
{
    return quantity;
}

int Goods::getGoodsId()
{
    return goodsId;
}
