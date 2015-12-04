// HW8-4.cpp

/* 
Michael Blumenshine
C++
HW 8 Problem 4 Extra credit
Due: 5 March 2015
*/

/** The issue with the article pertains to move constructors. With move,
 * one is actually moving the ORIGINAL class and members. In this case,
 * a mutex is moved during a move construction, whereas with a copy
 * constructor it cannot be moved. Furthermore, and perhaps more importantly
 * (and also I say with more confidence), there is an issue if one thread
 * is accessing an object that was just moved. A move operation MOVES
 * the class and members to another location. Any thread trying to access
 * the old variable will be left empty-handed.
 */
