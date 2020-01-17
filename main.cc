#include <iostream>
#include <string>
#include "player.h"
#include "model.h"
#include "controller.h"
#include "main.h"
#include "view.h"
#include "window.h"
using namespace std;

int main(int argc, char * argv[]) {

    string ab1_info = "LFDSP";
    string ab2_info = "LFDSP";
    string l1_info = "V1V2V3V4D1D2D3D4";
    string l2_info = "V1V2V3V4D1D2D3D4";
    bool graphics = false;

    if (argc>10) { // check valid number of arguments
        cerr << "Please enter correct arguments, inorder to proceed with gameplay.\n";
        return 1;
    }
    
    try {
        setup(argc, argv, ab1_info, ab2_info, l1_info, l2_info, graphics); // check valid argument set up
    } catch (string s) {
        cerr << s;
        return 1;
    }

    Grid g; // intalize grid
    View view{graphics}; // intalize view
    Model model{&view, ab1_info, ab2_info, l1_info, l2_info}; // intalize model

    try {
        Controller c{&model, ab1_info, ab2_info}; // intalize controller
        c.HandleInput(cin, cout);
    } catch (string s) {
        cout << s << endl;
    }
}
