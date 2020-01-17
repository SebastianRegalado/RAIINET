#ifndef GRID_H
#define GRID_H
#include <vector>
#include <string>
#include "posn.h"
#include "cell.h"

using namespace std;

class Player;

class Grid {
    vector<vector<Cell>> theGrid;

  public:
    Grid();
    void attach(MyLink* other, Posn dest);
    void move(Posn initial, Posn final);
    Cell& getCell(Posn posn);
    Cell& getCell(string s);
    string display(Owner playerPerspective);
    void attachObserver(Observer<Notification1> *p, Posn posn);
};

#endif
