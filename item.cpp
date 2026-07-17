#include "item.h"

Item::Item() {
    name = "Trash";
    type = "Forage Item";
    energyRestored = 0;
    isDonated = false;
}

Item::Item(string itemName, string itemType, int energy){
    name = itemName;
    type = itemType;
    energyRestored = energy;
    isDonated = false;
}

string Item::getName(){
    return name;
}

string Item::getType(){
    return type;
}

int Item::getEnergy(){
    return energyRestored;
}