#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "item.h"

using namespace std;

class Player {
private:
    string name;
    int energy;
    int maxEnergy;
    int money;
    string currentLocation;
    
    Item inventory[10];
    int inventoryCount;

public:
    Player();
    Player(string playerName);

    string getName();
    int getEnergy();
    void changeEnergy(int amount);
    int getMoney();
    void changeMoney(int amount);
    string getCurrentLocation();
    void setLocation(string newLocation);

    bool addItem(Item item);
    void removeItem(int index);
    void displayInventory();
    int getInventoryCount();
    Item getItem(int index);
};

#endif