#include <iostream>
#include <string>

using namespace std;
class State;

class Node {
public:
    Node(State *s) : state(s) {}
    void process();
    State *state;
};

class State {
public:
    virtual void process(Node *node) = 0;
    virtual ~State() {} // Designed for inheritance
};

class QuestionState  : public State {
public:
    QuestionState(string ques, Node *yes, Node *no);
    virtual void process(Node *node);
protected:
    string question;
    Node *yesNode; // No need for smart ptrs here
    Node *noNode;  // But only in this particular case
};

class AnswerState : public State {
public:
    AnswerState(string a) : animal(a) {}
    virtual void process(Node *node);
protected:
    string animal;
};

void
Node::process()
{
    state->process(this);
}

QuestionState::QuestionState(string q, Node *y, Node *n)
  : question(q), yesNode(y), noNode(n) {}

void
QuestionState::process(Node *node)
{
    string answer;
    cout << question << " ";
    getline(cin, answer);
    if(answer == "yes" || answer == "Yes") {
        yesNode->process();
    } else {
        noNode->process();
    }
}

void
AnswerState::process(Node *node)
{
    string answer;
    cout << "Are you thinking of a " << animal << "? ";
    // cin >> answer;  // Don't mix formatted and unformatted I/O
    getline(cin, answer);
    if(answer == "yes") {
        cout << "I knew it!" << endl;
    } else {
        string newAnimal;
        cout << "Gee, you stumped me, "
             << "what were you thinking of? ";
        getline(cin, newAnimal);
        cout << "What is a question to distinguish a "
             << newAnimal << " from a " << animal << "? ";
        string newQuestion;
        getline(cin, newQuestion);
        node->state
          = new QuestionState
                 (newQuestion,
                  new Node(new AnswerState(newAnimal)),
                  new Node(node->state));
    }
}

int
main()
{
    Node root(new AnswerState("butterfly"));
    cout << "Let's play the animal game" << endl;
    for(;;) {
        cout << "Think of an animal" << endl;
        root.process();
        cout << "That was fun. Let's play again" << endl << endl;
    }
    return 0;
}
