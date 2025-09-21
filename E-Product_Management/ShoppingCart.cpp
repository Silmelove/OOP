#include "ShoppingCart.h"

ShoppingCart::ShoppingCart() : total(0.0) {}
ShoppingCart::~ShoppingCart() { products.clear(); }

ShoppingCart& ShoppingCart::operator+=(Product* p) {
    if (!p) {
        cout << "[Cart] Null product cannot be added.\n";
        return *this;
    }
    if (p->getStock() <= 0) {
        cout << "[Cart] Product " << p->getId() << " is out of stock. Cannot add.\n";
        return *this;
    }
    products.add(p);
    p->updateStock(-1);
    total = calculateTotal();
    cout << "[Cart] Added product " << p->getId() << " to cart.\n";
    return *this;
}

bool ShoppingCart::removeProduct(Product* p) {
    if (!p) return false;
    bool ok = products.remove(p);
    if (ok) {
        p->updateStock(1);
        total = calculateTotal();
    }
    return ok;
}

double ShoppingCart::calculateTotal() const {
    double s = 0.0;
    for (size_t i = 0; i < products.size(); ++i) {
        Product* p = products.at(i);
        if (p) s += p->getPrice();
    }
    return s;
}

double ShoppingCart::applyDiscount(double rate) {
    double before = calculateTotal();
    if (rate < 0 || rate > 1) return before;
    double after = before * (1 - rate);
    total = after;
    return after;
}

void ShoppingCart::printCart() const {
    cout << "----- Shopping Cart (" << products.size() << " items) -----\n";
    products.printAll();
    cout << "Total: $" << calculateTotal() << "\n";
}

size_t ShoppingCart::size() const { return products.size(); }
