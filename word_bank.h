/********
This file describes the type of data and
tells the main program that the word bank exists.
********/

#ifndef WORD_BANK_H
#define WORD_BANK_H

#include <string>

using namespace std;

struct WordEntry {
    string word;
    string clue;
    string definition;
};

extern const WordEntry wordBank[];
extern const int wordBankSize;

#endif