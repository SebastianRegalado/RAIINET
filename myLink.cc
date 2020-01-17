#include "myLink.h"
#include "link.h"
#include <iostream>
#include <string>

MyLink::MyLink(LinkType lt, string name, int strength, Owner owner, Posn posn): 
    Link(lt, name, strength, owner), posn{posn}, jump{1}, active{1}, invis{0} {}

string MyLink::display() const { // display link type of player
	if (lt == LinkType::Data) {
		return name + ": D" + to_string(strength);
	} else {
		return name + ": V" + to_string(strength);
	}
}

int& MyLink::getjump() { // return jump
	return jump;
}

Posn& MyLink::getPosn() { // return link posn
	return posn;
}
