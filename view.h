#ifndef VIEW_H
#define VIEW_H
#include <vector>
#include <iostream>
#include "subject.h"
#include "observer.h"
#include "notification2.h"
#include "window.h"
#include "posn.h"

using namespace std;

class View {
    Xwindow w;
    bool graphics = false;
    
  public:
    View(bool g);
    void display(ostream& output, string s);
    void displayText(ostream& output, string s);
};

#endif
