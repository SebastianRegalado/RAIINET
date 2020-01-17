#ifndef LINK_H
#define LINK_H
#include <string>
#include "owner.h"
using namespace std;

enum class LinkType {Data, Virus}; 

class Link {
  protected:
    LinkType lt;
    string name;
    string alias;
    int strength;
    Owner owner;

  public:
    Link(LinkType lt, string name, int strength, Owner owner); 
    LinkType& getLinkType();
    string getname() const;
    string& getalias();
    int& getstrength();
    Owner getOwner() const;
    virtual string display() const = 0;
    virtual ~Link() = default;
};

#endif
