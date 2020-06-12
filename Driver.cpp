/*****************************************
 ** File:    Driver.cpp
 ** Project: Anagram Solving by Hashing
 ** Author:  Everest Brooks
 ** Date:    May 14th, 2019
 ** E-mail:  everest1@umbc.edu
 **
 ** This driver file contains file opening 
 ** functionality and creates and insatnce of 
 ** the class AnagramSolver
 **
 ***********************************************/
#include "AnagramSolver.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

  AnagramSolver aS( 1 << 16 );  // Table of size 2^16

  // Read the sample data an insert into the hash table.

  string fileName = "anagrams.txt";
  ifstream inFp( fileName );

  if ( inFp.is_open() ) {
    string line;
    while ( getline( inFp, line ) ) {
      if ( line.size() > 0 ) {
	aS.insert( line );
      }
    }
    inFp.close();
  } else {
    cerr << "File " << fileName << " could not be opened\n";
  }

  // Use getAnagrams to retrieve the anagrams of "wired".

  cout << "wired:\n";
  auto ana = aS.getAnagrams("wired");
  for (auto itr = ana.begin(); itr != ana.end(); itr++)
    cout << "   " << *itr << endl;
  cout << endl;

  // Dump the contents of the hash table.

  cout << "Full dump of table:\n";
  aS.dump();
  
  return 0;
}
  
  