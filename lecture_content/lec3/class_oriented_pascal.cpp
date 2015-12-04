#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;

int
numDigits(int i)
{
	ostringstream os;
	os << i;
	return os.str().size();
}

class Triangle {
public:
	Triangle(int n);
private:
	friend ostream &operator<<(ostream &, Triangle);
	void addRow()
	{
		Row row = rows[rows.size() - 1];
		Row result;
		int previous = 0;
		for (Row::iterator it = row.begin(); it != row.end(); it++) {
			result.push_back(previous + *it);
			previous = *it;
		}
		result.push_back(previous);
		rows.push_back(result);
	}
    int maxElement() const {
		Row lastRow = rows[rows.size() - 1];
		return *max_element(lastRow.begin(), lastRow.end());
	}

	string centeredInt(int i)
	{
		ostringstream os;
		os << i;
		string str = os.str();
		return string((eltSize - str.size())/2, ' ') + str;
	}

	void
	printRow(int i)
	{
		Row row = rows[i];
		for(Row::iterator it = row.begin(); it != row.end(); it++) {
			cout << left << setw(eltSize) << centeredInt(*it) << " ";
		}
		cout << endl;
	}
	typedef vector<int> Row;
	vector<Row> rows;
	size_t eltSize;
};


const int size = 12;

Triangle::Triangle(int n)
{
	Row startingRow; // Get things started
	startingRow.push_back(1); // With a row with only a 1
	rows.push_back(startingRow);
	for(int i = 1; i < n; i++) {
		addRow();
	}
	eltSize = numDigits(maxElement());
}

ostream&
operator<<(ostream &os, Triangle triangle)
{
    for(int i = 0; i < size; i++) {
        string spaces((size - i - 1) * (triangle.eltSize + 1) / 2, ' ');
        os << spaces;
        triangle.printRow(i);
    }
	return os;
}


int
main()
{
    Triangle triangle(size);
    cout << triangle;
    return 0;
}
