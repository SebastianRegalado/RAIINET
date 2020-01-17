#ifndef _OBSERVER_H_
#define _OBSERVER_H_

template <typename Notification> class Subject; // define type notification???!
class Cell;

template <typename Notification> class Observer {
 public:
  virtual void notify(Notification n1) = 0; // pass the Subject that called the notify method
  virtual ~Observer() = default;
};
#endif
