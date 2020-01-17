#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "subject.h"
#include "observer.h"
#include "notification2.h"
#include "model.h"
#include "posn.h"
#include "owner.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

enum class TypeofAbilities{Firewall, LinkBoost, Scan, Download, Polarize, Malware, Exchange, Invisibility};

class Controller {
    Model* model;
    vector<vector<TypeofAbilities>> PlayersAbilities;

  public:
    Controller(Model*, string, string); // still need to implement
    void HandleInput(istream&, ostream&);
};

#endif
