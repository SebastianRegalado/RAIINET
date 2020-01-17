#include "abilities.h"
#include "owner.h"

Ability::Ability(Owner owner) : active{1}, owner{owner} {}

bool Ability::isActive() { // check if its active
    return active; 
}

void Ability::deactivate() { // deactive ability
    active = 0; 
}

Malware::Malware(Owner owner) : Ability{owner} {} 

void Malware::use(Cell& c, Cell& d) { // apply malware ability
    c.getFirewall() = Owner::None;
}

string Malware::display() {
    return "Malware";
}

Firewall::Firewall(Owner owner) : Ability{owner} {}

void Firewall::use(Cell& c, Cell& d) { // apply firewall
    if(c.getFirewall() != Owner::None) { 
        throw "A firewall card has already been applied to this square";
    }
    if(c.getLink() != nullptr) {
        throw "A firewall can only be placed on top of empty squares";
    }
    c.getFirewall() = owner;
    deactivate();
    TypeNot1 tn1 = (owner == Owner::P1) ? TypeNot1::A1 : TypeNot1::A2;
    c.notifyObservers(Notification1{tn1, nullptr, nullptr}); // send notification
}

string Firewall::display() {
    return "Firewall";
}

LinkBoost::LinkBoost(Owner owner) : Ability{owner} {}

void LinkBoost::use(Cell& c, Cell& d) { // Use linkboost
    if(!c.getLink()->active) {
        throw "This link is no longer in the game";
    }
    c.getLink()->getjump() += 1;
    deactivate();
    TypeNot1 tn1 = (owner == Owner::P1) ? TypeNot1::A1 : TypeNot1::A2;
    c.notifyObservers(Notification1{tn1, nullptr, nullptr}); // send notification
}

string LinkBoost::display() {
    return "LinkBoost";
}

Scan::Scan(Owner owner) : Ability{owner} {}

void Scan::use(Cell& c, Cell& d) { // apply scan ability
    if(!c.getLink()->active) {
        throw "This link is no longer in the game";
    }
    c.notifyObservers(Notification1{TypeNot1::Scan, c.getLink(), nullptr});
    deactivate();
    TypeNot1 tn1 = (owner == Owner::P1) ? TypeNot1::A1 : TypeNot1::A2;
    c.notifyObservers(Notification1{tn1, nullptr, nullptr}); // send notification
}

string Scan::display() {
    return "Scan";
}

Download::Download(Owner owner) : Ability{owner} {}

void Download::use(Cell& c, Cell& d) { // apply download ability
    if(!c.getLink()->active) {
        throw "This link is no longer in the game";
    }
    c.notifyObservers(Notification1{TypeNot1::Download, c.getLink(), nullptr});
    c.getLink() = nullptr;
    deactivate();
    TypeNot1 tn1 = (owner == Owner::P1) ? TypeNot1::A1 : TypeNot1::A2;
    c.notifyObservers(Notification1{tn1, nullptr, nullptr}); // send notification
}

string Download::display() {
    return "Download";
}

Polarize::Polarize(Owner owner) : Ability{owner} {}

void Polarize::use(Cell& c, Cell& d) { // apply polarize ability
    if(!c.getLink()->active) {
        throw "This link is no longer in the game";
    }
    if(c.getLink()->getLinkType() == LinkType::Data) {
        c.getLink()->getLinkType() = LinkType::Virus;
    } else {
        c.getLink()->getLinkType() = LinkType::Data;
    }
    deactivate();
    TypeNot1 tn1 = (owner == Owner::P1) ? TypeNot1::A1 : TypeNot1::A2;
    c.notifyObservers(Notification1{tn1, nullptr, nullptr}); // send notification
}

string Polarize::display() {
    return "Polarize";
}

Exchange::Exchange(Owner owner) : Ability{owner} {}

void Exchange::use(Cell& c, Cell& d) { // apply exchange
    if (!c.getLink()->active || !d.getLink()->active) {
        throw "Links are not both active";
    }

    c.getLink()->getalias() = d.getLink()->getname();
    d.getLink()->getalias() = c.getLink()->getname();

    swap(c.getLink(), d.getLink());
    swap(c.getLink()->getPosn(), d.getLink()->getPosn());
    deactivate(); // deactivate
}

string Exchange::display() {
    return "Exchange";
}

Invisibility::Invisibility(Owner owner) : Ability{owner} {}

void Invisibility::use(Cell& c, Cell& d) { // use invisibility ability
    if (!c.getLink()->active) {
        throw "Link is not active";
    }

    c.getLink()->invis = true;
    deactivate(); // deactive
}

string Invisibility::display() {
    return "Invisibility";
}
