#include "binarySearchTree.h"
#include "word.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstddef>
#include <vector>
#include <iterator>

using namespace std;

int main() {

	//vector to hold the dictionary 
	vector<Word> dictionary; 

	//string to hold the words from the inputfile
	string temp; 

	//Word object to be made from the strings read in 
	//to be added to the dictionary vector of Word objects
	Word words;
	
	
	ifstream inputfile; 
	inputfile.open("english_words.txt");

	//making Word objects from the words read in from the inputfile and putting them in a vector
	while (inputfile >> temp) {

		//making Word objects from the english dictionary words will give each word a key
		//a key can map to more than one word
		words = Word(temp);
		//the dictionary vector stores the Word objects
		dictionary.push_back(words);

	}

	//bst of Word objects
	binarySearchTree<Word> theDictionary; 

	for (int i = 0; i < dictionary.size(); i++) {
		theDictionary.insert(dictionary[i]);
	}
	cout << "Test of find words" << endl << endl;

	cout << "The dictionary has been built with " << theDictionary.size() << " keys in the dictionary" << endl;


	//reading in the scrambled words to see if they are in the binarySearchTree
	//read in scrambled word, make a Word object out of the scrambled word => now it has a key
	//find the wordToUnscramble's key inside the tree of Word objects (compare the Word object's key to the scrambled word's key) 
	//get the word to unscramble's name from the vector dictionary
	string wordToUnscramble = "";
	Word wToUnscramble;

	while (wordToUnscramble != "quit-now") {

		cout << "Word to unscramble (quit-now to stop):" << endl;

		getline(cin, wordToUnscramble);

		//make wordToUnscramble a Word object
		wToUnscramble = Word(wordToUnscramble);

		//if the wordToUnscramble's key is found in theDictionary tree
		if (theDictionary.find(wToUnscramble, nullptr) == true) {

			//go through the dictionary vector and compare the found key to the words read in the dictionary vector
			//once it finds a match, add it to the string theRealWord
			string theRealWord = "";
			for (int i = 0; i < dictionary.size(); i++) {
				if (wToUnscramble.wordKey() == dictionary[i].wordKey()) {
					//space to separate each diff word added (since one key can map to multiple words)
					theRealWord = theRealWord + dictionary[i].name() + " ";
				}
			}

			//to count the amount of words the key mapped to
			int numRealWords = 1;

			for (int i = 0; i < theRealWord.size(); i++) {

				//space everytime a word is added
				if (theRealWord[i] == ' ') {
					numRealWords++;
				}
			}

			if (numRealWords > 2) {
				cout << endl << "Scrambled word " << wordToUnscramble << " maps to words: " << theRealWord << endl << endl;
			}
			else {
				cout << endl << "Scrambled word " << wordToUnscramble << " maps to word: " << theRealWord << endl << endl;
			}
			
		}

		//end if user input is quit now
		else {
			if (wordToUnscramble == "quit-now") {
				return 0;
			}
			else {
				cout << endl << "Scrambled word " << wordToUnscramble << " was not found" << endl << endl;
			}
			
		}
	}



	system("pause");
	return 0;
}
