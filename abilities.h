#ifndef ABILITIES_H
#define ABILITIES_H
#include "cell.h"
#include <string>
#include "owner.h"
using namespace std;

class Ability {
    bool active;
  protected:
    Owner owner;
  public:
    Ability(Owner owner);
    bool isActive();
    void deactivate();
    virtual void use(Cell& c, Cell& d) = 0;
    virtual string display() = 0;
};

class Malware : public Ability {
    public:
      Malware(Owner owner);
      void use(Cell& c, Cell& d) override;
      string display() override;
};

class Firewall : public Ability {
  public:
    Firewall(Owner owner);
    void use(Cell& c, Cell& d) override;
    string display() override;
};

class LinkBoost : public Ability {
  public:
    LinkBoost(Owner owner);
    void use(Cell& c, Cell& d) override;
    string display() override;
};

class Scan : public Ability {
  public:
    Scan(Owner owner);
    void use(Cell& c, Cell& d) override;
    string display() override;
};

class Download : public Ability {
  public:
    Download(Owner owner);
    void use(Cell& c, Cell& d)override;
    string display() override;
};

class Polarize : public Ability {
  public:
    Polarize(Owner owner);
    void use(Cell& c, Cell& d) override;
    string display() override;
};

class Exchange : public Ability {
  public:
    Exchange(Owner owner);
    void use(Cell& c, Cell& d) override;
    string display() override;
};

class Invisibility : public Ability {
  public:
    Invisibility(Owner owner);
    void use(Cell& c, Cell& d) override;
    string display() override;
};

#endif
