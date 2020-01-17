#include "enemyLink.h"
#include <string>

EnemyLink::EnemyLink(string name, Owner owner) : 
	Link(LinkType::Data, name, 0, owner), revealed{0} {}

void EnemyLink::reveal(MyLink *l) { // reveal discovered enemylink
	revealed = 1;
	lt = l->getLinkType();
	strength = l->getstrength();	
}

string EnemyLink::display() const {
	if (revealed) { // display an enemylink
		if (lt == LinkType::Data){
			return name + ": D" + to_string(strength);
		} else {
			return name + ": V" + to_string(strength);
		}
	} else {
		return name + ": ? ";
	}
}
