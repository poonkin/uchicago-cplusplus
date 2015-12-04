#include<vector>
#include<iostream>
using namespace std;
int main()
{
  vector<int> v = {1, 2}; // Init a vector of ints
  v.push_back(4); // Add an element on to the end
  for(auto it = v.begin(); it != v.end(); it++) {
    cout << *it << ", ";
  } // Prints "1, 2, 4,"
  return 0;
}
