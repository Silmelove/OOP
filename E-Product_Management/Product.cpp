#include "Product.h"

Product::Product(int id, const string& name, double price, int stock)
    : id(id), name(name), price(price), stock(stock) {}

Product::~Product() {}

int Product::getId() const { return id; }
string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

void Product::setPrice(double p) { if (p >= 0) price = p; }
void Product::setStock(int s) { if (s >= 0) stock = s; }

void Product::updateStock(int delta) {
    if (stock + delta < 0) {
        cout << "[Product] Not enough stock to reduce by " << -delta << " for product " << id << "\n";
        return;
    }
    stock += delta;
}

double Product::applyDiscount(double rate) {
    if (rate < 0 || rate > 1) return price;
    return price * (1 - rate);
}

void Product::print() const {
    cout << "Product[" << id << "] " << name << " - $" << price << " - stock: " << stock << '\n';
}

bool Product::operator==(const Product& other) const {
    return this->id == other.id;
}
