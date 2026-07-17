#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

class Character {
private:
    string name;
    string roleHint;
    int friendship;
    bool questCompleted;

public:
    Character();
    Character(string charName, string hint);

    std::string getName();
    std::string getHint();
    int getFriendship();
    void increaseFriendship(int amount);
    bool isQuestDone();
    void completeQuest();
};

#endif