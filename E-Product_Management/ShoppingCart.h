#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "InventoryList.h"
#include "Product.h"

using namespace std;

class ShoppingCart : public Discountable {
private:
    InventoryList<Product*> products;
    double total;

public:
    ShoppingCart();
    ~ShoppingCart();

    ShoppingCart& operator+=(Product* p);

    bool removeProduct(Product* p);

    double calculateTotal() const;
    virtual double applyDiscount(double rate) override;

    void printCart() const;
    size_t size() const;
};

#endif
