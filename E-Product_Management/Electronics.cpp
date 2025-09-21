#include "Electronics.h"

Electronics::Electronics(int id, const string& name, double price, int stock, double warrantyYears)
    : Product(id, name, price, stock), warrantyYears(warrantyYears) {}

Electronics::~Electronics() {}

double Electronics::getWarranty() const { return warrantyYears; }
void Electronics::setWarranty(double y) { if (y >= 0) warrantyYears = y; }

void Electronics::updateStock(int delta) {
    if (delta > 0) {
        int effectiveDelta = delta - 1;
        if (effectiveDelta < 0) effectiveDelta = 0;
        Product::updateStock(effectiveDelta);
        cout << "[Electronics] Applied handling loss 1 when restocking.\n";
    }
    else {
        Product::updateStock(delta);
    }
}

void Electronics::print() const {
    cout << "Electronics[" << id << "] " << name << " - $" << price
        << " - stock: " << stock << " - warranty: "
        << warrantyYears << " years\n";
}
