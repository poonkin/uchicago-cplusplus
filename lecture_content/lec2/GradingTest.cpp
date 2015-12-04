#include "Grading.h"
#include <iostream>
#include <memory>
using namespace std;
using namespace mpcs51044;

int main()
{
	Student_info jake("Jake");
	jake.midterm = 76;
	jake.final = 97;
	cout << "Enter Jake's homework grades. One on each line. Negative to quit" << endl;
	jake.read(cin);
	cout << "Jakes's grade is " << jake.grade() << endl;

	Abstract_student_info *collin = new BalancedGrading("Collin");
	collin->midterm = 80;
	collin->final = 100;
	cout << "Enter Collin's homework grades. One on each line. Negative to quit" << endl;
	collin->read(cin);
	cout << "Collin's grade is " << collin->grade() << endl;
	delete collin; // Free up object when you're done

	unique_ptr<Abstract_student_info> robin(new IgnoreHomework("Robin"));
	robin->midterm = 80;
	robin->final = 100;
	cout << "Enter Robin's homework grades. One on each line. Negative to quit" << endl;
	robin->read(cin);
	cout << "robin's grade is " << robin->grade() << endl;

	unique_ptr<UseGradingMachine> conway(new UseGradingMachine("Conway", new BalancedGradingMachine()));
	conway->midterm = 80;
	conway->final = 100;
	cout << "Enter Conway's homework grades. One on each line. Negative to quit" << endl;
	conway->read(cin);
	cout << "Conways's grade is " << conway->grade() << endl;
	conway->updateGradingMachine(new IgnoreHomeworkGradingMachine());
	cout << "Now that grading policy is changed to ignore homework. Conway's grade is " 
		 << conway->grade() << endl;

	return 0;
}