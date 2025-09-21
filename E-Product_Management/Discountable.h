#ifndef DISCOUNTABLE_H
#define DISCOUNTABLE_H

using namespace std;

class Discountable {
public:
    virtual double applyDiscount(double rate) = 0;
    virtual ~Discountable() = default;
};

#endif
