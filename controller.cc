#include "controller.h"

Controller::Controller(Model* m, string AB_1, string AB_2) {
    this->model = m;
 
    if (AB_1.length()>5) throw "AB_1 has too many abilities initalized"; // exception testing for invalid
    if (AB_1.length()<5) throw "AB_1 has too little abilities initalized";
    if (AB_2.length()>5) throw "AB_2 has too many abiltiies initalized";
    if (AB_2.length()<5) throw "AB_2 has too little abiltities intialized";

    vector<string> AB_temp;
    AB_temp.emplace_back(AB_1);
    AB_temp.emplace_back(AB_2);

    for(int i=0; i<2; ++i) {
        vector<TypeofAbilities> temp;

        for(int j=0; j<5; ++j) { // load Ability avaliable for users
            if (AB_temp[i][j]=='F') {
                temp.emplace_back(TypeofAbilities::Firewall);
            } else if (AB_temp[i][j]=='D') {
                temp.emplace_back(TypeofAbilities::Download);
            } else if (AB_temp[i][j]=='S') {
                temp.emplace_back(TypeofAbilities::Scan);
            } else if (AB_temp[i][j]=='P') {
                temp.emplace_back(TypeofAbilities::Polarize);
            } else if (AB_temp[i][j]=='L') {
                temp.emplace_back(TypeofAbilities::LinkBoost);
            } else if (AB_temp[i][j]=='M') {
                temp.emplace_back(TypeofAbilities::Malware);
            } else if (AB_temp[i][j]=='E') {
                temp.emplace_back(TypeofAbilities::Exchange);  
            } else if (AB_temp[i][j]=='I') {
                temp.emplace_back(TypeofAbilities::Invisibility);  
            } else {
                throw "Invalid Controller Setup (Invalid Ability Initalized)";
            }
        }

        PlayersAbilities.emplace_back(temp);
    }
}

