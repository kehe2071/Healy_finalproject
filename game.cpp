#include "play.h"
#include <iostream>

Game::Game() {
    currentDay = 1;
    maxDays = 7;
    jojaInfluence = 0;
    
    bundleNames[0] = "Crop"; 
    bundleNames[1] = "Fish";
    bundleNames[2] = "Mineral";
    bundleNames[3] = "Animal Product";
    bundleNames[4] = "Forage Item";
    for(int i = 0; i < 5; i++){
        bundleChecks[i] = false;
    }

    npcs[0] = Character("Lewis", "Checks progress");
    npcs[1] = Character("Willy", "Helps catch rare fish");
    npcs[2] = Character("Clint", "Helps find rare minerals");
    npcs[3] = Character("Marnie", "Trades for food");

    locations[0] = "Farm";
    locations[1] = "Town Square";
    locations[2] = "Beach";
    locations[3] = "Mines";
    locations[4] = "JojaMart";
}

void Game::displayEnding() {
    if (checkWin()) {
        cout << "==============================================" << endl;
        cout << "           Community Center fixed!            " << endl;
        cout << "==============================================" << endl;
    }
    else{
        cout << "==============================================" << endl;
        cout << "                   GAME OVER                  " << endl;
        cout << "==============================================" << endl;
        cout << "The season ended before the bundle was finished" << endl;
    }
}

void Game::displayDashboard(){
    cout << "==================================================" << endl;
    cout << "            THE FINAL BUNDLE (Day " << currentDay << " " << maxDays << endl;
    cout << "==================================================" << endl;
    cout << "Farmer: " << player.getName() << " Energy: " << player.getEnergy() << " Money: " << player.getMoney() << " gold" << endl;
    cout << "Current Location: " << player.getCurrentLocation() << endl;
    cout << "Joja Influence: " << jojaInfluence << endl;
    
    int count = 0;
    for(int i = 0; i < 5; i++){
        if(bundleChecks[i]){
            count++;
        }    
    }
    cout << "Bundle Progress: " << count << " Items Donated" << endl;
    displayMap();
}

void Game::displayMap(){
    int choice;
    cout << endl;
    cout << "                       Farm                           " << endl;
    cout << "                         |                            " << endl;
    cout << " Mines ----------    Town Square -------------   Beach" << endl;
    cout << "                         |                            " << endl;
    cout << "                      Joja Mart                       " << endl;
}

void Game::startGame() {
    string name;
    cout << "Enter your farmer's name: " << endl;
    cin >> name;
    player = Player(name);
    gameLoop();
}

void Game::gameLoop() {
    while (currentDay <= maxDays){
        if (checkWin()) {
            displayEnding();
            return;
        }
        
        displayDashboard();
        cout << "What would you like to do?" << endl;
        cout << "1. Travel" << endl;
        cout << "2. Work" << endl;
        cout << "3. Talk to villager" << endl;
        cout << "4. Community Center" << endl;
        cout << "5. Visit JojaMart" << endl;
        cout << "6. Check Inventory" << endl;
        cout << "7. End Day" << endl;
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1:
                moveLocation();
                break;
            case 2:
                forageOrWork();
                break;
            case 3:
                interactWithNPC();
                break;
            case 4:
                visitCommunityCenter();
                break;
            case 5:
                visitJojaMart();
                break;
            case 6: 
                player.displayInventory();
                cout << "Enter item index to eat (or 0 to cancel): ";
                int index;
                cin >> index;

                if(index > 0 && index <= player.getInventoryCount()){
                    Item food = player.getItem(index - 1);
                    player.changeEnergy(food.getEnergy());
                    player.removeItem(index - 1);
                    cout << "Ate " << food.getName() << "! Energy Restored!" << endl;
                }
                break;
            case 7:
                endDay();
                break;
            default:
                cout << "Invalid Option." << endl;
        }
    }
    displayEnding();
}

void Game::moveLocation() {
    int choice;
    
    cout << "Where would you like to travel?" << endl;
    for (int i = 0; i < 5; i++){
        cout << i + 1 << ". " << locations[i] << endl;
    }
    cout << "Choice: ";
    cin >> choice;

    if (choice >= 1 && choice <= 5){
        player.setLocation(locations[choice - 1]);
        cout << "Traveled to " << locations[choice - 1] << "!" << endl;
    }
    else{
        cout << "Invalid choice." << endl;
    }
}

void Game::visitCommunityCenter() {
    if (player.getCurrentLocation() != "Town Square") {
        cout << "The Community Center is near the Town Square. Travel there first!" << endl;
        return;
    }

    cout << "--- Final Bundle Board ---" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "[" << (bundleChecks[i] ? "X" : " ") << "] " << bundleNames[i] << endl;
    }

    if (player.getInventoryCount() == 0) {
        cout << "Your inventory is empty. Bring items to donate!" << endl;
        return;
    }

    cout << "Would you like to donate an item? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int index;
        player.displayInventory();
        cout << "Choose an item to donate (1-" << player.getInventoryCount() << "): ";
        cin >> index;

        if (index >= 1 && index <= player.getInventoryCount()) {
            Item donation = player.getItem(index - 1);
            bool accepted = false;

            for (int i = 0; i < 5; i++) {
                if (donation.getType() == bundleNames[i] && !bundleChecks[i]) {
                    bundleChecks[i] = true;
                    player.removeItem(index - 1);
                    cout << "Donated " << donation.getName() << " to the " << bundleNames[i] << " slot!" << endl;
                    accepted = true;
                    break;
                }
            }
            if (!accepted) {
                cout << "That item doesn't fit any missing bundle slot!" << endl;
            }
        }
    }
}

