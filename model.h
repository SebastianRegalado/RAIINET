#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <iostream>
#include "player.h"
#include "grid.h"
#include <memory>
#include "subject.h"
#include "observer.h"
#include "notification2.h"
#include "owner.h"
#include "view.h"
using namespace std;

class Model : public Subject<Notification2>, public Observer<Notification2> {
    vector<unique_ptr<Player>> players;
    Grid Board;
    View* view;
    int count = 0;
    bool usedAbility = false;

  public:
    Model(View* v, string ab1 = "", string ab2 = "", string l1 = "", string l2 = "");
    void notify(Notification2 n2) override;
    void move(string name, string direction);
    void displayAbilities(ostream& output);
    void board(ostream& output);
    void useAbility(int abilityID, Posn cellPosn);
    void useAbility(int abilityID, string linkName);
    void useAbility(int abilityID, string cName, string dName);
    void portals();
    Owner getTurn();
};

#endif
