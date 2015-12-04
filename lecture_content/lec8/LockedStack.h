#ifndef LOCKED_STACK_H
#  define LOCKED_STACK_H
#include<memory>
#include<mutex>
#include<stdexcept>

namespace cspp51044 {
struct ListItem {
  ListItem(ListItem *n, int d) : next(n), data(d) {}
  ListItem *next;
  int data;
};

struct LockedStack {
  LockedStack() : first(0) {}
  int pop() {
    std::lock_guard<std::mutex> guard(lock);
    if(!first) {
      throw std::runtime_error("Can't pop from empty stack");
    }
    ListItem *oldFirst = first;
    int result = first->data;
    first = first->next;
    delete oldFirst;
    return result;
  }
  void push(int i) {
    std::lock_guard<std::mutex> guard(lock);
    ListItem *newFirst = new ListItem(first, i);
    first = newFirst;
  }
private:
  ListItem *first;
  std::mutex lock;
};
}
#endif