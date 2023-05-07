#include <stdio.h>
#include "Defs.h"
#include "LinkedList.h"
#include "Jerry.h"
#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "KeyValuePair.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
//auxilary functions

//FOUNDTHISPLANET
//checks if there is planets with the same name and returns it
//else: returns null
planets* foundthisPLANET(planets** p,char* pName, int num){
    int f=0;
    if(p==NULL||pName==NULL)
        return NULL;
    for(int i=0;i<num; i++){
        if(strcmp(p[i]->name,pName)==0){
            return p[i];
        }
        f++;
    }
    if(f==num){
        return NULL;
    }
}
// printing all jerries with same attrbute
status printJerryByAtt(multiH mh,char* att){
    if(mh==NULL|| att==NULL)
        return failure;
    linkedList l=lookupInMultiValueHashTable(mh,att);
    if(l==NULL)
        return failure;
    printf("%s : \n",att);
    if(displayList(l)==success)
        return success;
}
//convert lowercase to uppercase
char* wordUpper(char* a){
    if(a==NULL){
        printf("Memory Problem");
        return NULL;
    }
    char* upper= (char*)malloc(strlen(a)+1);
    if(upper==NULL){
        printf("Memory Problem");
        return NULL;
    }
    strcpy(upper,a);
    for(int i=0;i< strlen(a);i++){
        upper[i]=(toupper(a[i]));
    }
    return upper;

}
//counts lines in file
int countlines(char *filename)
{
    // count the number of lines in the file called filename
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=0;

    if (fp == NULL)
        return 0;

    lines++;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }
    fclose(fp);
    return lines;
}
double getPhval(jerry* j, char* att){
    for(int i=0;i<j->attributeNum;i++){
        if(strcmp(att,j->p[i]->name)==0){
            return j->p[i]->attributeValue;
        }
    }
}
jerry * mostsuitable(linkedList l, char* att, double val){
    if(l==NULL|| att==NULL|| getLengthList(l)==0)
        return NULL;
    double min;
    jerry * thisJerry;
    if(getLengthList(l)==1){
        return (getDataByIndex(l,1));
    }else {
        jerry *j = getDataByIndex(l, 1);
        min = fabs(val - getPhval(j, att));
        thisJerry = j;
        for (int i = 1; i < getLengthList(l); i++) {
            j = getDataByIndex(l, i + 1);
            if (fabs(val - getPhval(j, att)) < min) {
                min = fabs(val - getPhval(j, att));
                thisJerry = j;
                if (min == 0)
                    return thisJerry;
            }
        }
    }

    return thisJerry;
}

