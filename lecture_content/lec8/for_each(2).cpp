#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<functional>
using namespace std;

struct maxlenftn {
	maxlenftn() { maxlen = 0; }
    void operator()(string s) {
		maxlen = max(maxlen,s.size());
	}
	string::size_type maxlen;
};

vector<string> names = {
	"Spertus", "Lemon", "Golden", "Melhus"
};
void wrong() {
	maxlenftn maxf;
	for_each(names.begin(),names.end(),maxf);
	cout << maxf.maxlen << endl;
}

void better() {
	maxlenftn maxf;
	for_each(names.begin(),names.end(), ref(maxf));
	cout << maxf.maxlen << endl;
}

void best() {
	cout << for_each(names.begin(),names.end(), maxlenftn()).maxlen << endl;
}

void lambda() {
  size_t maxlen;
  for_each(names.begin(), names.end(), [&maxlen](string s) { maxlen = max(maxlen, s.size()); });
  cout << maxlen << endl;
}

struct maxlenftn2 {
	maxlenftn2() { maxlen = 0; }
    void operator()(string s) {
		maxlen = max(maxlen,s.size());
	}
	static string::size_type maxlen;
};

string::size_type maxlenftn2::maxlen;

void bad() {
	maxlenftn2 maxf;
	for_each(names.begin(),names.end(),maxf);
	cout << maxf.maxlen << endl;
}

int main()
{
  wrong();
  bad();
  better();
  best();
  lambda();
  return 0;
}
