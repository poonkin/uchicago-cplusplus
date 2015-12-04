#include<thread>
#include<iostream>
#include<vector>
#include<algorithm>
#include<mutex>
using namespace std;

mutex ioMutex;

void thrFunc()
{
  for(int i = 0; i < 100; i++) {
    lock_guard<mutex> guard(ioMutex);
    cout << "Thread " << this_thread::get_id() << " looped " << i << " times" << endl;
  }
}

int main()
{
  vector<thread> vt;
  for(int i = 0; i < 4; i++) {
    vt.emplace_back(thrFunc);
  }
  for_each(vt.begin(), vt.end(), [](thread &t) { t.join(); });
  return 0;
}