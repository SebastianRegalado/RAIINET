#ifndef ENEMYLINK_H
#define ENEMYLINK_H
#include <string>
#include "myLink.h"
#include "posn.h"
#include "owner.h"
using namespace std;

class EnemyLink : public Link {
  public:
	bool revealed;
	void reveal(MyLink* l);
	EnemyLink(string name, Owner owner);	
	string display() const;
};

#endif
