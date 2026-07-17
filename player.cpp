#include "player.h"
#include <iostream>


Player::Player() {
    name = "Farmer"; energy = 10; maxEnergy = 10; money = 100;
    currentLocation = "Farm"; inventoryCount = 0;
}

Player::Player(string playerName) {
    name = playerName; energy = 10; maxEnergy = 10; money = 100;
    currentLocation = "Farm"; inventoryCount = 0;
}

string Player::getName()
{
    return name; 
}

int Player::getEnergy()
{
    return energy;
}

void Player::changeEnergy(int amount)
{
    energy += amount;
    if(energy > maxEnergy){
        energy = maxEnergy;
    }
    if(energy < 0){
        energy = 0;
    }

}

int Player::getMoney(){
    return money; 
}

void Player::changeMoney(int amount){
     money += amount;
}

string Player::getCurrentLocation(){
    return currentLocation;
}

void Player::setLocation(string newLocation){
    currentLocation = newLocation;
}

bool Player::addItem(Item item) {
    if (inventoryCount >= 10) {
        cout << "Inventory Full!" << endl;
        return false;
    }
    inventory[inventoryCount] = item;
    inventoryCount++;
    return true;
}

void Player::removeItem(int index) {
    if(index < 0 || index >= inventoryCount){
        return;
    }
    for(int i = index; i < inventoryCount - 1; i++){
        inventory[i] = inventory[i + 1];
    }
    inventoryCount--;
}

void Player::displayInventory(){
    cout << "--- Inventory ---" << endl;
    if (inventoryCount == 0){
        cout << "Empty" << endl;
    }
    else{
        for(int i = 0; i < inventoryCount; i++){
            cout << i + 1 << ". " << inventory[i].getName() << " (" << inventory[i].getType() << ")" << endl;
        }
    }
}

int Player::getInventoryCount(){
     return inventoryCount;
}

Item Player::getItem(int index){
    return inventory[index];
}