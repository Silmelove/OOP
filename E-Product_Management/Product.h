#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include "Discountable.h"

using namespace std;

class Product : public Discountable {
protected:
    int id;
    string name;
    double price;
    int stock;

public:
    Product(int id = 0, const string& name = "", double price = 0.0, int stock = 0);
    virtual ~Product();

    int getId() const;
    string getName() const;
    double getPrice() const;
    int getStock() const;

    void setPrice(double p);
    void setStock(int s);

    virtual void updateStock(int delta);

    virtual double applyDiscount(double rate) override;

    virtual void print() const;

    bool operator==(const Product& other) const;
};

#endif
