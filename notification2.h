#ifndef NOTIFICATION2_H
#define NOTIFICATION2_H
#include "posn.h"
#include <vector>
#include <string>

using namespace std;

enum class TypeofAbilities;

enum class TypeNot2 {Move, Ability, Abilities, Board};

struct Notification2 {
    TypeNot2 tn2;
    bool requiresname;
    string Linkname;
    string direction;
    int abilityIndex;
    Posn posn;
};

#endif
