#include "view.h"
using namespace std;

View::View(bool g):graphics{g} {}

void View::display(ostream& output, string s) {
    if (graphics) {
        int diff = 186; 
        int size = 50;
        bool pp1 = 1;
        if(s[7] == '2') pp1 = 0;

        w.fillRectangle(0, 0, 500, 40, 0);
        w.fillRectangle(0, 450, 500, 40, 0);

        //Your information
        w.drawBigString(20, 20, s.substr(0, 9));
        w.drawBigString(20, 30, s.substr(10, 18));
        w.drawBigString(20, 40, s.substr(29, 12));

        //Enemy's information
        w.drawBigString(20, 470, s.substr(186, 9));
        w.drawBigString(20, 480, s.substr(196, 18));
        w.drawBigString(20, 490, s.substr(215, 12));

        for(int c = 0; c < 8; ++c) { // go through grid columns
            for(int r = 0; r < 8; ++r) { // go through grid rows
                char c1 = s[105 + 9*c + r]; // go through players information
                if((r==3 && c==0)||(r==4 && c==0)||(r==3 && c==7)||(r==4 && c==7)) {
                    w.fillRectangle(r * size + 30, c * size + 50, size, size, 4);
                } else if(c1 != '.') {
                    if(c1 == 'm') {
                        if(pp1) w.fillRectangle(r * size + 30, c * size + 50, size, size, 6);
                    } else if (c1 == 'w') {
                        if(!pp1) w.fillRectangle(r * size + 30, c * size + 50, size, size, 6);
                    } else {
                        char c2 = 'x';
                        if(c1 == 'a' && pp1) c2 = s[45];
                        else if(c1 == 'a') c2 = s[45+diff];
                        if(c1 == 'b' && pp1) c2 = s[52];
                        else if(c1 == 'b') c2 = s[52+diff];
                        if(c1 == 'c' && pp1) c2 = s[59];
                        else if(c1 == 'c') c2 = s[59+diff];
                        if(c1 == 'd' && pp1) c2 = s[66];
                        else if(c1 == 'd') c2 = s[66+diff];
                        if(c1 == 'e' && pp1) c2 = s[72];
                        else if(c1 == 'e') c2 = s[72+diff];
                        if(c1 == 'f' && pp1) c2 = s[79];
                        else if(c1 == 'f') c2 = s[79+diff];
                        if(c1 == 'g' && pp1) c2 = s[86];
                        else if(c1 == 'g') c2 = s[86+diff];
                        if(c1 == 'h' && pp1) c2 = s[93];
                        else if(c1 == 'h') c2 = s[93+diff];
                        if(c1 == 'A' && pp1) c2 = s[231];
                        else if(c1 == 'A') c2 = s[231-diff];
                        if(c1 == 'B' && pp1) c2 = s[238];
                        else if(c1 == 'B') c2 = s[238-diff];
                        if(c1 == 'C' && pp1) c2 = s[245];
                        else if(c1 == 'C') c2 = s[245-diff];
                        if(c1 == 'D' && pp1) c2 = s[252];
                        else if(c1 == 'D') c2 = s[252-diff];
                        if(c1 == 'E' && pp1) c2 = s[258];
                        else if(c1 == 'E') c2 = s[258-diff];
                        if(c1 == 'F' && pp1) c2 = s[265];
                        else if(c1 == 'F') c2 = s[265-diff];
                        if(c1 == 'G' && pp1) c2 = s[272];
                        else if(c1 == 'G') c2 = s[272-diff];
                        if(c1 == 'H' && pp1) c2 = s[279];
                        else if(c1 == 'H') c2 = s[279-diff];

                        if(c2 == 'V') {
                            w.fillRectangle(r * size + 30, c * size + 50, size, size, 2);
                        } else if (c2 == 'D') {
                            w.fillRectangle(r * size + 30, c * size + 50, size, size, 3);
                        } else {
                            w.fillRectangle(r * size + 30, c * size + 50, size, size, 5);
                        }
                    }
                    w.drawBigString(r * size + 52, c * size + 77, s.substr(105 + 9*c + r, 1));
                } else {
                    w.fillRectangle(r * size + 30, c * size + 50, size, size, 1);
                }
            }
        }
    }
    displayText(output, s); 
}

void View::displayText(ostream& output, string s) { // display output to output screen
    output << s << endl;
};