void Game::visitJojaMart() {
    if (player.getCurrentLocation() != "JojaMart"){
        cout << "You must travel to JojaMart first!" << endl;
        return;
    }
    int choice;

    cout << "1. Buy 'Joja Cola' (Restores 5 Energy) - 20 gold" << endl;
    cout << "2. Buy 'Auto-Extractor' (Completes Mineral bundle slot) - 60 gold [Increases Joja Influence]" << endl;
    cout << "3. Leave" << endl;
    cout << "Choice: ";

    cin >> choice;

    if (choice == 1){
        if (player.getMoney() >= 20) {
            player.changeMoney(-20);
            player.addItem(Item("Joja Cola", "Food", 5));
            cout << "Bought Joja Cola!" << endl;
        } else {
            cout << "Not enough gold!" << endl;
        }
    } else if (choice == 2) {
        if (player.getMoney() >= 60) {
            player.changeMoney(-60);
            bundleChecks[2] = true;
            jojaInfluence++;
            cout << "Joja completed the Mineral Bundle slot for you! Town is suspicious..." << endl;
        }
        else{
            cout << "Not enough gold!" << endl;
        }
    }
}

void Game::endDay() {
    cout << "You head to bed. Day " << currentDay << " ends..." << endl;
    currentDay++;
    player.changeEnergy(10); // Fully restore energy for the next day
    player.changeMoney(15);  // Passive daily crop/farm income
    cout << "Energy restored! Gained 15 gold passive income." << endl;
}

bool Game::checkWin() {
    for (int i = 0; i < 5; i++) {
        if (!bundleChecks[i]) return false;
    }
    return true;
}


void Game::interactWithNPC() {
    string currentLoc = player.getCurrentLocation();
    int npcIndex = -1; // -1 = no npc

    if(currentLoc == "Town Square"){
        npcIndex = 0; // Lewis
    }
    else if(currentLoc == "Beach"){
        npcIndex = 1; // Willy
    }
    else if(currentLoc == "Mines"){
        npcIndex = 2; // Clint
    }
    else if(currentLoc == "Farm"){
        npcIndex = 3; // Marnie
    }
    if(npcIndex == -1){
        cout << "Nobody is around here to talk to." << endl;
        return;
    }
    cout << npcs[npcIndex].getName() << npcs[npcIndex].getHint() << endl;

    if (!npcs[npcIndex].isQuestDone()) {
        cout << "Would you like to hand them an item to increase friendship? (y/n): ";
        char choice;
        cin >> choice;

        if ((choice == 'y' || choice == 'Y') && player.getInventoryCount() > 0) {
            int index;
            
            player.displayInventory();
            cout << "Select item (1 - " << player.getInventoryCount() << "): ";
            
            cin >> index;

            if (index >= 1 && index <= player.getInventoryCount()) {
                Item gift = player.getItem(index - 1);
                player.removeItem(index - 1);
                
                npcs[npcIndex].increaseFriendship(5);
                npcs[npcIndex].completeQuest();
                
                cout << "You gifted a " << gift.getName() << "! Friendship level is now " << npcs[npcIndex].getFriendship() << "!" << endl;
            }
        }
        else if(player.getInventoryCount() == 0 && (choice == 'y' || choice == 'Y')){
            cout << "Your inventory is empty! Go get some items first." << endl;
        }
    }
    else{
        cout << npcs[npcIndex].getName() << " says hello." << endl;
    }
}

void Game::forageOrWork() {
    if (player.getEnergy() < 2) {
        cout << "Too tired! Sleep or eat to restore energy." << endl;
        return;
    }
    
    string location = player.getCurrentLocation();
    player.changeEnergy(-2);

    if(location == "Farm"){
        player.addItem(Item("Parsnip", "Crop", 2));
        cout << "Harvested a fresh Parsnip! (-2 Energy)" << endl;
    }
    else if(location == "Beach"){
        player.addItem(Item("Sunfish", "Fish", 3));
        cout << "Caught a Sunfish! (-2 Energy)" << endl;
    }
    else if(location == "Mines"){
        player.addItem(Item("Copper Ore", "Mineral", 0));
        cout << "Mined some Copper Ore! (-2 Energy)" << endl;
    }
    else if(location == "Town Square"){
        player.addItem(Item("Egg", "Animal Product", 1));
        cout << "Found a fresh stray Egg! (-2 Energy)" << endl;
    }
    else{
        player.addItem(Item("Wild Berry", "Forage Item", 3));
        cout << "Foraged a Wild Berry! (-2 Energy)" << endl;
    }
}