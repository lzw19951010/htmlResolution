#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H
#include "BTree.h"
void createInvertedIndex(B_Tree &T, keyType word, DocLink (&doc)[10000],int DocID, int &TermID, MusicInfo &M);

#endif
