#include "word.h"
#include <algorithm>

//constructors
//every Word object (scrambled word that is user input) has a key and the word that the key maps to 
Word::Word() {
	key = "";
	theWord = "";
}


Word::Word(std::string theWord2) {
	
	theWord = theWord2;
	key = theWord2;

	for (unsigned int i = 0; i < theWord.length(); i++) {
		//first step to making the key for the scrambled word 
		//is setting the key to the scrambled word and setting everything to lower case
		key[i] = tolower(key[i]);
	}

	//sortin the key in alphabetical order
	std::sort(key.begin(), key.end());
}


std::string Word::name() const {
	return theWord;
}

std::string Word::wordKey() const {

	std::string key1 = theWord;

	for (unsigned int i = 0; i < theWord.length(); i++) {
		key1[i] = tolower(key1[i]);
	}

	std::sort(key1.begin(), key1.end());

	return key1;
}


//operators
bool Word::operator==(const Word &other) {

	//if the two Word objects have the same wordKey then they are the same "word"
	if (key.compare(other.wordKey()) == 0) {
		return true;
	}
	else {
		return false;
	}

}

bool Word::operator>(const Word &other) {

	if (key.compare(other.wordKey()) > 0) {
		return true;
	}
	else {
		return false;
	}

}

bool Word::operator<(const Word &other) {

	if (key.compare(other.wordKey()) < 0) {
		return true; 
	}
	else {
		return false;
	}

}

bool Word::operator>=(const Word &other) {
	if (key.compare(other.wordKey()) == 0 || key.compare(other.wordKey()) > 0) {
		return true;
	}
	else {
		return false;
	}
}

