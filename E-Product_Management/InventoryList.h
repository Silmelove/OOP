#ifndef INVENTORYLIST_H
#define INVENTORYLIST_H

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
class InventoryList {
private:
    vector<T> items;

public:
    void add(const T& it) { items.push_back(it); }

    bool remove(const T& it) {
        auto itpos = find(items.begin(), items.end(), it);
        if (itpos == items.end()) return false;
        items.erase(itpos);
        return true;
    }

    size_t size() const { return items.size(); }
    T at(size_t i) const { return items.at(i); }
    void clear() { items.clear(); }

    void printAll() const {
        cout << "InventoryList contents (" << items.size() << "):\n";
        for (const auto& it : items) {
            if constexpr (is_pointer<T>::value) {
                if (it) it->print();
            }
            else {
                it.print();
            }
        }
    }
};

#endif
