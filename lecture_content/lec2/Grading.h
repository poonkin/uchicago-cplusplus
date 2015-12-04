#ifndef GRADING_H
#  define GRADING_H
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
using std::istream;
using std::string;
using std::vector;
using std::accumulate;

namespace mpcs51044 {

struct Student_info {
	// Student has no grades at the start of the  class
	Student_info(string studentName) : name(studentName), midterm(0), final(0) {}
	string name;
	double midterm, final;
	vector<double> homework;

	istream& read(istream &is) {
		for(;;) {
			double hw;
			is >> hw;
			if (hw < 0)
				break;
			homework.push_back(hw);
		}
		return is;
	}

	double grade() const;
};  // Semicolon is required!

struct Abstract_student_info { // In header  
	string name;
	double midterm = 0;
	double final = 0;
	vector<double> homework;
	Abstract_student_info(string name) : name(name) {}

	istream& read(istream &is) {
		for (;;) {
			double hw;
			is >> hw;
			if (hw < 0)
				break;
			homework.push_back(hw);
		}
		return is;
	}
	// This class doesn't specify a grading strategy.
	virtual double grade() const = 0;

};

struct BalancedGrading : public Abstract_student_info {
	// using Abstract_student_info::Abstract_student_info; // C++11 inheriting constructors not supported in Visual Studio 2013
	BalancedGrading(string name) : Abstract_student_info(name) {} // Not needed on Clang/g++ if you comment out the above line
	virtual double grade() const override {
		double avg = accumulate(homework.begin(), homework.end(), 0.0) / homework.size();
		return (midterm + final + avg) / 3;
	}
};
struct IgnoreHomework : public Abstract_student_info {
	// using Abstract_student_info::Abstract_student_info; // C++11 inheriting constructors not supported in Visual Studio 2013
	IgnoreHomework(string name) : Abstract_student_info(name) {} // Not needed on Clang/g++ if you comment out the above line
	virtual double grade() const {
		return (midterm + final) / 2;
	}
};

struct UseGradingMachine;
struct GradingMachine {
	virtual double grade(UseGradingMachine const *) = 0;
};

struct UseGradingMachine {
	UseGradingMachine(string studentName, GradingMachine *initialGradingMachine) { // Constructor 
		name = studentName;
		gradingMachine = initialGradingMachine;
	}  

	~UseGradingMachine() {
		delete gradingMachine; 
	}

	void updateGradingMachine(GradingMachine *newGradingMachine) {
		delete gradingMachine;
		gradingMachine = newGradingMachine;
	}

	GradingMachine *gradingMachine;
	string name;
	double midterm = 0, final = 0;
	vector<double> homework;

	istream& read(istream &is) {
		for (;;) {
			double hw;
			is >> hw;
			if (hw < 0)
				break;
			homework.push_back(hw);
		}
		return is;
	}

	double grade() const {
		return gradingMachine->grade(this);
	}

};

struct BalancedGradingMachine : public GradingMachine {
	virtual double grade(UseGradingMachine const *student) {
		double avg = accumulate(student->homework.begin(), student->homework.end(), 0.0) / student->homework.size();
		return (student->midterm + student->final + avg) / 3;
	}
};
struct IgnoreHomeworkGradingMachine : public GradingMachine {
	virtual double grade(UseGradingMachine const *student) {
		return (student->midterm + student->final) / 2;
	}
};
}
#endif