//MAIN
int main(int argc, char* argv[]) {
    int numberOfPlanets=atoi(argv[1]);
    
    int i;
    FILE *pFile;
    int lines= countlines(argv[2]);
    pFile= fopen(argv[2],"r");
    char line[300];
    char s[3] = ",";
    char *token;
    int p;
    char *jer[4];
    char *pl[4];
    char* att[2];
    int hashNumber=11;

    planets *newplanets[numberOfPlanets];

    multiH multiht =createMultiValueHashTable(copyJAtt, freeJAtt, printJatt, (CopyFunction)copyjerry, (FreeFunction)freeJerry, (PrintFunction)printJerry, (EqualFunction)equaljerryID,(EqualFunction) equaljerry, (TransformIntoNumberFunction)transformJkeyIntoNumber, hashNumber);
    linkedList newJerreis = createLinkedList(copyjerry, (FreeFunction)deletejerry, (PrintFunction )printJerry, (EqualFunction) equaljerry);

    hashTable jerriesht=createHashTable(copyJID, freeJID,  printJID,  copyjerry, (FreeFunction) freeJerry, (PrintFunction) printJerry, (EqualFunction)  equaljerryID, (TransformIntoNumberFunction) transformJkeyIntoNumber, hashNumber);

    if (pFile == NULL)
        return 0;

    // planet word
    fgets(line, 300, pFile);
    //ALL PLANETS
    fgets(line, 300, pFile);

    for (i = 0; i < numberOfPlanets; i++) {
        p = 0;
        token = strtok(line, s);
        while (token != NULL) {
            pl[p] = token;
            token = strtok(NULL, s);
            p++;
        }
        newplanets[i] = initPlanet(pl[0], atof(pl[1]), atof(pl[2]), atof(pl[3]));
        if(newplanets[i]== NULL){
            printf("Memory Problem");
        }


        fgets(line, 300, pFile);

    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //ALL JERREIS
    fgets(line, 300, pFile);
    int j ;
    char attn[300];
    double value;
    //ALL JERREIS
    jerry * jer1;
    for (j = numberOfPlanets+2 ; j <lines; j++) {
        i=0;
        jer[i] = strtok(line, s);

        i++;
        while (i < 4) {
            jer[i] = strtok(NULL, ",\n");
            i++;
        }
        for (i = 0; i < numberOfPlanets; i++) {
            if (strcmp(newplanets[i]->name, jer[2]) == 0) {
                    jer1=initJerry(jer[0], atoi(jer[3]), jer[1], newplanets[i]);
                    if(!jer1){
                        printf("Memory Problem");
                    }
                    addToHashTable(jerriesht, jer[0],jer1);
                    appendNode(newJerreis,jer1);
                break;
            }
        }



        fgets(line, 300, pFile);
        //    //JERRY'S Attribute
        while(line[0] == '\t') {
            j++;
            if(j<lines) {
                token = strtok(line, "\t:\r");
                strcpy(attn, token);
                token = strtok(NULL, ":\n\r");
                if (token == NULL) { break; }
                value = atof(token);
                addAttribute(jer1, attn, value);
                addToMultiValueHashTable(multiht,attn,jer1);
                /*printf("att:%s\nvalue:%.2f\n",attn,value);*/
                fgets(line, 300, pFile);
            }

        }

    }
    fclose(pFile);
    bool done=true;
    char number=-1;
    char number1=-1;
    char input[300];
    while(done) {
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf("%s", input);
        if(strlen(input)>1){
            number='a';
        } else{
            number=input[0];
        }
        char jerryName[30];
        char physicalAtt[300] ;
        double attValue;

        int f;
        char planetsName[300];
        char dimension[300];
        int happy=0;
        char inp[300];
        jerry * jerry1;
        int happylevel;
        switch (number) {
            case '1':
                f=0;
                //displayHashElements(jerriesht);
                printf("What is your Jerry's ID ? \n");
                scanf("%s", jerryName);
               jerry * j=lookupInHashTable(jerriesht,jerryName);
                //if jerry is found in hash table O(1)
                if((j)!=NULL){
                    //print an error message andback to the main menu
                    printf("Rick did you forgot ? you already left him here ! \n");
                    break;
                }
                //if jerry not found in hash table
                else
                {
                    //we will ask for the planet name it come from
                    printf("What planet is your Jerry from ? \n");
                    scanf("%s", planetsName);
                    //check if this planet is found
                    planets * p=foundthisPLANET(newplanets,planetsName, numberOfPlanets);
                    if(p!=NULL){
                        printf("What is your Jerry's dimension ? \n");
                        scanf("%s",dimension);
                        printf("How happy is your Jerry now ? \n");
                        scanf("%d",&happy);
                        //add this jerry to hash table
                        jerry1= initJerry(jerryName,happy,dimension,p);
                        if(addToHashTable(jerriesht,jerryName ,jerry1)==success){
                            printJerry(jerry1);
                        }
                        appendNode(newJerreis,jerry1);
                        break;
                    }
                    //if the planets not found
                    else
                    {
                        printf("%s is not a known planet ! \n",planetsName);
                        break;
                    }
                }
            case '2':

                printf("What is your Jerry's ID ? \n");
                scanf("%s", jerryName);
                jerry * j1=lookupInHashTable(jerriesht,jerryName);
                //if jerry is found in hash table O(1)
                if(j1!=NULL){
                    printf("What physical characteristic can you add to Jerry - %s ? \n",jerryName);
                    scanf("%s",physicalAtt);
                    //if there are physical characteristic with same name of physicalAtt

                    if(checkPhysicalCharacteristics(j1,physicalAtt)==true){
                        printf("The information about his %s already available to the daycare ! \n",physicalAtt);
                        break;
                    }
                    //the physical characteristic not found on system
                    else{
                        printf("What is the value of his %s ? \n",physicalAtt);
                        scanf("%lf",&attValue);
                        if(addToMultiValueHashTable(multiht,physicalAtt,j1)==success){
                            addAttribute(j1,physicalAtt,attValue);
                            printJerryByAtt(multiht,physicalAtt);
                            break;
                        }

                    }
                }
                //jerry not found
                else
                {
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }

                break;

            case '3':
                printf("What is your Jerry's ID ? \n");
                scanf("%s", jerryName);
                jerry * j2=lookupInHashTable(jerriesht,jerryName);
                //if jerry is found in hash table O(1)
                if(j2!=NULL)
                {
                    printf("What physical characteristic do you want to remove from Jerry - %s ? \n",jerryName);
                    scanf("%s",physicalAtt);
                    if(checkPhysicalCharacteristics(j2,physicalAtt)==true) {
                        linkedList l = lookupInMultiValueHashTable(multiht, physicalAtt);
                        if (l != NULL) {
                            jerry *j3 = searchByKeyInList(l, jerryName);
                            if (j2 == j3) {
                                removeFromMultiValueHashTable(multiht,physicalAtt,j3->id);
                                removeAttribute(j2, physicalAtt);
                                printJerry(j2);
                                break;

                            }
                        }
                    }

                    else
                    {
                        printf("The information about his %s not available to the daycare ! \n",physicalAtt);
                    }
                    break;
                }
                //jerry not found
                else
                {
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }

            case '4':
                printf("What is your Jerry's ID ? \n");
                scanf("%s", jerryName);
                jerry * j3=lookupInHashTable(jerriesht,jerryName);
                //if jerry is found in hash table O(1)
                if(j3!=NULL)
                {
                    removeFromHashTable(jerriesht,jerryName);
                    for(int i=0; i<j3->attributeNum;i++) {
                        removeFromMultiValueHashTable(multiht,j3->p[i]->name,j3->id);
                    }
                    deleteNode(newJerreis,jerryName);
                    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                    break;
                    }
                else{
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }

            case '5':
                printf("What do you remember about your Jerry ? \n");
                scanf("%s",physicalAtt);
                linkedList l=lookupInMultiValueHashTable(multiht,physicalAtt);
                if(l!=NULL){
                    printf("What do you remember about the value of his %s ? \n",physicalAtt);
                    scanf("%lf",&attValue);
                    printf("Rick this is the most suitable Jerry we found : \n");
                    jerry * j4=mostsuitable(l, physicalAtt, attValue);
                    printJerry(j4);
                    removeFromHashTable(jerriesht,j4->id);
                    for(int i=0;i<j4->attributeNum;i++){
                    removeFromMultiValueHashTable(multiht,physicalAtt,j4->id);
                    }
                    deleteNode(newJerreis,j4->id);

                    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                    break;
                }
                else{
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n",physicalAtt);
                    break;
                }
            case '6': {
                int length=getLengthList(newJerreis);
                int sad;
                jerry *sadJerry;
                    if(length>0){
                        jerry *j = getDataByIndex(newJerreis, 1);
                        sad=j->happinesslevel;
                        sadJerry=j;
                        for(int i=1;i<length;i++){
                            jerry *j = getDataByIndex(newJerreis, i+1);
                            if(j->happinesslevel<sad){
                                sad=j->happinesslevel;
                                sadJerry=j;
                            }
                        }
                        printf("Rick this is the most suitable Jerry we found : \n");
                        printJerry(sadJerry);
                        removeFromHashTable(jerriesht,sadJerry->id);
                        for(int i=0;i<sadJerry->attributeNum;i++){
                            removeFromMultiValueHashTable(multiht,physicalAtt,sadJerry->id);
                        }
                        deleteNode(newJerreis,sadJerry->id);
                        printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                    }
                    else{
                        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                        break;
                    }

                break;
            }
            case '7':
                number1=-1;
                printf("What information do you want to know ? \n");
                printf("1 : All Jerries \n");
                printf("2 : All Jerries by physical characteristics \n");
                printf("3 : All known planets \n");
                scanf("%s",inp);
                if(strlen(inp)==1) {
                    number1=inp[0];} else{
                    number1='D';
                }
                    switch (number1) {
                        case '1':

                            if (getLengthList(newJerreis) == 0)
                                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                            else {
                                displayList(newJerreis);
                            }
                            break;

                        case '2':
                            printf("What physical characteristics ? \n");
                            scanf("%s", physicalAtt);
                            if (lookupInMultiValueHashTable(multiht, physicalAtt) != NULL) {
                                printJerryByAtt(multiht, physicalAtt);
                            } else {
                                printf("Rick we can not help you - we do not know any Jerry's %s ! \n", physicalAtt);

                            }
                            break;

                        case '3':
                            for ( i = 0; i < numberOfPlanets; i++) {
                                printPlanet(newplanets[i]);
                            }
                            break;

                        default:
                            printf("Rick this option is not known to the daycare ! \n");
                            break;
                    }


                break;
            case '8':

                //there are at least one jerry
                number1=-1;
                if (getLengthList(newJerreis) >=1) {
                    printf("What activity do you want the Jerries to partake in ? \n");
                    printf("1 : Interact with fake Beth \n");
                    printf("2 : Play golf \n");
                    printf("3 : Adjust the picture settings on the TV \n");
                    scanf("%s", inp);
                    if (strlen(inp) == 1) {
                        number1 = inp[0];
                    } else{
                        number1 = 'J';
                    }

                        switch (number1) {
                            case '1':
                                for (int i = 0; i < getLengthList(newJerreis); i++) {
                                    jerry *j = getDataByIndex(newJerreis, i + 1);
                                    if (j->happinesslevel >= 20) {
                                        happylevel = j->happinesslevel + 15;
                                        if (happylevel <= 100) {
                                            j->happinesslevel += 15;
                                        } else {
                                            j->happinesslevel = 100;
                                        }
                                    }

                                    if (j->happinesslevel <= 19) {
                                        happylevel = j->happinesslevel - 5;
                                        if (happylevel >= 0) {
                                            j->happinesslevel -= 5;
                                        } else {
                                            j->happinesslevel = 0;
                                        }
                                    }

                                }
                                printf("The activity is now over ! \n");
                                displayList(newJerreis);
                                break;
                            case '2':
                                for (int i = 0; i < getLengthList(newJerreis); i++) {
                                    jerry *j = getDataByIndex(newJerreis, i + 1);
                                    if (j->happinesslevel >= 50) {
                                        happylevel = j->happinesslevel + 10;
                                        if (happylevel <= 100) {
                                            j->happinesslevel += 10;
                                        } else {
                                            j->happinesslevel = 100;
                                        }
                                    }
                                    if (j->happinesslevel <= 49) {
                                        happylevel = j->happinesslevel - 10;
                                        if (happylevel >= 0) {
                                            j->happinesslevel -= 10;
                                        } else {
                                            j->happinesslevel = 0;
                                        }
                                    }

                                }
                                printf("The activity is now over ! \n");
                                displayList(newJerreis);
                                break;
                            case '3':
                                for (int i = 0; i < getLengthList(newJerreis); i++) {
                                    jerry *j = getDataByIndex(newJerreis, i + 1);
                                    happylevel = j->happinesslevel + 20;
                                    if (happylevel <= 100) {
                                        j->happinesslevel += 20;
                                    } else {
                                        j->happinesslevel = 100;
                                    }
                                }
                                printf("The activity is now over ! \n");
                                displayList(newJerreis);
                                break;


                            default:
                                printf("Rick this option is not known to the daycare ! \n");
                                break;

                        }


                        break;


                }
                //there are no jerries
                else {
                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                break;
                     }

            case '9':
                destroyHashTable(jerriesht);
                destroyList(newJerreis);
                destroyMultiValueHashTable(multiht);
                for(int i=0;i<numberOfPlanets;i++){
                    deletePlanet(newplanets[i]);
                }
                printf("The daycare is now clean and close ! \n");
                done = false;
            break;
            default:
                printf("Rick this option is not known to the daycare ! \n");
        }
    }

    return 0;
}