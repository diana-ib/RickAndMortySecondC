//
// Created by ise on 11/26/22.
//
#include "Defs.h"
#include "Jerry.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
planets* initPlanet(char * name ,double x, double y, double z){
    planets * newPlanet=(planets*)malloc(sizeof (planets));
    if(newPlanet==NULL){
        return NULL;
    }
    newPlanet->name= (char *) malloc(strlen(name)+1);
    if(newPlanet->name==NULL){
        free(newPlanet);
        return NULL;
    }
    strcpy(newPlanet->name,name);
    newPlanet->x=x;
    newPlanet->y=y;
    newPlanet->z=z;
    return newPlanet;
}

origin* initOrigin(char* d){
    origin* newOrigin=(origin*) malloc(sizeof (origin));
    if(newOrigin==NULL){
        return NULL;
    }
    else{
        newOrigin->dimenesion=(char*)malloc(strlen(d)+1);
        if(newOrigin->dimenesion==NULL){
            free(newOrigin);
            return NULL;
        }
        strcpy(newOrigin->dimenesion,d);
    }

    return newOrigin;
}

physical* initPhysicalCharacteristics(char * name, double value){
    physical * newAttribute= (physical*) malloc(sizeof (physical));
    if(newAttribute==NULL){
        return NULL;
    }
    newAttribute->name=(char *) malloc(strlen(name)+1);
    if(newAttribute->name==NULL){
        free(newAttribute);
        return NULL;
    }
    strcpy(newAttribute->name,name);
    newAttribute->attributeValue=value;
    return newAttribute;
}

jerry* initJerry(char* id, int happiness ,char* o ,planets *p ){
    jerry* j=(jerry* ) malloc(sizeof (jerry));
    if(j==NULL){
        return NULL;
    }
    else{
        j->id=(char*) malloc(strlen(id)+1);
        if(j->id==NULL){
            free(j);
            return NULL;
        }
        strcpy(j->id,id);
        if(happiness>=0 && happiness<=100){
            j->happinesslevel=happiness;
        }
        j->attributeNum=0;
        j->p=NULL;

        j->orig=initOrigin(o);
        if(p==NULL){
            free(j->orig->dimenesion);
            free(j->id);
            free(j);
            return NULL;
        }
        j->planet=p;
    }

    return j;
}
bool checkPhysicalCharacteristics(jerry* j, char* name){
    if(j==NULL || name==NULL)
        return false;
    if(j->attributeNum==0)
        return false;
    else{
        for(int i=0; i< j->attributeNum; i++){
            if(strcmp(name, j->p[i]->name)==0) {
                return true;
            }
        }
    }
    return false;

}


void addAttribute(jerry* j,char * p, double num ){
    if(j==NULL || p==NULL)
        return;
    if(j->p==NULL){
        j->p=(physical**)malloc(sizeof (physical*));
    }
    if(checkPhysicalCharacteristics(j,p)){
        return;
    }
    else{
        j->attributeNum++;
        j->p=(physical**) realloc(j->p,(sizeof(physical*))* (j->attributeNum));
        if(j->p==NULL){
            free(j->p);
            return;}
        j->p[j->attributeNum-1]=initPhysicalCharacteristics(p, num);
    }


}

status removeAttribute(jerry* j, char* name){
    int i;
    if(j==NULL || name==NULL)
        return failure;
    if(j->p==NULL){
        return failure;
    }
    int s=-1;
    for(i=0;i<j->attributeNum;i++) {
        if(strcmp(j->p[i]->name,name)==0) {
            free(j->p[i]->name);
            free(j->p[i]);
            s=i;
            i++;
        }
        if(s!=-1){
            j->p[s]=j->p[i];
            s++;
        }
    }
    j->attributeNum--;
    j->p=(physical**) realloc(j->p,sizeof(physical*)*j->attributeNum);
    return success;
}




status printPlanet(planets* p){
    if(p==NULL){
        return failure;
    }
    printf("Planet : %s (%.2f,%.2f,%.2f) \n",p->name,p->x,p->y,p->z);
    return success;
}

