#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "notification1.h"
#include "subject.h"
#include "observer.h"
#include "myLink.h"
#include "owner.h"
#include "posn.h"
using namespace std;

class Cell : public Subject<Notification1> {
  Posn posn;
  MyLink *l;
  Owner firewall;
  Owner Server;
  vector<Observer<Notification1> *> players;

 public:
  Cell(int row, int col);
  void place(MyLink* other);
  MyLink*& getLink();
  Owner &getFirewall();
  bool isServer();
  void setServer(Owner Server);
  void setFirewall(Owner firewallOwner);
  string display(Owner playerPerspective);
};

#endif
