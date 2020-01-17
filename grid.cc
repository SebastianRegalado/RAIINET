#include "grid.h"
#include "myLink.h"
#include "owner.h" 


Grid::Grid() { // grid constructor
    for(int i=0; i<8; ++i) {
        vector<Cell> v;
        for(int j=0; j<8; ++j) {
            v.emplace_back(Cell(i, j));
        }
        theGrid.emplace_back(v);
    }

    theGrid[0][3].setServer(Owner::P1); // set server ports
    theGrid[0][4].setServer(Owner::P1);
    theGrid[7][3].setServer(Owner::P2);
    theGrid[7][4].setServer(Owner::P2);
}

void Grid::attach(MyLink* other, Posn dest) {
    theGrid[dest.row][dest.col].getLink() = other; // attach links to cell
}

void Grid::attachObserver(Observer<Notification1> *p, Posn posn) {
    theGrid[posn.row][posn.col].attach(p); // attach observer to grid
}

void Grid::move(Posn initial, Posn finalPos) { // move cell
    auto temp = theGrid[initial.row][initial.col].getLink(); 

    theGrid[finalPos.row][finalPos.col].place(temp);

    theGrid[initial.row][initial.col].getLink() = nullptr; //deleting link from its original position

    temp->getPosn() = finalPos;
}

Cell& Grid::getCell(Posn posn) { // return cell
    return theGrid[posn.row][posn.col];
}

Cell& Grid::getCell(string s) { // return cell
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (theGrid[i][j].getLink() != nullptr && theGrid[i][j].getLink()->active && //we should not check the second condition
                theGrid[i][j].getLink()->getname() == s) {
                return theGrid[i][j];
            }
        }
    }

    throw "Link " + s + " is no longer in the board."; 
}

string Grid::display(Owner playerPerspective) { // display grid
    string s = "========\n";
    for(int i=0; i < 8; ++i) {
        for(int j=0; j < 8; ++j) {
            s += theGrid[i][j].display(playerPerspective);
        }
        s += "\n";
    }
    s += "========\n";
    return s;
}
