//
// Created by ise on 12/20/22.
//
#include "Defs.h"
#ifndef GENERICADT_LINKEDLIST_H
#define GENERICADT_LINKEDLIST_H
//pointers to structs linked List
typedef struct linkedList_s *linkedList;
//pointer to struct Node
typedef struct Node_s *node;

//create node and returning if failure returning null
node createNode(Element);
//create linked list and returning if failure returning null
linkedList createLinkedList(CopyFunction copyEle, FreeFunction freeEle, PrintFunction printEle, EqualFunction equalEle);
//destroy the list and returning success or failure
status destroyList(linkedList l);
//receving list and print print element
status appendNode(linkedList l, Element e);
//destroy the node and returning success or failure
status deleteNode(linkedList l, Element e);
//receving list and print it
status displayList(linkedList l);
//returning the data of specific index
Element getDataByIndex(linkedList l, int i);
//receving list and retuning the lingth of the list 
int getLengthList(linkedList l);
//receiving list and node if the search find the node by Key
Element searchByKeyInList(linkedList l,Element e);
#endif //GENERICADT_LINKEDLIST_H
