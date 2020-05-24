#include <stdio.h>
#include <stdlib.h>

struct person{
    char *name;
    int birthyear;
    struct person *mother;
    struct person *father;
    struct person *nextperson;
    
};

void print (struct person *families){
    struct person *curr = families;
    while(curr!=NULL){
        if(curr->mother == NULL && curr->father == NULL){
            printf("name=%s birth year=%d mother=unknown father=unknown",curr->name,curr->birthyear);
        }
        else if (curr->mother == NULL)
        {
            printf("name=%s birth year=%d mother=unknown father=%s",curr->name,curr->birthyear,curr->father->name);
        }
        else if(curr->father == NULL){
            printf("name=%s birth year=%d mother=%s father=unknown",curr->name,curr->birthyear,curr->mother->name);
        }
        else{
            printf("name=%s birth year=%d mother=%s father=%s",curr->name,curr->birthyear,curr->mother->name,curr->father->name);
        }
        printf("\n");
        curr = curr->nextperson;
    }
}

struct person *findPerson(struct person *list, char *name){
    struct person *current = list;
    while(current!=NULL){
        if (!strcmp(name,current->name))
        {
            return current;
        }
        current=current->nextperson;
    }
    return NULL;
}

void addperson (struct person **families, char *name, int birthyear){
    if (!strcmp(name,"unknown"))
    {
        printf("addperson: a person cannot be called \"unknown\"\n");
        return;
    }
    else if(findPerson(*families,name)!=NULL){
        printf("addperson: person %s already exists\n",name);
        return;
    }
    
     struct person *new = (struct person *)malloc(sizeof(struct person));

    if (new == NULL)
    {
        printf("addperson: newperson == NULL");
        return;
    }
    
    new->name = (char *) malloc (sizeof(char) * (strlen(name)+1));
    strcpy(new->name,name);
    new->birthyear = birthyear;
    new->father = NULL;
    new->mother = NULL;
    new->nextperson = *families;
    *families = new;    
}


void addparents (struct person *families, char *person, char *mother, char *father){
    if(findPerson(families,person)==NULL){
        printf("person %s not found\n",person);
        return;
    }
    else if(findPerson(families,mother)==NULL){
        printf("person %s not found\n",mother);
        return;
    }
    else if(findPerson(families,father)==NULL){
        printf("person %s not found\n",father);
        return;
    }
    
    struct person *currPerson = findPerson(families,person); 
    
    if(currPerson->mother !=NULL && !strcmp(currPerson->mother->name,mother)){
        printf("person %s already has a mother %s\n",person,mother);
        return;
    }
    else if(currPerson->father !=NULL && !strcmp(currPerson->father->name,father)){
        printf("person %s already has a father %s\n",person,father);
        return;
    }
    
    currPerson->father = findPerson(families,father);
    currPerson->mother = findPerson(families,mother);

}

int ancestor (struct person *young, struct person *old, int level){
    int temp;
    if(!strcmp(young->name,old->name)){
        return level;
    }
    if(young->father !=NULL){
        temp = ancestor(young->father,old,level+1);
        if(temp!=level){
            return temp; 
        }    
    }
    if(young->mother !=NULL){
        temp = ancestor(young->mother,old,level+1);
        if(temp!=level){
            return temp; 
        }    
    }
    return level-1;
}

void removeolderpersons (struct person **families, int birthyear){
    struct person *curr = *families;
    struct person *prev = NULL;
    while(curr!=NULL){
        if(curr->birthyear < birthyear){
            if(prev==NULL){
                *families=curr->nextperson;
                prev = NULL;
            }
            else{
                prev->nextperson=curr->nextperson;
            }
            free(curr->name);
            free(curr);
            
            if(prev==NULL){
                curr=*families;            }
            else{
                curr=prev->nextperson;   
            }
        }
        else{
            if(curr->mother && curr->mother->birthyear < birthyear){
            curr->mother = NULL;
            }
            if(curr->father && curr->father->birthyear < birthyear){
                curr->father = NULL;
            }
            prev = curr;
            curr=curr->nextperson;
        }
    }
}

int main(void){
    char cmd=' ';
    struct person *families = NULL;
    char personName[100];
    char fatherName[100];
    char motherName[100];
    char youngName[100];
    char oldName[100];
    int year = 0, ancResult = 0,cYear =0;

    do{
        printf("command? ");
        scanf(" %c",&cmd);

        switch(cmd){
            case 'i':
                printf("name? ");
                scanf(" %[^\n]s",&personName);
                printf("birth year? ");
                scanf(" %d",&year);
                addperson(&families,personName,year);
            break;
            case 't':
                print(families);
            break;
            case 'p':
                printf("person? ");   
                scanf(" %[^\n]s",&personName);
                printf("mother? ");
                scanf(" %[^\n]s",&motherName);
                printf("father? ");
                scanf(" %[^\n]s",&fatherName);
                addparents(families,personName,motherName,fatherName);
            break;
            case 'k':
                printf("cut-off year? ");   
                scanf(" %d",&cYear);
                removeolderpersons(&families,cYear);
            break;
            case 'a':
                printf("young? ");   
                scanf(" %[^\n]s",&youngName);
                printf("old? ");
                scanf(" %[^\n]s",&oldName);
                if(findPerson(families,oldName)!=NULL && findPerson(families,youngName)!=NULL){
                    ancResult = ancestor(findPerson(families,youngName),findPerson(families,oldName),0);
                    switch (ancResult){
                        case -1:
                            printf("%s is not an ancestor of %s\n",oldName,youngName);
                        break;
                        case 0:
                            printf("%s is the same person as %s\n",oldName,youngName);
                        break;
                            printf("%s is a parent of %s\n",oldName,youngName);
                        case 1:
                            printf("%s is is a ",oldName);
                            for(int i =0;i<ancResult;i++){
                                printf("great ");
                            }
                            printf(" grandparent of %s",youngName);
                        break;
                        default:
                        break;
                    }
                }
            break;
        }
    }while(cmd!='q');
    printf("bye");
}

