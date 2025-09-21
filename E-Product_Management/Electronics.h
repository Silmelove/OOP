#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"

using namespace std;

class Electronics : public Product {
private:
    double warrantyYears;

public:
    Electronics(int id = 0, const string& name = "", double price = 0.0, int stock = 0, double warrantyYears = 1.0);
    virtual ~Electronics();

    double getWarranty() const;
    void setWarranty(double y);

    virtual void updateStock(int delta) override;
    virtual void print() const override;
};

#endif
