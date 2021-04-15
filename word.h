/*
* a Word object has a key and theWord (real word)
* name() gets the real word
* wordKey() gets the key of the word
*
* every treeNode should have the Word object's key, the left/right
* a binarySearchTree is a tree of Word objects
* you can insert, erase, and delete treeNodes from the tree 
*
* the user will input a string that will be made into a Word object (and thus have a key created)
* the userinput's Word object's key will be searched for in the tree using the tree's methods
* then to get the unscrambled word, search the vector of Word objects that the tree was made from for the real word
*/
#ifndef WORD_H_
#define WORD_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <cstddef>

class Word {

	private:
		
		std::string key; 
		std::string theWord;

	public:

		//constructors
		Word();
		Word(std::string theWord2);

		//accessors
		std::string name() const;
		std::string wordKey() const;

		
		//operators
		bool operator==(const Word &other);
		bool operator<(const Word &other);
		bool operator>(const Word &other);
		bool operator>=(const Word &other);

};



#endif 