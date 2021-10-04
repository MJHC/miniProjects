#include <stdio.h>
#include <stdlib.h>
/*Symbolsk Konstant til at kunne ændre på antal af spille kort nemt*/
#define CARDSLIMIT 55

/*Enums til at gøre koden mere læsbar*/
enum boolean{False, True};
enum suits{Clubs, Diamonds, Hearts, Spades, Joker};
enum values{Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};

/*struct med kort værdier*/
struct cards{
    int suit;
    int value;
    int joker;
}myCards[CARDSLIMIT];

/*typedef så man ikke behøver at skrive struct cards men nu kun cards*/
typedef struct cards cards;

/*Prototyper*/
void initCards(cards *myCards);
int sortCards(const void *a, const void *b);
void printCards(cards *myCards);

/*programmet køres i main*/
int main(){ 
    initCards(myCards);
    printCards(myCards); 
    return EXIT_SUCCESS;
}

/*Alle kort jokere inkluderet bliver initialiseret og sorteret*/
void initCards(cards *myCards){
    int i, j, s = 0, v = 0;
    for (j = 0; j < CARDSLIMIT; j++){  

        myCards[j].joker = False;
        if(s != Spades+1){
            myCards[j].suit = s;
            s++;
        }else{s = 1;}

        if(v != Ace+1){
            myCards[j].value = v;
            v++;
        }else{v = 1;}
    }
    for (i = CARDSLIMIT-3; i < CARDSLIMIT; i++){
        myCards[i].joker = True;
        myCards[i].suit = Joker;
    }   
    qsort(myCards, CARDSLIMIT, sizeof(cards), sortCards);
}

/*sortCards er hvordan qsort skal sortere kortene*/
int sortCards(const void *a, const void *b){
    int suit1 = ((cards*)a)->suit, suit2 = ((cards*)b)->suit,
        value1 = ((cards*)a)->value, value2 = ((cards*)b)->value;

    if(suit1 == suit2)
        return (value1 - value2);
    else
        return (suit1 - suit2);
}

/*
    printCards printer kortene i terminalen i et læsbart format.
    Da kortene reelt set kun er tal og er svært at læse for
    brugeren af programmet
*/
void printCards(cards *myCards){
    int i, k, j;
    char *sStrings[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    char *vStrings[13] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    
    for ( i = 0; i < CARDSLIMIT; i++){
        if(myCards[i].joker != True){
            for (k = 0; k < 4; k++){
                if(myCards[i].suit == k)
                    printf("%-10s", sStrings[k]);
            }
            for (j = 0; j < 13; j++){
                if(myCards[i].value == j)
                    printf("%s", vStrings[j]);
            }
        } else{
            printf("Joker");
        }
        printf("\n");
    }
}