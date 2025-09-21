#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "Product.h"

using namespace std;

class Order {
private:
    int orderId;
    vector<Product*> items;
    double total;

public:
    Order(int id = 0);
    ~Order();

    void addItem(Product* p);
    void calculateTotal();
    void printOrder() const;
};

#endif
