#include "link.h"

Link::Link(LinkType lt, string name, int strength, Owner owner): 
    lt{lt}, name{name}, alias{name}, strength{strength}, owner{owner} {}

LinkType& Link::getLinkType() { // return link type
    return lt;
}

string Link::getname() const { // return link name
    return name;
}

string& Link::getalias() { // return link alias
    return alias;
}

int& Link::getstrength() { // return link strength
    return strength;
}

Owner Link::getOwner() const { // return link owner
    return owner;
}
