# RickAndMortySecondC
JerryBoree: JerryBoreeMain.o HashTable.o Jerry.o KeyValuePair.o LinkedList.o MultiValueHashTable.o
	gcc JerryBoreeMain.o HashTable.o Jerry.o KeyValuePair.o LinkedList.o MultiValueHashTable.o -o JerryBoree
HashTable.o: HashTable.c KeyValuePair.h Defs.h LinkedList.h HashTable.h
	gcc -c HashTable.c
JerryBoreeMain.o: JerryBoreeMain.c Defs.h LinkedList.h Jerry.h MultiValueHashTable.h HashTable.h KeyValuePair.h
	gcc -c JerryBoreeMain.c
Jerry.o: Jerry.c Defs.h Jerry.h
	gcc -c Jerry.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h Defs.h LinkedList.h HashTable.h  
	gcc -c MultiValueHashTable.c
clean:
	rm -f *.o

