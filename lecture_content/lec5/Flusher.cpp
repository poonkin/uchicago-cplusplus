#include<iostream>
using namespace std;
void g();
int h();

class Flusher {
public:
  Flusher(ostream &_os) : os(_os) {}
  ~Flusher() {
    os.flush();
  }
private:
  ostream &os;
};

int f() {
  Flusher flusher(cout);
  cout << "Some text";
  g(); // g and h are functions whose
  cout << h(); // definitions are unknown
  return 0;
}
