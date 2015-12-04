#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<functional>
using namespace std;

/** I find that the Lambda works well here. Often, a functor name can serve a better
 * description than source code without a name if the operation is complicated and hard to
 * understand from a glance. Still, this operation is so simple that having the source code
 * there makes it easy to discern exactly what is being performed. It also saves us from needing
 * to construct the maxlenftn struct.
 * 
 * The lambda also allows us to use a type that is "more primitive" than a member of a class. This
 * saves us from accessing a member of the struct and allows us to simply use the value as a local variable.
 * While minor, this may be desirable by some.
 * 
 * Still, the functor is itself very lightweight. Furthermore,
 * creating a functor is a better example of DRY programming; if an operation is to be performed
 * often, it makes sense to condense it to something that is easily called as opposed to
 * explicitly stating what it is.
 * 
 * In the end, it seems that the best prior method and the lambda method are comparable in their
 * economy and effectiveness, with the "best" function winning slightly in terms of economy.
 */

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

// The lambda_style function uses a lambda to calculate the max. See above for comparison.
void lambda_style() {
	string::size_type maxlength = 0;
	for_each(names.begin(), names.end(), [&](string s) { maxlength = max(maxlength, s.size()); });
	cout << maxlength << endl;
}


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
	cout << for_each(names.begin(),names.end(),maxlenftn()).maxlen << endl;
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
  lambda_style();
  return 0;
}
