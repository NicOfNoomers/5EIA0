#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "pynqlib.h"



#define HEIGHT 30
#define WIDTH 40
#define SnakeSize 20
#define nmrBtns 4

struct pos{
  int x;
  int y;
  struct pos *next;
};

struct ttl {
    int x;
    int y;
    int value;
    int ttl;
    struct ttl *next;
};

// Function Delcarations

    // Functions for killerBlocks
void print_ttl (struct ttl *head); // �b� command
struct ttl *lookup_ttl (struct ttl *head, int x, int y);
struct ttl *insert_new_ttl (struct ttl *head, int x, int y, int ttl); // �i� command
void update_ttl (struct ttl *head); // �u� command
struct ttl *remove_ttl (struct ttl *head); // �r� command


    // Functions for snake 
void print_pos (struct pos *head); // �s� command
struct pos *lookup_pos (struct pos *head, int x, int y); // �l� command
struct pos *add_new_pos (struct pos *head, int x, int y); // �f� command
struct pos *remove_last_pos (struct pos *head); // �t� command
void play(void);



void update_ttl (struct ttl *head){
    struct ttl *current = head;
    while(current!=NULL){
        current->ttl--;
        current = current->next;
    }
}


void print_list (struct pos *head)
{
    struct pos *curr = head;
    printf("[");
    while (curr != NULL) {
        if (head != curr) printf (",");
        printf("(%d,%d)",curr->x,curr->y);
        curr = curr->next;
    }
    printf("]\n");
}


void print_ttl (struct ttl *head)
{
    struct ttl *curr = head;
    printf("[");
    while (curr != NULL) {
        if (head != curr) printf (",");
        printf("(%d,%d,%d,%d)",curr->x,curr->y,curr->value,curr->ttl);
        curr = curr->next;
    }
    printf("]\n");
}


struct pos *lookup_pos (struct pos *head, int x, int y){
// True if it finds the key
// False if it does not find the key
    struct pos *curr = head;
    while (curr != NULL) {
        if(curr->x == x && curr->y == y){
            return 1;
        }
        else{
            curr = curr->next;   
        }
    }
    return 0;
}

struct ttl *lookup_ttl (struct ttl *head, int x, int y){
// True if it finds the key
// False if it does not find the key
    struct ttl *curr = head;
    while (curr != NULL) {
        if(curr->x == x && curr->y == y){
            return 1;
        }
        else{
            curr = curr->next;   
        }
    }
    return 0;
}

struct pos *add_new_pos (struct pos *head, int x, int y){
    if(!lookup_pos(head,x,y)){
        struct pos *new;
        new = (struct pos*) malloc (sizeof(struct pos));
        if (new == NULL) {
            printf("insert: error: no space left\n");
            return head;
        }
        new->x = x;
        new->y = y;
        new->next = head;
        return new;
    }
    else{
        printf("Position (%d,%d) is already in the list\n");
        return head;
    }
}

struct pos *add_new_ttl (struct ttl *head, int x, int y,int ttl){
    if(!lookup_ttl(head,x,y)){
        struct ttl *prev = NULL;
        struct ttl *curr = head;
        struct ttl *new;
        new = (struct ttl*) malloc (sizeof(struct ttl));
        if (new == NULL) {
            printf("insert: error: no space left\n");
            return head;
        }
        new->x = x;
        new->y = y;
        new->value = ttl;
        new->ttl = ttl;

        if(head != NULL){
            while(curr!=NULL && (curr->ttl)<ttl){
                prev = curr;
                curr = curr->next;
            }
            if (prev == NULL)
            {
                new->next = head;
                return new;
            }
            else{
                new->next = curr;
                prev->next = new;
                return head;
            }
        }
        return new;
    }
    else{
        printf("Position (%d,%d) is already in the list\n");
        return head;
    }
}

struct pos *remove_last_pos (struct pos *head){
    // Removes last element on the right of the list pof pointers
    if(head != NULL){
        struct pos *previous = head;
        struct pos *temp = head;
        while (temp->next!= NULL){
            previous = temp;  
            temp = temp->next;
        }
        if (temp == head){ 
            previous = NULL;
        }
        else{
            previous->next = NULL;
            previous = head;
        }
        free(temp);
        return previous;
    }
}

