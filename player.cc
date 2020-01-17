#include "player.h"
#include <iostream>

Player::Player(Grid* myGrid, Owner ID, string ab, string links): myGrid{myGrid}, PlayerID{ID} {

    string name1 = (Owner::P1 == ID) ? "a" : "A";
    string name2 = (Owner::P1 == ID) ? "A" : "a"; 
    for(int i = 0; i < 16; ++i) { //Initializes myLinks and enemyLinks
        Posn p = {0, i/2};
        if (Owner::P2 == ID) p.row = 7;
        if ((i == 6 || i == 8) && Owner::P1 == ID) p.row += 1;
        else if (i == 6 || i == 8) p.row -= 1;
        LinkType lt = (links[i] == 'D') ? LinkType::Data : LinkType::Virus;
        ++i; // Checks the strength               here!    
        myLinks.emplace_back(MyLink(lt, name1, (int)(links[i] - '0'), ID, p));
        Owner enemyID = (Owner::P1 == ID) ? Owner::P2 : Owner::P1; 
        enemyLinks.emplace_back(EnemyLink(name2, enemyID));
        ++name1[0];//Changes the name1 and name2
        ++name2[0];
    }

    for(int i = 0; i < 5; ++i) { //Initializes myAbilities
        if(ab[i] == 'L') myAbilities.emplace_back(make_unique<LinkBoost>(ID));
        if(ab[i] == 'F') myAbilities.emplace_back(make_unique<Firewall>(ID));
        if(ab[i] == 'D') myAbilities.emplace_back(make_unique<Download>(ID));
        if(ab[i] == 'S') myAbilities.emplace_back(make_unique<Scan>(ID));
        if(ab[i] == 'P') myAbilities.emplace_back(make_unique<Polarize>(ID));
        if(ab[i] == 'M') myAbilities.emplace_back(make_unique<Malware>(ID));
        if(ab[i] == 'E') myAbilities.emplace_back(make_unique<Exchange>(ID));
        if(ab[i] == 'I') myAbilities.emplace_back(make_unique<Invisibility>(ID));
    }

    //attaches the links to their initial cell
    for(int i = 0; i < 8; ++i) myGrid->attach(&myLinks[i], myLinks[i].getPosn());

    //sets player as observer of the cells
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            Observer<Notification1> *o = &*this; 
            myGrid->attachObserver(o, Posn{i, j});
        }
    }
}

void Player::move(string name, string direction) { // move link
    Cell &c = myGrid->getCell(name); 
    Posn p = c.getLink()->getPosn();
    int j = c.getLink()->getjump();

    if((PlayerID == Owner::P1 && c.getLink()->getOwner() == Owner::P2) ||
       (PlayerID == Owner::P2 && c.getLink()->getOwner() == Owner::P1)) {
        throw "You don't own this link";
    }


    if(direction == "up" || direction == "left") {j *= -1;}
    if(direction == "up" || direction == "down") {p.row += j;}
    else p.col +=j;

    if(portal){
        if (p.col < 0) {
            p.col += 8;
        } else if (p.col > 7) {
            p.col -= 8;
        }
    }

    if(p.col < 0 || p.col > 7) throw "You are trying to go out of bounds"; // check boundaries
    if(p.row < 0 && c.getLink()->getOwner() == Owner::P1) {
        throw "You are trying to go out of bounds";
    } else if (p.row < 0) {
        myGrid->move(c.getLink()->getPosn(), Posn{7, 3});
    } else if (p.row == 0 && (p.col == 3 || p.col == 4) && c.getLink()->getOwner() == Owner::P1) {
        throw "You cannot place link on top of your own server";
    } else if (p.row > 7 && c.getLink()->getOwner() == Owner::P2) {
        throw "You are trying to go out of bounds";
    } else if (p.row > 7) {
        myGrid->move(c.getLink()->getPosn(), Posn{0, 3});
    } else if (p.row == 7 && (p.col == 3 || p.col == 4) && c.getLink()->getOwner() == Owner::P2) {
        throw "You cannot place link on top of your own server";
    } else {
        myGrid->move(c.getLink()->getPosn(), p);
    }
}

void Player::useAbility(int AbilityNum, Cell &c, Cell &d) { // apply abilities to cell
    if (myAbilities[AbilityNum - 1]->isActive()) {
        myAbilities[AbilityNum - 1]->use(c, d);
    } else {
        throw "You have already used this ability";
    }
}

