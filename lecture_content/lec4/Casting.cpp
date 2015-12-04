#include<iostream>
#include<string>
using namespace std;

struct Dog  {
  virtual void takeWalk() { cout << "Let's take a walk" << endl; }
  int bones;
  virtual ~Dog() {}
};

struct Cat  {
  virtual void catchMouse() { cout << "Pounce..." << endl; }
  virtual void sleepAllDay() { cout << "Snore..." << endl; }
  int catToys;
  virtual ~Cat() {}
};

struct FamilyMember  {
  void doStuff() {
    cout << "Coming home" << endl;
  }
  string favoriteComputerGame;
  virtual ~FamilyMember() {}
};

struct Fido : public Dog, public FamilyMember {
};

int main() {
  Fido *fido = new Fido;
  Dog *dog = fido;
  FamilyMember *fm = fido;
  cout << "(Cat *)dog = " << (Cat *)dog << endl;
  cout << "dynamic_cast<Cat *>(dog) = " << dynamic_cast<Cat *>(dog) << endl;
  ((Cat *)dog)->catchMouse();
  // ((Cat *)dog)->sleepAllDay();
  if(dynamic_cast<Cat *>(dog)) {
    dynamic_cast<Cat *>(dog)->catchMouse();
  }

  cout << "reinterpret_cast<Fido *>(fm) = " << reinterpret_cast<Fido *>(fm) << endl;
  cout << "dynamic_cast<Fido *>(fm) = " << dynamic_cast<Fido *>(fm) << endl;
//  (reinterpret_cast<Fido *>(fm))->takeWalk();
  dynamic_cast<Fido *>(fm)->takeWalk();
};