struct ttl *remove_last_ttl (struct ttl *head){
    // Removes last element on the right of the list pof pointers
    if(head != NULL){
        struct ttl *finished = NULL;
        struct ttl *previous = NULL;
        struct ttl *current = head;
        while(current!=NULL && current->ttl<=0){
            finished = current;
            free(current);
            current = finished->next;
        }
        return current;
    }
    return NULL;
}

struct ttl *remove_ttl (struct ttl *head){
    // Removes last element on the right of the list pof pointers
    if(head != NULL){
        struct ttl *finished = NULL;
        struct ttl *previous = NULL;
        struct ttl *current = head;
        while(current!=NULL && current->ttl>0){
            finished = current;
            current = current->next;
        }
        while(current!=NULL){
            previous = current;
            // set_pixel(current->y,current->x,0,0,0);
            free(current);
            current = previous->next;
        }        
        if (finished == NULL){
            return NULL;
        }
        else{
            finished->next = NULL;
            return head;
        }
    }
    return NULL;
}

// void play(void)
// {
//     pixel displaybuffer[HEIGHT][WIDTH];
//     init_display(HEIGHT, WIDTH, 10, displaybuffer);
//     int y = HEIGHT/2, x = WIDTH/2, ydir = 0, xdir = 1;
//     int initialSnakeLength = 6;
//     struct pos *snakeHead=NULL;
//     int counter=0;
//     int delay = 200;

//     struct ttl *killers = NULL;
//     int maxkiller = 10; // max # killer blocks at any time
//     int killerprob = 20; // percent
//     int killerduration = 20; // measured in loop iterations
//     int bonus_prob = 30; // in percent
//     int bonus_duration = 40; // between 10 and 10+bonus_duration

//     snakeHead = add_new_pos(snakeHead,x,y);
//     for (int i = 0; i < initialSnakeLength; ++i)
//     {
//         x++;
//         snakeHead = add_new_pos(snakeHead,x,y);
//         set_pixel(y,x,0,255,0);
//     }

//     do {
//         update_ttl(killers);
//         killers = remove_ttl(killers);
//         if (!(counter % 10))
//         {
//             // Increment pixels by one every 10 iterations
//             snakeHead = add_new_pos(snakeHead,x,y);
//             set_pixel(y,x,0,255,0);
//             y = (y+ydir + HEIGHT)%HEIGHT;
//             x = abs(x+xdir + WIDTH)%WIDTH;
//         }
//         if (rand()%100 < killerprob) {
//             int killerx = rand()%WIDTH;
//             int killery = rand()%HEIGHT;
//             if(!lookup_pos(snakeHead,killerx,killery) && !lookup_ttl(killers,killerx,killery)){
//                 killers = add_new_ttl(killers,killerx,killery,killerduration);
//                 set_pixel(killery,killerx,255,0,0);
//             }
//         }

//         snakeHead = add_new_pos(snakeHead,x,y);
//         set_pixel(y,x,0,255,0);
//         set_pixel(y,x,0,0,255);
//         struct pos *temp;
//         temp = remove_last_pos(snakeHead);
//         set_pixel(temp->y,temp->x,0,0,0);
        

//         if (lookup_ttl(killers,x,y))
//         {
//             break;
//         }

//         draw_display();
//         set_pixel(y,x,0,255,0);
//         y = (y+ydir + HEIGHT)%HEIGHT;
//         x = abs(x+xdir + WIDTH)%WIDTH;


//         if (lookup_pos(snakeHead,x,y))
//         {
//             break;
//         }
        
//         // Struct to find the btn longest time pressed
//         struct Btn
//         {
//             int btnNumber;
//             int btnTime;
//         };
//         struct Btn clickedBtn;
//         sleep_msec_buttons_pushed(delay); // sets button_states[]
//         clickedBtn.btnNumber = 0;
//         clickedBtn.btnTime = button_states[0];
//         for (int i = 1; i < nmrBtns; ++i)
//         {
//             if (clickedBtn.btnTime<button_states[i])
//             {
//                 clickedBtn.btnNumber = i;
//                 clickedBtn.btnTime = button_states[i];      
//             }
//         }
//         // clickedBtn is the struct that contains the longest time pressed btn

