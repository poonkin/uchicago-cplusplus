#include<iostream>
using namespace std;

struct Greeter {
public:
  Greeter() {
    cout << "Hello world" << endl;
  }
};

Greeter greeter;

int main()
{
  return 0;
}
