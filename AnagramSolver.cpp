/*****************************************
 ** File:    AnagramSolver.cpp
 ** Project: Anagram Solving by Hashing
 ** Author:  Everest Brooks
 ** Date:    May 14th, 2019
 ** E-mail:  everest1@umbc.edu
 **
 ** This file contains the functions and code for
 ** the data structure class "AnagramSolver". 
 ** This is to find anagrams by hashing
 **
 ***********************************************/
#include "AnagramSolver.h"

#include<iostream>
#include<set>
#include<string>
#include<algorithm>
#include<exception>
using namespace std;


// Default Constructor
AnagramSolver::AnagramSolver(int htSize) {

	unsigned int htSized = htSize;
	// throw errors if table sizes are out of range
	if (htSized > HT_SIZE_LIMIT ) {
		throw range_error("Hash table capacity cannot be greater than 2^16.");
	}
	if (htSized < 1) {
		throw range_error("Hash table capacity cannot be less than 2^1.");
	}

	// else create a table of the size
	m_htSize = htSize;
	m_ht = new set<string>[htSize];

}


// Copy constructor
AnagramSolver::AnagramSolver(const AnagramSolver& rhs) {

	// define new size and create new array
	m_htSize = rhs.m_htSize;
	m_ht = new set<string>[m_htSize];

	// copy over data that exists
	for (int i = 0; i < m_htSize; i++) {
		if (!m_ht[i].empty()) {
			m_ht[i] = rhs.m_ht[i];
		}
	}
}


// Assignment operator
AnagramSolver& AnagramSolver::operator=(const AnagramSolver& rhs) {

	// if same, quit
	if (this == &rhs ) {
		return *this;
	}

	// define and create new object
	m_htSize = rhs.m_htSize;
	m_ht = new set<string>[m_htSize];

	// copy data over
	for (int i = 0; i < m_htSize; i++) {
		if (!m_ht[i].empty()) {
			m_ht[i] = rhs.m_ht[i];
		}
	}
	return *this;

}


// Destructor
AnagramSolver::~AnagramSolver() {
	
	// delete entire table, then set pointer to NULL
	delete [] m_ht;
	m_ht = NULL;

}


// Insert 'line' into hash table.  Return true if a new entry is
// created, false if the line is already in the table.
bool AnagramSolver::insert(string line) {

	bool confirm = m_insert(line);
	return confirm;

}


// Search for 'line' in the hash table.  Return true if found, false
// otherwise.
bool AnagramSolver::search(string line) {

	// if searching line returns an empty string, then it does not exist
	if (m_search(line) == std::set<string>()) {
		return false;
	}
	return true;
	
}


// If 'line' is in the the hash table, return its set of anagrams,
// including 'line'.  If 'line' is not in the hash table, return an
// emtpy set of strings.
set<string> AnagramSolver::getAnagrams(string line) {

	// check if the line exists in the table
	bool exist = search(line);
	
	if (exist == true) {
		set<string> anagrams = m_search(line);
		return anagrams;
	}

	// else
	return std::set<string>();

}


// Dump all non-empty lists from the hash table.  Print the hash
// value in hexadecimal and the strings in the list.
void AnagramSolver::dump() {
	
	// iterate over the table and output the values
	cout << "Full Dump of Table\n" << endl;

	for (int i = 0; i < m_htSize - 1; i++) {
		if (!m_ht[i].empty()) {
			
			// print index
			cout << std::hex << i << endl;
			
			// cout << m_ht[i][j];
			for (const auto & it : m_ht[i]) {
				cout << "\t" << it << endl;
			}
		} 
	}
}


// Hash function.  Should hash anagrams to the same value (good
// collision) while minimizing the number of non-anagrams that hash
// to the same value (bad collisions).
unsigned int AnagramSolver::AnagramHasher(string line) {

	// create temp variable to modify 
	int hash = 0;
	string input = line;
	
	// strip whitespace
	input.erase(remove(input.begin(), input.end(), ' '), input.end());

	// sort alphabetically
	sort(input.begin(), input.end());


	// take first half and square ASCII value before adding
	// take second half and multiply each ASCII value by fibinacci index starting at 10

	int len = input.length();
	int half = len % 2;
	int num; 

	for (int i = 0; i < half; i++) {
		num = input[i];
		num = num * num;
		hash += num;
	}

	int fib; 
	int t1 = 34;
	int t2 = 55;
	for (unsigned int i = half; i < input.length(); i++) {
		num = input[i];
		num = num * fib;
		hash += num;

		// increase fibinacci
		fib = t1 + t2;
		t1 = t2;
		t2 = fib;

	}

	return hash;

}


//********************************************************
// Private Helper Functions

// private function to actually insert the anagram into the hash table
// Insert 'line' into hash table.  Return true if a new entry is
// created, false if the line is already in the table.
bool AnagramSolver::m_insert(string line) {

	int hash = AnagramHasher(line);
	if (hash > m_htSize) {
		hash = hash % m_htSize;
	}
	int origHash = hash;

	// if that position is empty, insert
	if (m_ht[hash].empty() == true) {
		m_ht[hash].insert(line);
		return true;
	}


	// loop starting at hash, until anagram set found or free space found
	bool isHere = false;
	while (isHere == false && !m_ht[hash].empty()) {

		// see if it is in that set
		isHere = search(line);
		if (isHere == true) { return false; }

		// if set is a anagram but does not contain line
		if (m_compare(line, hash) == true) {
			m_ht[hash].insert(line);
			return true;
		}

		// if anagram not in set and set not a match
		hash += 1;

		// loop over to beggining if needed
		if (hash == m_htSize) {
			hash = 0;
		}

		// if whole table has been iterated, then return false
		if (hash == origHash) {
			return false;
		}

	}

	// if free space found
	m_ht[hash].insert(line);
	return true;
	
}


// private function to find and return the strings, if they exist
set<string> AnagramSolver::m_search(string line){
	
	int hash = AnagramHasher(line);
	if (hash > m_htSize) {
		hash = hash % m_htSize;
	}
	int origHash = hash;
	bool compared = false;
	string ana = "";

	// if set exists, check to see if contained, if not, linear probing commences
	while (!m_ht[hash].empty()) {

		compared = m_compare(line, hash);

		// iterate over set to check for a line match
		if (compared == true) {
			for (const auto & it : m_ht[hash]) {
				ana = it;
				if (line == ana) {
					return m_ht[hash];
				}
			}
		}

		// reset boolean
		compared = false;

		// loop over the list as long as a match isn't found and a set isn't empty
		hash += 1;

		// loop over to beggining if needed
		if (hash == m_htSize) {
			hash = 0;
		}

		// if whole table has been iterated, then return empty set
		if (hash == origHash) {
			return std::set<string>();
		}
	}

	// else return empty set
	return std::set<string>();

}


// takes in the line and the hash to compare the set to the line
bool AnagramSolver::m_compare(string line, int hash) {

	// verify that set is anagram
	
	// create temp variables to modify 
	string input = line;
	string index;
	for (const auto & it : m_ht[hash]) {
		index = it;
		break;
	}

	// strip whitespace
	input.erase(remove(input.begin(), input.end(), ' '), input.end());
	index.erase(remove(index.begin(), index.end(), ' '), index.end());

	// sort alphabetically
	sort(input.begin(), input.end());
	sort(index.begin(), index.end());


	// compare
	if (input == index) {
		return true;
		// isAna = true;
	}

	return false;

}
//********************************************************