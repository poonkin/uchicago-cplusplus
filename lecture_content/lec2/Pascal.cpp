#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;

typedef vector<int> Row;
typedef vector<Row> Triangle;

Row
nextRow(Row row)
{
    Row result;
    int previous = 0;
    for (auto elt : row) {
        result.push_back(previous + elt);
        previous = elt;
    }
    result.push_back(previous);
    return result;
}

const int size = 12;

int
numDigits(int i)
{
    int digits = 1;
    while((i/=10) != 0) {
        digits++;
    }
    return digits;
}

int
numDigits_alternate(int i)
{
	ostringstream os;
	os << i;
	return os.str().size();
}

int eltSize;

string
centeredInt(int i)
{
    ostringstream os;
    os << i;
    string str = os.str();
    return string((eltSize - str.size())/2, ' ') + str;
}

void
printRow(Row row)
{
    for(auto elt: row) {
        cout << left << setw(eltSize) << centeredInt(elt) << " ";
    }
    cout << endl;
}

void
printTriangle(Triangle triangle)
{
    Row lastRow = triangle[size - 1];
    // g++ doesn't like the following code because it defines extra std::max functions
    // It's actually surprising the Visual C++ accepts it
    //
    // int maxElement = accumulate(lastRow.begin(), lastRow.end(), 0, max<int>);
    //
    // use this instead
    int maxElement = *max_element(lastRow.begin(), lastRow.end());
    eltSize = numDigits(maxElement);
    for(int i = 0; i < size; i++) {
        string spaces((size - i - 1) * (eltSize + 1) / 2, ' ');
        cout << spaces;
        printRow(triangle[i]);
    }
}


int
main()
{
    Triangle triangle;
    Row previousRow;
    previousRow.push_back(1);
    for(int i = 0; i < size; i++) {
        triangle.push_back(previousRow);
        previousRow = nextRow(previousRow);
    }
    printTriangle(triangle);
    return 0;
}