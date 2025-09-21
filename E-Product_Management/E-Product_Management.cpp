#include <iostream>
#include <iomanip>
#include "Product.h"
#include "Electronics.h"
#include "ShoppingCart.h"
#include "InventoryList.h"
#include "Order.h"

using namespace std;

int main() {
    cout << "\n========================================\n";
    cout << "   E-commerce Assignment - Student Demo   \n";
    cout << "========================================\n\n";

    InventoryList<Product*> inventory;

    Product* p1 = new Product(1, "Notebook", 2.5, 10);
    Electronics* e1 = new Electronics(2, "USB-C Charger", 15.0, 5, 2.0);
    Product* p2 = new Product(3, "Pen", 1.0, 0);

    inventory.add(p1);
    inventory.add(e1);
    inventory.add(p2);

    cout << ">>> Initial Inventory:\n";
    cout << "----------------------------------------\n";
    inventory.printAll();
    cout << "----------------------------------------\n\n";

    ShoppingCart cart;
    cout << ">>> Adding items to cart...\n";
    cart += p1;
    cart += e1;
    cart += p2;  
    cout << endl;

    cart.printCart();

    cout << ">>> Operator == check:\n";
    Product anotherP1(1, "Notebook copy", 2.5, 1);
    if (*p1 == anotherP1) {
        cout << "Products p1 and anotherP1 are considered EQUAL by ID.\n";
    }
    else {
        cout << "Products p1 and anotherP1 are DIFFERENT.\n";
    }
    cout << endl;

    cout << ">>> Applying 10% discount to cart...\n";
    double newTotal = cart.applyDiscount(0.1);
    cout << "Cart total after discount: $"
        << fixed << setprecision(2) << newTotal << "\n\n";

    cout << ">>> Creating Order #1001\n";
    Order order1(1001);
    order1.addItem(p1);
    order1.addItem(e1);
    order1.calculateTotal();
    order1.printOrder();
    cout << endl;

    cout << ">>> Restocking electronics (+3)...\n";
    e1->updateStock(3);
    e1->print();
    cout << endl;

    delete p1;
    delete e1;
    delete p2;

    cout << "========================================\n";
    cout << "            End of Demo                  \n";
    cout << "========================================\n";
    return 0;
}
