#include<iostream>

using namespace std;

template<char c>
struct Letter {
  Letter() {
    cout << c;
  }
};

struct el : virtual public Letter<'e'> {
  el() {
    cout << 'l';
  }
};

struct EL : public el {
};


struct World : public Letter<'w'>, public Letter<'o'> {
  ~World() {
    delete new Letter<'d'>();
    cout << endl;
  }
  Letter<'r'> r;
  Letter<'l'> l;
};

struct Hellx : virtual public Letter<'H'>, public EL, public el {
  Hellx(char c) {
    cout << c << " ";
  }
} hellx('o');

static World world;

int main() {
  return 0;
}
