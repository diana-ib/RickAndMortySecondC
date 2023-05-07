//
// Created by ise on 11/26/22.
//
#include "Defs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef MANAGEJERRIES_C_JERRY_H
#define MANAGEJERRIES_C_JERRY_H

typedef struct planet_s{
    char * name;
    double x,y,z;
}planets;

typedef struct origin_s{
    char* dimenesion;
}origin;

typedef struct PhysicalCharacteristics{
    char *name;
    double attributeValue;
}physical;
typedef struct createJerry{
    char * id;
    int attributeNum;
    int happinesslevel;
    struct planet_s* planet;
    struct origin_s* orig;
    struct PhysicalCharacteristics** p;
}jerry;
//create new planet. return null if fails.
planets* initPlanet(char * name ,double x, double y, double z);
//create new origin. return null if fails.
origin* initOrigin(char* d);
//create new Physical Characteristics. return null if fails.
physical* initPhysicalCharacteristics(char * name, double value);
//create new jerry. return null if fails.
jerry* initJerry(char* id, int happiness ,char* o,planets *p );
//check if jerry has the Physical Characteristics and return true if there else return false
bool checkPhysicalCharacteristics(jerry* j, char* name);
//allocate a new Physical Characteristics and add it to jerry 
void addAttribute(jerry* j,char * p, double num );
//deleted the Physical Characteristics from jerry and reterun fails or success
status removeAttribute(jerry* j, char* name);
//print Jerry
status printJerry(jerry* j);
//print Planet
status printPlanet(planets* p);
//deallocates the planet
void deletePlanet(planets* p);
//deallocates the Origin
void deleteOrigin(origin* o);
//deallocates the jerry
void deletejerry(jerry* j);
//the four funtion 
//deallocates the jerry
status freeJerry (Element j);
//chcking if the jerry has id same id
bool equaljerry( jerry *j, char* id);
// jerry function(vlue of the linked list in hash table)
//chcking if the elements is equal if they have same id
bool equaljerryID( char* j, char* id);
//copying key value pair of jerry
Element copyjerry (Element j);
//ID function(key in linked list of the hash table
// copying key , id of jerry
Element copyJID(Element id);
//freeing key, id of jerry
status freeJID(Element id);
//printing id of jerry the key
status printJID(Element id);
//convert the key (id) to number
//convert the key (PhysicalCharacteristics) to number
int transformJkeyIntoNumber(char * id);
//attrbute function
// copying key , PhysicalCharacteristics of jerry
Element copyJAtt(Element att);
//freeing key, PhysicalCharacteristics of jerry
status freeJAtt(Element att);
//printing PhysicalCharacteristics of jerry the key
status printJatt(Element att);


#endif //MANAGEJERRIES_C_JERRY_H