void Player::notify(Notification1 nt1) { // send notification
    switch (nt1.tn1) {
        case TypeNot1::Battle:
            if (nt1.w->getOwner() == nt1.l->getOwner()) { // error check: battle own link
                throw "Cannot battle with own link!";
            }

            if(PlayerID == nt1.w->getOwner()) {
                if ((nt1.l)->getLinkType() == LinkType::Data) DownloadedData += 1;
                else DownloadedVirus += 1;
                revealEnemy(nt1.l);

                if (DownloadedData >= 4) {
                    triggerWin();
                } else if (DownloadedVirus >= 4) {
                    triggerLoss();
                }
            } else {
                if ((nt1.l)->getLinkType() == LinkType::Data) EDownloadedData += 1;
                else EDownloadedVirus += 1;
                revealEnemy(nt1.w);
            }
            break;
        // Firewall was triggered on a virus
        case TypeNot1::FirewallTrigger:
            for (int i = 0; i < 8; i++) {
                if (myLinks[i].active && myLinks[i].getname() == (nt1.l)->getname()) {
                    (nt1.l)->active = 0;
                    DownloadedVirus += 1;
                    return;
                }
            }
            // Else virus is enemy link
            EDownloadedVirus += 1;
            revealEnemy(nt1.l);
            break;
        // Need to reveal a link
        case TypeNot1::Scan:
            revealEnemy(nt1.w);
            break;
        // Download ability was used
        case TypeNot1::Download:
            (nt1.w)->active = 0;

            if(PlayerID == nt1.w->getOwner()) {
                if ((nt1.w)->getLinkType() == LinkType::Data) EDownloadedData += 1;
                else EDownloadedVirus += 1;
            } else {
                if ((nt1.w)->getLinkType() == LinkType::Data) {
                    DownloadedData += 1;
                } else {
                    DownloadedVirus += 1;
                }
                revealEnemy(nt1.w);
            }

            if (DownloadedData >= 4) {
                triggerWin();
            } else if (DownloadedVirus >= 4) {
                triggerLoss();
            }
            break;
        // Server download was triggered
        case TypeNot1::Server1:
            if (PlayerID == Owner::P1) {
                revealEnemy(nt1.w);
                (nt1.w)->active = 0;
                if ((nt1.w)->getLinkType() == LinkType::Data) {
                    DownloadedData += 1;
                } else {
                    DownloadedVirus += 1;
                }

                if (DownloadedData >= 4) {
                    triggerWin();
                } else if (DownloadedVirus >= 4) {
                    triggerLoss();
                }
            } else {
                if ((nt1.w)->getLinkType() == LinkType::Data) {
                    EDownloadedData += 1;
                } else {
                    EDownloadedVirus += 1;
                }
            }
            break;
        case TypeNot1::Server2: // server2 download triggered
            if (PlayerID == Owner::P2) {
                revealEnemy(nt1.w);
                (nt1.w)->active = 0;
                if ((nt1.w)->getLinkType() == LinkType::Data) {
                    DownloadedData += 1;
                } else {
                    DownloadedVirus += 1;
                }

                if (DownloadedData >= 4) {
                    triggerWin();
                } else if (DownloadedVirus >= 4) {
                    triggerLoss();
                }
            } else {
                if ((nt1.w)->getLinkType() == LinkType::Data) {
                    EDownloadedData += 1;
                } else {
                    EDownloadedVirus += 1;
                }
            }
            break;
        case TypeNot1::A1: // ability used by player1
            if(PlayerID == Owner::P1) AvailableAbilities -= 1;
            else EAvailableAbilities -= 1;
            break;
        case TypeNot1::A2: // ability used by player2
            if(PlayerID == Owner::P1) EAvailableAbilities -= 1;
            else AvailableAbilities -= 1;
            break;
    }
}

string Player::displayMyLinks() { // display player links
    string s = "Player ";
    if(PlayerID == Owner::P1) s += "1";
    else s += "2";
    s += ":\nDownloaded: " + to_string(DownloadedData) + "D, " + to_string(DownloadedVirus) + "V\n";
    s += "Abilities: " + to_string(AvailableAbilities) + "\n";
    for(int i = 0; i < 3; ++i) s += myLinks[i].display() + "  ";
    s += myLinks[3].display() + "\n";
    for(int i = 4; i < 7; ++i) s += myLinks[i].display() + "  ";
    s += myLinks[7].display() + "\n";
    return s;
}

string Player::displayEnemyLinks() { // display other player links
    string s = "Player ";
    if(PlayerID == Owner::P1) s += "2";
    else s += "1";
    s += ":\nDownloaded: " + to_string(EDownloadedData) + "D, " + to_string(EDownloadedVirus) + "V\n";
    s += "Abilities: " + to_string(EAvailableAbilities) + "\n";
    for(int i = 0; i < 3; ++i) s += enemyLinks[i].display() + "  ";
    s += enemyLinks[3].display() + "\n";
    for(int i = 4; i < 7; ++i) s += enemyLinks[i].display() + "  ";
    s += enemyLinks[7].display() + "\n";
    return s;
}

MyLink& Player::getLink(string name) { // return link
    for(int i = 0; i < 8; ++i) {
        if(myLinks[i].active && myLinks[i].getname() == name) return myLinks[i];
    } 
    throw "Link " + name + " is no longer on the board";
}

void Player::revealEnemy(MyLink* link) { // reveal enemy link
    for (int i = 0; i < 8; ++i) {
        if(enemyLinks[i].getname() == link->getname()) enemyLinks[i].reveal(link);
    }
}

void Player::portals() {// set portals
    portal = !portal;    
}

string Player::displayAbilities() { // display player ability
    string s = "Player ";
    if(PlayerID == Owner::P1) s += "1";
    else s += "2";
    s += "\n";
    for(int i = 0; i < 4; ++i) {
        s += to_string(i+1) + ": " + myAbilities[i]->display() + " ";
        if(myAbilities[i]->isActive()) s += "(unused)\n";
        else s += "(used)\n";
    }
    s += to_string(5) + ": " + myAbilities[4]->display();
    if(myAbilities[4]->isActive()) s += " (unused)";
    else s += " (used)";
    s += "\n";
    return s;
}

Owner Player::getID() { // return player ID
    return PlayerID; 
}

void Player::triggerWin() { // print win scenario
    throw "Player " + to_string((int) PlayerID ) + " Wins!";
}

void Player::triggerLoss() { // print lose scenario
    throw "Player " + to_string(3 - ((int) PlayerID)) + " Wins!";
}