status printJerry(jerry* j){
    if( j==NULL){
        return failure;
    }
    if(j->attributeNum==0) {
        printf("Jerry , ID - %s : \n", j->id);
        printf("Happiness level : %d \n", j->happinesslevel);
        printf("Origin : %s \n", j->orig->dimenesion);
        printPlanet(j->planet);
        return success;
    }
    if(j->attributeNum>0) {
        printf("Jerry , ID - %s : \n", j->id);
        printf("Happiness level : %d \n", j->happinesslevel);
        printf("Origin : %s \n", j->orig->dimenesion);
        printPlanet(j->planet);
        printf("Jerry's physical Characteristics available : \n\t");
        for(int i=0; i<j->attributeNum-1;i++){
            printf("%s : %.2f ",j->p[i]->name,j->p[i]->attributeValue);
            printf(", ");
        }
        printf("%s : %.2f \n",j->p[j->attributeNum-1]->name,j->p[j->attributeNum-1]->attributeValue);
        return success;
    }
    return  success;
}
void deletePlanet(planets* p){
    if(p ==NULL)
        return;
    if(p->name!=NULL)
        free(p->name);
    free(p);
}
void deleteOrigin(origin* o){
    if(o==NULL)
        return;
    if(o->dimenesion!=NULL)
        free(o->dimenesion);
    free(o);
}
void deletejerry(jerry* j){

    if(j==NULL)
        return;
    if(j->id!=NULL)
        free(j->id);
    if(j->orig!=NULL)
        deleteOrigin(j->orig);
    if(j->p!=NULL){
        for(int i=0; i< j->attributeNum ;i++){
            free(j->p[i]->name);
            free(j->p[i]);
        }
    }
    free(j->p);
    free(j);
}

// the value is JERRY
Element copyjerry (Element j){
    return j;
}
status freeJerry (Element j){
    if(j==NULL){
        return failure;
    }
    return success;
}


// the key is jerry ID
Element copyJID(Element id){
    if(id==NULL)
        return NULL;
    char* key=(char*)malloc(strlen(id)+1);
    if(key==NULL)
        return NULL;
    strcpy(key,id);
    return (key);
}

status freeJID(Element id){
    if(id==NULL)
        return failure;
    free((char *)id);
    return success;
}
status printJID(Element id){
    if(id==NULL)
        return failure;
    char* key=(char*)malloc(strlen(id)+1);
    if(key==NULL)
        return failure;
    strcpy(key,(char*)id);
    printf("id:%s",key);
    free(key);
    return success;
}

bool equaljerry( jerry *j, char* id){
    if(j==NULL ||id==NULL)
        return false;
    return equaljerryID(j->id,id);
}

bool equaljerryID( char* j, char* id){
    if(j==NULL ||id==NULL)
        return false;
    if(strcmp(j,id)==0)
        return true;
    return false;
}

int transformJkeyIntoNumber(char *id){
    if(id==NULL)
        return 0;
    int sum=0;
    int len= strlen(id);
    for(int i=0;i<len;i++){
        sum+=(int)id[i];
    }
    return (sum);
}
// the key is PhysicalCharacteristics of jerry
Element copyJAtt(Element att){
    if(att==NULL)
        return NULL;
    char* key=(char*)malloc(strlen(att)+1);
    if(key==NULL)
        return NULL;
    strcpy(key,att);
    return (key);
}
//freeing key, PhysicalCharacteristics of jerry
status freeJAtt(Element att){
    if(att==NULL)
        return failure;
    free((char *)att);
    return success;
}
//printing PhysicalCharacteristics of jerry the key
status printJatt(Element att){
    if(att==NULL)
        return failure;
    char* key=(char*)malloc(strlen(att)+1);
    if(key==NULL)
        return failure;
    strcpy(key,(char*)att);
    printf("id:%s",key);
    free(key);
    return success;

}

