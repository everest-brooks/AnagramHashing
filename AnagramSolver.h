/*****************************************
 ** File:    AnagramSolver.h
 ** Project: Anagram Solving by Hashing
 ** Author:  Everest Brooks
 ** Date:    May 14th, 2019
 ** E-mail:  everest1@umbc.edu
 **
 ** This file contains the function headers for
 ** the data structure class "AnagramSolver". 
 ** This is to find anagrams by hashing
 **
 ***********************************************/
#ifndef _ANAGRAMSOLVER_H
#define _ANAGRAMSOLVER_H

#include<set>
#include<string>
#include<algorithm>
#include<exception>

using namespace std;

class AnagramSolver {
 public:

  // Maximum hash table size (2^16)
  const unsigned int HT_SIZE_LIMIT = (1 << 16); 

  // Create a AnagramSolver object with hash table of size 'htSize'.  If
  // 'htSize' is greater than HT_SIZE_LIMIT or less than 1, throw a
  // range_error exception.
  AnagramSolver( int htSize );

  // Copy constructor
  AnagramSolver( const AnagramSolver& rhs );

  // Assignment operator
  AnagramSolver& operator=( const AnagramSolver& rhs );

  // Destructor
  ~AnagramSolver();

  // Insert 'line' into hash table.  Return true if a new entry is
  // created, false if the line is already in the table.
  bool insert( string line );

  // Search for 'line' in the hash table.  Return true if found, false
  // otherwise.
  bool search( string line );

  // If 'line' is in the the hash table, return its set of anagrams,
  // including 'line'.  If 'line' is not in the hash table, return an
  // emtpy set of strings.
  set<string> getAnagrams( string line );

  // Dump all non-empty lists from the hash table.  Print the hash
  // value in hexadecimal and the strings in the list.
  void dump();
  
private:
  set<string> *m_ht;     // Array of string sets
  int m_htSize;          // Size of hash table

  // Hash function.  Should hash anagrams to the same value (good
  // collision) while minimizing the number of non-anagrams that hash
  // to the same value (bad collisions).
  static unsigned int AnagramHasher( string line );

  //********************************************************
  // Private helper functions 

  // private fucntion to actually insert the anagram into the hash table
  bool m_insert(string line);

  // private function to search and return the strings, if they exist
  set<string> m_search(string line);

  // takes in the line and the hash to compare the set to the line
  bool m_compare(string line, int hash);

  //********************************************************
};
#endif