#ifndef MYLINK_H
#define MYLINK_H
#include <string>
#include "posn.h"
#include "link.h"
#include "owner.h"
using namespace std;

class MyLink : public Link {
    Posn posn;
    int jump;

  public:
    bool active;
    bool invis;
    MyLink(LinkType lt, string name, int strength, Owner owner, Posn posn);
	  string display() const;
	  int& getjump();
    Posn& getPosn();
};

#endif
