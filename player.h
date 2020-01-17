#ifndef PLAYER_H
#define PLAYER_H
#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include "notification1.h"
#include "subject.h"
#include "abilities.h"
#include "observer.h"
#include "link.h"
#include "myLink.h"
#include "enemyLink.h"
#include "grid.h"

using namespace std;

class Player : public Observer<Notification1> {
    Grid *myGrid;
    Owner PlayerID;
    vector<unique_ptr<Ability>> myAbilities;
    vector<MyLink> myLinks;
    vector<EnemyLink> enemyLinks;
    int DownloadedData = 0;
    int DownloadedVirus = 0;
    int EDownloadedData = 0;
    int EDownloadedVirus = 0;
    int AvailableAbilities = 5;
    int EAvailableAbilities = 5;
    bool portal = false;
  public:
    Player(Grid* myGrid, Owner owner, string ab1, string l1);
    void notify(Notification1 nt1);
    void move(string name, string direction);
    void useAbility(int AbilityNum, Cell &c, Cell &d);
    string displayMyLinks();
    string displayEnemyLinks();
    MyLink& getLink(string name);
    void revealEnemy(MyLink* link);
    void portals();
    string displayAbilities();
    Owner getID();
    void triggerWin();
    void triggerLoss();
};

#endif
