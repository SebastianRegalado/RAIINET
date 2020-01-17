#include "cell.h"
#include "owner.h"
#include "link.h"
#include "notification1.h"
#include <iostream>

bool sameOwner(MyLink *l1, MyLink *l2) {
    return l1->getOwner() == l2->getOwner(); 
}

Cell::Cell(int row, int col): posn{Posn{row, col}}, l{nullptr}, firewall{Owner::None},
	Server{Owner::None} {}

void Cell::place(MyLink* other) {

    if(isServer()) {
        if (Server == Owner::P1) {
            notifyObservers(Notification1{TypeNot1::Server1, other, nullptr});
        } else {
            notifyObservers(Notification1{TypeNot1::Server2, other, nullptr});
        }
	    return;
    }

    if (firewall == Owner::None || firewall == other->getOwner()) {
        // No Firewall interaction
    	if (l == nullptr) {
    	    l = other;
    	} else {
	    // Resolve combat
	    if (l->getstrength() > other->getstrength()) {
            notifyObservers(Notification1{TypeNot1::Battle, l, other});//Check
	    } else {
            MyLink* loser = l;
            l = other;
            notifyObservers(Notification1{TypeNot1::Battle, l, loser}); // Check
	    }
	}
    } else {
        // Triggered Firewall
		// Reveal link
		notifyObservers(Notification1{TypeNot1::Scan, other, nullptr});
      	if (other->getLinkType() == LinkType::Data) {
	        // Reveal data link
	        //notifyObservers(Notification1{TypeNot1::Scan, l, other}); // Check
            if (!l) {
    	        l = other;
            } else {
	            // Resolve combat
    	        if (l->getstrength() > other->getstrength()) {
            		notifyObservers(Notification1{TypeNot1::Battle, l, other});//Check
	 		   	} else {
         			MyLink* loser = l;
            		l = other;
            		notifyObservers(Notification1{TypeNot1::Battle, l, loser}); // Check
	    		}
	        }
    	} else {
	        // Remove virus link
    		notifyObservers(Notification1{TypeNot1::Download, other, nullptr});
    	}
    }
}

MyLink*& Cell::getLink() {
    return l;
}

Owner &Cell::getFirewall() {
    return firewall;
}

bool Cell::isServer() {
	return Server != Owner::None;
}

void Cell::setServer(Owner Server) {
	this->Server = Server;
}

void Cell::setFirewall(Owner firewallOwner) {
    firewall = firewallOwner;
}

string Cell::display(Owner playerPerspective) {
	if(Server == Owner::P1) {return "s";}
	if(Server == Owner::P2) {return "S";}
	if(firewall == Owner::P1 && playerPerspective == Owner::P1) {return "m";}
	if(firewall == Owner::P2 && playerPerspective == Owner::P2) {return "w";}
	if(l) {
        if (l->getOwner() == playerPerspective) {
            return l->getname();
        } else if (!l->invis) {
            return l->getalias();
        }
    }
	return ".";
}
