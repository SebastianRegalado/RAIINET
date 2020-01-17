#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
using namespace std;

template <typename Notification> class Observer;

template <typename Notification> class Subject {
  vector<Observer<Notification>*> observers;
  
 public:
  void attach(Observer<Notification> *o); 
  void notifyObservers(Notification tn1);
};

template <typename Notification> 
void Subject<Notification>::notifyObservers(Notification tn1) {
  for (auto &ob : observers) ob->notify(tn1);
}

template <typename Notification>  
 void Subject<Notification>::attach(Observer<Notification> *o) {
    observers.emplace_back(o);
}

#endif
