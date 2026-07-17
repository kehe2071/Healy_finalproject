#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item{
private:
    string name;
    string type;
    int energyRestored;
    bool isDonated;

public:
    Item();
    Item(string itemName, string itemType, int energy);

    string getName();
    string getType();
    int getEnergy();
};

#endif