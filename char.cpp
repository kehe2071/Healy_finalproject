#include "char.h"

Character::Character(){
    name = "NPC";
    roleHint = "No hint";
    friendship = 0;
    questCompleted = false;
}

Character::Character(string charName, string hint){
    name = charName;
    roleHint = hint;
    friendship = 0;
    questCompleted = false;
}

string Character::getName(){
    return name;
}

string Character::getHint(){
    return roleHint;
}

int Character::getFriendship(){
    return friendship;
}

void Character::increaseFriendship(int amount){
    friendship += amount;
}

bool Character::isQuestDone(){
    return questCompleted;
}

void Character::completeQuest(){
    questCompleted = true;
}