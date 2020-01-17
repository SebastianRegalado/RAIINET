#include "model.h"
#include "owner.h"

Model::Model(View* v, string ab1, string ab2, string l1, string l2) : count{0} {
    players.emplace_back(make_unique<Player>(&Board, Owner::P1, ab1, l1));
    players.emplace_back(make_unique<Player>(&Board, Owner::P2, ab2, l2));
    view = v;
}


void Model::notify(Notification2 n2) { // notification from model to players
    if(n2.tn2 == TypeNot2::Move) {
        players[count % 2]->move(n2.Linkname, n2.direction);
    } else if (n2.tn2 == TypeNot2::Ability) {
        if(n2.requiresname) {
            Cell& c = Board.getCell(n2.Linkname);
            players[count % 2]->useAbility(n2.abilityIndex, c, c);
        } else {
            Cell& c = Board.getCell(n2.posn);
            players[count % 2]->useAbility(n2.abilityIndex, c, c);
        }
    } else if (n2.tn2 == TypeNot2::Abilities) {
        players[count % 2]->displayAbilities();
    } else if (n2.tn2 == TypeNot2::Board) {
        players[count % 2]->displayMyLinks();
        Board.display(players[count % 2]->getID());
        players[count % 2]->displayEnemyLinks();
    } 
}

void Model::move(string name, string direction) { // move links
    players[count % 2]->move(name, direction);
    count += 1;
    usedAbility = false;
}

void Model::displayAbilities(ostream& output) { // display ability to output screen
    view->displayText(output, players[count % 2]->displayAbilities());
}

void Model::board(ostream& output) { // print board
    view->display(output, players[count % 2]->displayMyLinks() + Board.display(players[count % 2]->getID()) 
        + players[count % 2]->displayEnemyLinks());
}

void Model::useAbility(int abilityID, Posn cellPosn) { // apply ability to game
    if (!usedAbility) {
        players[count % 2]->useAbility(abilityID, Board.getCell(cellPosn), Board.getCell(cellPosn));
        usedAbility = true;
    } else {
        throw "Already used an ability this turn!";
    }
}

void Model::useAbility(int abilityID, string linkName) { // apply ability to game
    if (!usedAbility) {
        players[count % 2]->useAbility(abilityID, Board.getCell(linkName), Board.getCell(linkName));
        usedAbility = true;
    } else {
        throw "Already used an ability this turn!";
    }
}

void Model::useAbility(int abilityID, string cName, string dName) { // apply ability to game
    if (!usedAbility) {
        players[count % 2]->useAbility(abilityID, Board.getCell(cName), Board.getCell(dName));
        usedAbility = true;
    } else {
        throw "Already used an ability this turn!";
    }
}

void Model::portals() { // add portals to let players go out of bound sideways
    players[0]->portals();
    players[1]->portals();
}

Owner Model::getTurn() { // return game turn state
    if (count % 2 == 0) {
        return Owner::P1;
    } else {
        return Owner::P2;
    }
}