void Controller::HandleInput(istream &in, ostream& out) {
    string str;
    model->board(out);

    while (getline(in, str)) { // read line of game command
        stringstream s{str};
        string command;
        s >> command;

        if (command=="move") { // move command
            string Link;
            string Dir;

            s >> Link;
            s >> Dir;

            if (s.fail()) {
                cerr << "Incomplete move command." << endl;
                continue;
            }

            if (Owner::P1==model->getTurn()) { // check valid move command inputs
                if (Link.length() > 1 || !((Link>="a")&&(Link<="h"))) {
                    cerr << "Invalid link in move command for Player 1." << endl;
                    continue;
                }
            }

            if (Owner::P2==model->getTurn()) {
                if (Link.length() > 1 || !((Link>="A")&&(Link<="H"))) {
                    cerr << "Invalid link in move command for Player 2." << endl;
                    continue;
                }
            }

            if (!((Dir=="up")||(Dir=="down")||(Dir=="left")||(Dir=="right"))) {
                cerr << "Invalid Dir in move command." << endl;
                continue;
            }

            try {
                model->move(Link, Dir); // implement move command
                model->board(out);
            } catch (char const *a) {
                cerr << a << endl;
            }

        } else if (command=="abilities") {
            model->displayAbilities(out); // display abilities
        } else if (command=="ability") {
            int typeAbility;
            s >> typeAbility;

            if (s.fail()) {
                cerr << "Invalid ability command." << endl;
                continue;
            }

            if ((typeAbility<1)||(typeAbility>5)) {
                cerr << "Invalid Ability Id." << endl;
                continue;
            }

            int P_turn;

            if (Owner::P1==model->getTurn()) {
                P_turn=0;
            } else {
                P_turn=1;
            }

            if (PlayersAbilities[P_turn][typeAbility-1]==TypeofAbilities::Firewall) { // check player
                int pos_x, pos_y;

                s >> pos_x;
                s >> pos_y;

                if (s.fail()) {
                    cerr << "Incomplete firewall ability command." << endl;
                    continue;
                }

                try {
                    model->useAbility(typeAbility, Posn{pos_x,pos_y}); // apply firewall command
                } catch (char const *a) {
                    cerr << a << endl;
                }
            } else if (PlayersAbilities[P_turn][typeAbility-1]==TypeofAbilities::Exchange) {
                string firstLink;
                string secondLink;
                s >> firstLink;
                s >> secondLink;

                if (s.fail()) {
                    cerr << "Invalid Exchange command." << endl;
                    continue;
                }

                if (Owner::P1==model->getTurn()) { // check exchange command setup
                    if ((!((firstLink>="a")&&(firstLink<="h"))) || (!((secondLink>="a")&&(secondLink<="h")))) {
                        cerr << "Invalid link in Exchange command for Player 1." << endl;
                        continue;
                    }
                }

                if (Owner::P2==model->getTurn()) {
                    if (!((firstLink>="A")&&(firstLink<="H")) || !((secondLink>="A")&&(secondLink<="H"))) {
                        cerr << "Invalid link in Exchange command for Player 2." << endl;
                        continue;
                    }
                }

                try {
                    model->useAbility(typeAbility, firstLink, secondLink); // apply exchange command
                } catch (char const *a) {
                    cerr << a << endl;
                }
            } else if (PlayersAbilities[P_turn][typeAbility-1]==TypeofAbilities::Download) {
                string Link;
                s >> Link;

                if (s.fail()) {
                    cerr << "Invalid ability command." << endl;
                    continue;
                }

                if (Owner::P1==model->getTurn()) { // check Download command input
                    if (!((Link>="A")&&(Link<="H"))) {
                        cerr << "Invalid link in Download command for Player 1." << endl;
                        continue;
                    }
                }

                if (Owner::P2==model->getTurn()) {
                    if (!((Link>="a")&&(Link<="h"))) {
                        cerr << "Invalid link in Download command for Player 2." << endl;
                        continue;
                    }
                }
                
                try {
                    model->useAbility(typeAbility, Link); // apply Download command
                } catch (char const *a) {
                    cerr << a << endl;
                } 
            } else if ((PlayersAbilities[P_turn][typeAbility-1]==TypeofAbilities::Scan)||
                        (PlayersAbilities[P_turn][typeAbility-1]==TypeofAbilities::Polarize)) {
                string Link;
                s >> Link;

                if (s.fail()) {
                    cerr << "Invalid ability command" << endl; // check scan and polarize command input
                    continue;
                }

                try {
                    model->useAbility(typeAbility, Link); // apply scan/polarize command input
                } catch (char const *a) {
                    cerr << a << endl;
                }
            } else {
                string Link;
                s >> Link;

                if (s.fail()) {
                    cerr << "Invalid ability command." << endl;
                    continue;
                }

                if (Owner::P1==model->getTurn()) { // check ability command input
                    if (!((Link>="a")&&(Link<="h"))) {
                        cerr << "Invalid link in ability command for Player 1." << endl;
                        continue;
                    }
                }

                if (Owner::P2==model->getTurn()) {
                    if (!((Link>="A")&&(Link<="H"))) {
                        cerr << "Invalid link in ability command for Player 2." << endl;
                        continue;
                    }
                }

                try {
                    model->useAbility(typeAbility, Link); // apply ability command input
                } catch (char const *a) {
                    cerr << a << endl;
                }
            }
        } else if (command=="board") {
            model->board(out); // apply board command
        } else if (command=="sequence") {
            string FileName;
            s >> FileName;

            if (s.fail()) {
                cerr << "Invalid sequence command." << endl;
                continue;
            }

            ifstream myfile;
            myfile.open(FileName);

            if (myfile.is_open()) {
                HandleInput(myfile, out); // recursive call for sequence          
            }
        
        } else if (command=="portals") {
            model->portals();  // apply portals command
        } else if (command=="quit") {
            break; // apply quite command
        } else {
            cerr << "Invalid Command" << endl;
            continue;
        }
    }
}
