#ifndef NOTIFICATION1_H
#define NOTIFICATION1_H

class MyLink;
enum class TypeNot1 {Battle, Scan, Download, Server1, Server2, FirewallTrigger, A1, A2};

struct Notification1 {
    TypeNot1 tn1;
    MyLink *w, *l;
};

#endif
