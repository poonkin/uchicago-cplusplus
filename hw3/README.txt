README.txt

Michael Blumenshine
MPCS 51044
Readme for HW 3
Due: 29 January 2015

HW 3.1

The program utilizes two classes. One initializes the ios while constructing and also adds a little comma
between Hello and World while destructing. This class is called ForceInit. The other class, Hello_World, 
first creates a static ForceInit and then prints Hello while constructing. It prints World while destructing.
From the comments in the program:

The sequence of events:
 * First, a Hello_World is declared and its constructor called. Its constructor instantiates
 * ForceInit, and then prints "Hello" JUST AFTER ForceInit's constructor inits cout. In stack
 * fashion, the ForceInit destructor is called first as the program exits, which prints ", ".
 * Finally, the Hello_World destructor is called, which prints "world!" and endl. The end.
 
HW 3.2

Fairly straight forward. The example code from HW 3.2 was used pretty much verbatim 
in main (with one slight modification, as ostream_iteratorrequired cout and the string, 
not just the ", " string). I assumed that using this code was desired, and that we were simply
supposed to write the Nth_Power class. Writing the functor was fairly straight forward.
This implementation accepts and returns an int. If a vector of doubles is transformed, they will
lose precision. This was intended; the example code uses a vector of ints, so this functionality
was assumed to be desired.

HW 3.3

Which is better?
 
I would argue that for most purposes, dynamic cast is better. It didn't allow
us to break the polymorphic relationship; indeed the C-pointer allowed us to
do whatever we wanted, which could have resulted in trying to access certain
members that don't exist.

reinterpret_cast would do a bitwise reinterpretation, giving us full access
to the functionality of the other object. This makes reinterpret_cast the
desired choice in this scenario of allowing C-style behavior.

HW 3.4

Please see the .txt file for my answer.

HW 3.5

The game works by having a class for animals, which track the name, questions and answers associated
with them, and their scores (compared to an array of "answers" that the user gives each time the
user plays). The questions are a struct which contain the question text itself, the id of the question (a unique identifier)
and the answer. A QuestionList class is a vector of Questions with additional helper methods. An animal contains
a QuestionList of known questions and answers pertaining to it, while there is a master_list of all
questions which is traversed each time the game is played.

Please see the comments in the source file for more information.

HW 3.6

To avoid compile warnings and linker errors, we need one additional step.
By hiding the call in another function, we get the behavior we desire.
What happens:

Actual output:
pure virtual method called
terminate called without an active exception
Aborted (core dumped)

Exit code:
------------------
(program exited with code: 134)