//         if (clickedBtn.btnTime>0)
//         {
//             switch(clickedBtn.btnNumber){
//                 case 0:
//                 // Move right
//                     if (!lookup_pos(snakeHead,abs((snakeHead->x)-1),snakeHead->y) && !lookup_pos(snakeHead,((snakeHead->x)+1)%WIDTH,snakeHead->y))
//                     {
//                         // Move the x coord +1
//                         xdir=1;
//                         ydir=0;
//                     }
//                     break;
//                 case 1:
//                 // Move up
//                 if (!lookup_pos(snakeHead,snakeHead->x,abs((snakeHead->y)-1)) && !lookup_pos(snakeHead,snakeHead->x,((snakeHead->y)+1)%HEIGHT))                    {
//                         // Move the x coord +1
//                         ydir=-1;
//                         xdir=0;
//                     }
//                     break;
//                 case 2:
//                 // Move down
//                     if (!lookup_pos(snakeHead,snakeHead->x,abs((snakeHead->y)-1)) && !lookup_pos(snakeHead,snakeHead->x,((snakeHead->y)+1)%HEIGHT))
//                     {
//                         // Move the x coord +1
//                         ydir =1;
//                         xdir = 0;
//                     }
//                     break;
//                 case 3:
//                 // Move left
//                     if (!lookup_pos(snakeHead,abs((snakeHead->x)-1),snakeHead->y) && !lookup_pos(snakeHead,((snakeHead->x)+1)%WIDTH,snakeHead->y))
//                     {
//                         // Move the x coord +1
//                         xdir=-1;
//                         ydir=0;
//                     }
//                     break;
//             }         
//         }
//         counter++;
//     } while (1);
//     printf("Your score is %d\n", counter);
//     sleep_msec(5000);
// }

int main(void){
    int size = 0;
    char cmd;
    struct pos *head;
    head = NULL;
    struct ttl *killerHead = NULL;
    do{
        int correctCmd = 0;
        char commands[] = {'q','l','f','s','t','b','i','u','r','p'};
        printf("Command: ");
        scanf(" %c",&cmd); 
        for (int i=0; i < strlen(commands);i++){
            if(commands[i]==cmd){
                correctCmd = 1;
            }
        }
        
        if(!correctCmd){
            printf("Invalid command '%c'\n",cmd);
        }
        else{
            if  (cmd =='s'){
                print_list(head);
            }
            else if(cmd == 'l'){
                int x,y;
                printf("Position (x y)? ");
                scanf(" %d %d",&x,&y);
                if(lookup_pos(head,x,y)){
                    printf("Position (%d,%d) is in the list\n",x,y);
                }
                else{
                    printf("Position (%d,%d) is not in the list\n",x,y);
                }
            }
            else if(cmd == 'f'){
                int x,y;
                printf("Position (x y)? ");
                scanf(" %d %d",&x,&y);
                head = add_new_pos(head,x,y);
            }
            else if(cmd == 't'){
                head = remove_last_pos(head);   
            }
            else if(cmd == 'p'){
                // printf("Welcome to SNAKE!\nButtons 0-3 are right, up, down, left, respectively.\nSnake�s head is blue, tail is green, bonuses are yellow, killer blocks are red.");
                // char anw;
                // do
                // {
                //     play();
                //     printf("Play again? ");
                //     scanf(" %c",&anw);
                // } while (anw == 'y');
                break;
            }
            else if(cmd == 'b'){
                print_ttl(killerHead);
            }
            else if(cmd == 'i'){
                int x,y,ttl;
                printf("Position (x y ttl)? ");
                scanf(" %d %d %d",&x,&y,&ttl);
                if (ttl<=0)
                {
                    printf("TTL must be > 0\n");
                }
                else{
                    killerHead = add_new_ttl(killerHead,x,y,ttl);
                }
            }   
            else if(cmd == 'u'){
                update_ttl(killerHead);
            }
            else if(cmd == 'r'){
                killerHead=remove_last_ttl(killerHead);
            }
        }
    }while(cmd != 'q');
    printf("Bye\n");
    return 0;
}