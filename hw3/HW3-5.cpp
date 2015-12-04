// HW3-5.cpp

/* 
Michael Blumenshine
MPCS 51044
Homework 3, Problem 5
Due: 29 January 2015
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <climits>

// Some functions that I've taken from earlier C++ assignments --
// especially those for valid input checking -- require these preprocessor
// definitions.
#define TRUE 1
#define FALSE 0

using namespace std;

// The function check_range is a template function which checks
// whether a given value of template type is within the range
// of [min,max], also of type T. If so, it returns TRUE (1).
// Else it returns FALSE (0).
template<typename T>
int check_range(T min, T max, T value)
{
	if (value >= min && value <= max)
		return TRUE;
	else return FALSE;
}

// A Question is a struct which contains a string that represents the
// actual question, an id which uniquely identifies questions from the
// master_list of all questions (see main), and the answer (1 if true,
// 0 if false).
struct Question
{
	Question(string question, long id, int answer)
	{
		this->question = question;
		this->id = id;
		this->answer = answer;
	}
	string question;	// the text of the question
	long id;			// unique identifier for all questions if used properly
	int answer;			// 1 if TRUE, 0 if FALSE
};				

// A question list is a list of questions with some helpful member functions.
// It only has a default no-argument constructor. 
class QuestionList
{
public:
	//	Its destructor ensures that
	// every Question struct in its "questions" vector is deleted and that the
	// "questions" vector is cleared.
	~QuestionList()
	{
		for (size_t i = 0; i < questions.size(); ++i)
			delete questions[i];
			
		questions.clear();
	}
	
	// This checks a question list for whether or not a particular question exists in that list.
	// It uses the question's id field to do so. This is useful for adding new questions with new
	// answers to old animals that have already appeared but haven't been updated. I.e. if I added
	// a cat early in the game but then thought of cat much later, with a much longer list of
	// questions than existed at the time cat was last thought of.
	bool does_question_exist(long id)
	{
		for (size_t i = 0; i < this->questions.size(); ++i)
		{
			if (id == questions[i]->id)
				return true;
		}
		return false;
	}
	
	// Getter function for the size of the questions vector, the vector of all Question structs.
	size_t get_size() { return questions.size(); }
	
	// Returns a pointer to a Question struct, kept at index i in the questions vector.
	Question* get_question(int i) { return questions[i]; }
	
	// Adds a pointer to a new Question to the vector list, calling the constructor for a struct.
	void add_question(string question, long id, int answer) 
	{
		questions.push_back(new Question(question, id, answer));	
	}

private:
	vector<Question*> questions;	// This vector contains pointers to all the Questions for a particular animal, or for the master_list.
	
};

// An Animal represents a particular animal saved and known to the program.
// It has one constructor, which requires that a string animal_name be passed,
// which represents the name. Further, it initializes the score to 0, which
// is used to determine the best guess per the answers to questions.
// It contains fields for the score, the animal_name, and the QuestionList for the individual animal.
class Animal
{
public:
	Animal(string animal_name) { this->animal_name = animal_name; this->score = 0; }
	
	// This function adds a question to the QuestionList of known questions and answers
	// pertaining to this animal.
	void add_question(string question, long id, int answer)
	{
		if (!(this->local_questions.does_question_exist(id)))		// it first calls the QuestionList member function does_question_exist
			this->local_questions.add_question(question, id, answer);	// to ensure that it isn't adding the same question more than once.
	}
	
	// The function calc_score takes an array of ints that represents the current answer selection of the user per round
	// and the size of answer_arr at this stage in the game. It resets a previous score to 0 and then calculates all the
	// matches. If a mismatch is found, it returns -1, which represents that this animal is impossible given the user's
	// answers. The reason calc_score is needed is that one animal might not have any mismatches, but one might have
	// more matches and thus is a better guess. I.e., I insert dog and say "Does it have fur?", then play and say yes, but answer cat, then
	// insert question "Does it meow?" then think of cat again and answer yes twice, dog would have only one known match and no mismatches, 
	// but cat would have two known matches and no mismatches, thus cat would be a better guess.
	void calc_score(int * answer_arr, int size)
	{
		this->score = 0;
		int total_score = 0;
		
		// For all of the users answers,
		for (int j = 0; j < size; ++j)
		{
			// for each of the questions known to this animal,
			for (size_t k = 0; k < this->local_questions.get_size(); ++k)
			{
				// if this question matches one of the animals questions
				if (this->local_questions.get_question(k)->id == j)
				{
					// and if the answers match
					if (this->local_questions.get_question(k)->answer == answer_arr[j])
					{
						++total_score;	// increase the score by one.
					}
					else {
						this->score = -1;	// else make it known that this animal cannot work, set its score so
						return;				// and return.
					}
				}
			}
		}
		
		this->score = total_score;		// set the animals score, to be retrieved with the next function below.
	}
	
	// Getter method for the score field.
	int get_score() { return this->score; }
	// Getter method for the animal's name, stored in animal_name.
	string get_name() { return this->animal_name; }

private:
	QuestionList local_questions;		// QuestionList of all the questions pertaining to an instance of an animal.
	string animal_name;					// string representing the animal's name.
	int score;							// Score as compared against an array of the user's answers.
};

// Function prototypes
void init_game(QuestionList* master_list, vector<Animal*> &animal_list, int &answer, string &temp_str, long & current_id);
void play_game(QuestionList* master_list, vector<Animal*> &animal_list, int &answer, string &temp_str, long & current_id, int &animal, int &choice);
int get_int(int min, int max);		// The following is used for getting valid inputs.
void convert_answer(int& value);
void flush_input();

int main()
{
	QuestionList *master_list = new QuestionList;
	vector<Animal*> animal_list;
	string temp_str;
	long current_id = 0;
	int answer, animal;
	int choice = TRUE;
	
	cout << "Welcome to the Animal Game!" << endl << endl;
	
	init_game(master_list, animal_list, answer, temp_str, current_id);
	
	while (choice == TRUE)
	{		
		play_game(master_list, animal_list, answer, temp_str, current_id, animal, choice);	
	}
	
	std::cout << std::endl << "Thanks for playing!" << std::endl << std::endl;
	
	// Clearing the vector of animals, deleting each object before calling clear.
	for (size_t i = 0; i < animal_list.size(); ++i)
		delete animal_list[i];
		
	animal_list.clear();
	delete master_list;	// Deleting the master_list, whose destructor will take care of the Questions individually.
	
	return EXIT_SUCCESS;
}

// The init_game function initializes the game and the initial state that is required to play the game.
// In this case, this only consists of an initial animal and an initial question. Initial initial initial.
void init_game(QuestionList* master_list, vector<Animal*> &animal_list, int &answer, string &temp_str, long & current_id)
{
	cout << "Please enter the first animal: ";
	cin >> temp_str;
	
	flush_input();
	
	animal_list.push_back(new Animal(temp_str));
	
	cout << "Please enter a yes/no question that distinguishes this animal <press enter twice>: ";
	std::getline(std::cin, temp_str, '\n');
	
	flush_input();
	
	cout << "Is the answer..." << endl << "1) Yes" << endl << "2) No" << endl << "Enter: ";
	
	answer = get_int(1,2);
	convert_answer(answer);
	
	animal_list[0]->add_question(temp_str, current_id, answer);
	master_list->add_question(temp_str, current_id++, answer);
}

// The actual running of the game.
void play_game(QuestionList* master_list, vector<Animal*> &animal_list, int &answer, string &temp_str, long & current_id, int &animal, int &choice)
{
	int answer_arr[master_list->get_size()];
		animal = animal_list.size();
		
		cout << endl << "Now think of any animal (can be the one you just entered). I'm going to ask you some questions..." << endl << endl;
		
		for (size_t i = 0; i < master_list->get_size(); ++i)
		{
			cout << master_list->get_question(i)->question << endl << "Is the answer..." << endl << "1) Yes" << endl << "2) No" << endl << "Enter: ";
			answer_arr[i] = get_int(1,2);
			convert_answer(answer_arr[i]);	
		}
		
		for (size_t i = 0; i < animal_list.size(); ++i)
			animal_list[i]->calc_score(answer_arr, master_list->get_size());
		
		int max = -1;
		int max_i = -1;
		for (size_t i = 0; i < animal_list.size(); ++i)
		{
			if (animal_list[i]->get_score() > max)
			{
				max = animal_list[i]->get_score();
				max_i = i;
			}
		}
		
		if (max == -1)
		{
			cout << endl << "No animal I know is possible with the answers to the questions." << endl;
			answer = FALSE;
		}
		else {
			cout << endl << "Is the animal you're thinking of a " << animal_list[max_i]->get_name() << "?" 
				<< endl  << "1) Yes" << endl << "2) No" << endl << "Enter: ";
			
			answer = get_int(1,2);
		}
		
		if (answer == TRUE)
		{
			cout << endl << "I win!!!" << endl << endl;
			
			for (size_t i = 0; i < animal_list.size(); ++i)
			{
				if (animal_list[max_i]->get_name() == animal_list[i]->get_name())
				{	
					animal = i;
					break;
				}
			}
			
			for (size_t i = 0; i < master_list->get_size(); ++i)
			{
				animal_list[animal]->add_question(master_list->get_question(i)->question, master_list->get_question(i)->id, answer_arr[master_list->get_question(i)->id]);
			}
		}
		else {
			cout << endl << "What animal were you thinking of? Enter: ";
			cin >> temp_str;
			
			flush_input();
			
			animal = animal_list.size();
			bool found = false;
			
			for (size_t i = 0; i < animal_list.size(); ++i)
			{
				if (temp_str == animal_list[i]->get_name())
				{	
					found = true;
					animal = i;
					break;
				}
			}
	
			if (!found)
			{
				animal_list.push_back(new Animal(temp_str));
				cout << "I've learned a new animal!" << endl;
				cout << "Please enter a yes/no question that distinguishes this animal <press enter twice>: ";
			}
			else
			{
				cout << "I should have got that one!" << endl;
				cout << "Why not enter another yes/no question to help me out <press enter twice>: ";
			}
			
			std::getline(std::cin, temp_str, '\n');
			
			flush_input();
	
			cout << "Is the answer..." << endl << "1) Yes" << endl << "2) No" << endl << "Enter: ";
	
			answer = get_int(1,2);
			convert_answer(answer);
			
			for (int i = 0; i < current_id; ++i)
			{
				animal_list[animal]->add_question(master_list->get_question(i)->question, master_list->get_question(i)->id, answer_arr[master_list->get_question(i)->id]);
			}
			animal_list[animal]->add_question(temp_str, current_id, answer);
			master_list->add_question(temp_str, current_id++, answer);
		}
		
		
		cout << "Would you like to play again?" << endl;
		cout << "1) Yes" << endl << "2) No" << endl << "Enter: ";
		choice = get_int(1,2);
}


int get_int(int min, int max)
 {	
	int value;
	int valid_input = FALSE;
	
	while (!valid_input)
	{
		//std::cin.ignore(INT_MAX);
		if (cin >> value)
		{
			if (check_range(min, max, value))		// call to template check_range function
				valid_input = TRUE;			// valid int and range
			else cout << "Out of valid range from " << min << " to " << max << "! Please enter again: ";	// valid input but out of range
		}
		else 
		{
			cout << "Invalid! Please enter a valid integer: ";			// printed if user had bad input, no range consideration
		}
		std::cin.clear();					// clear and ignore are used for CRLF input
		std::cin.ignore(INT_MAX, '\n');
	}
	
	return value;
 }
 
 void convert_answer(int& value)
 {
	 if (value != TRUE)
		value = FALSE;
 }
 
 void flush_input()
 {
	 std::cin.clear();					// clear and ignore are used for CRLF input
	 std::cin.ignore(INT_MAX, '\n');
 }
