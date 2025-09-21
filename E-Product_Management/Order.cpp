#include "Order.h"

Order::Order(int id) : orderId(id), total(0.0) {}
Order::~Order() { items.clear(); }

void Order::addItem(Product* p) {
    if (!p) return;
    items.push_back(p);
}

void Order::calculateTotal() {
    total = 0.0;
    for (auto p : items) if (p) total += p->getPrice();
}

void Order::printOrder() const {
    cout << "=== Order " << orderId << " ===\n";
    for (auto p : items) if (p) p->print();
    cout << "Order total: $" << total << "\n";
}
