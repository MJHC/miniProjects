/***********************************************************
*   Eksamensopgave 2:   Yatzy med mange terninger.         *
*   Lavet af:           Magnus J. Harder Christensen       *
*   Email:              mjhc20@student.aau.dk              * 
*   Gruppe:             A408B                              *
*   Studie retning:     Software                           *
*   Afleveringsdato:    15.11.2020                         *
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*enum for bedre læsbarhed*/
enum gameRounds {One_pair,  Two_pairs ,  Three_of_a_kind ,  Four_of_a_kind ,  Small_straight ,  Large_Straight ,  Full_house ,  Chance ,  Yatzy};

/*prototyper*/
int com (const void *a, const void *b);
void scanData(int *in);
void rollDice(int *dice, int size);
void checkUpper(int *dice, int size, int *mySum, int face, char ** name);
void pair(int *dice, int size, int *mySum, int state, int *localSum);
void kind(int *dice, int size, int *mySum, int state, int *localSum);
void straight(int *dice, int size, int *mySum, int s, int b, int *localSum);
void chance(int *dice, int size, int *mySum, int *localSum);
void full(int *dice, int size, int *mySum, int *localSum);
void runYatzy();
void checkLower(int *dice, int size, int *mySum, int state, char **myCharA);
void bonus(int *mySum);

/*main med loop som spørger om man vil spille spillet igen*/
int main(){
    char ch = 'y';
    time_t t;
    srand((unsigned) time(&t));

    while(ch == 'y' || ch == 'Y'){
    system("cls");
    runYatzy();
    printf("Run Yatzy Again?(Y/N): ");
    scanf(" %c", &ch);
    }
    return 0;
}

/*com fortæller hvordan qsort skal udføre sortering*/
int com (const void *a, const void *b){
   return ( *(int*)a - *(int*)b );
}

/*tager brugerens input*/
void scanData(int *in){
        printf("\n\nIf the input is less than 5 the program will exit\n");
        printf("\nEnter amount of dice you want to play with: ");
        scanf(" %d", in);
        system("cls");
}

/*ruller terninger og sortere dem med qsort*/
void rollDice(int *dice, int size){
    int i;
    for( i = 0 ; i < size ; i++ ) {
        dice[i] = (rand() % 6) + 1;
        printf("%d ",dice[i]);
     }
    qsort(dice, size, sizeof(int), com);
}

/*tjekker om de terninger der er blevet kastet indeholder terning X*/
void checkUpper(int *dice, int size, int *mySum, int face, char ** name){
    int i, counter = 0, localSum = 0;

    printf("%s\t\t\t", name[face-1]);
    rollDice(dice, size);
    for ( i = 0; i < size; i++){
        if(counter < 5){
            if (dice[i] == face){
                *mySum += face;
                localSum += face;
                counter++;  
            }
        }
    }
    printf("\t%d\n", localSum);
}

/*tjekker om der er et par eller 2 alt efter hvad state er sat til*/
void pair(int *dice, int size, int *mySum, int state, int *localSum){
    int i, localSum1 = 0;

    switch (state){
    case 1:
        for (i = 0; i < size; i++){
            if(dice[i] == dice[i+1])
                *localSum = dice[i] + dice[i+1];
        }
        *mySum += *localSum;
    break;
    case 2:
        for (i = size-1; i > 0; i--){
            if(dice[i] == dice[i-1]){
                *localSum = dice[i] + dice[i-1];
                dice[i-1] = 0;
                break;
            }  
        }
        for (i = 0; i < size; i++){
            if(dice[i] == dice[i+1] && dice[i] != localSum1/2)
                localSum1 = dice[i] + dice[i+1];
        }
        if(localSum1 != 0){
            *localSum += localSum1;
            *mySum += *localSum;  
        } else{
            *localSum = 0;
        }    
    break;
    }
}

/*tjekker om der er 3 eller 4 af en type eller om der er yatzy alt efter hvad state er*/
void kind(int *dice, int size, int *mySum, int state, int *localSum){
    int i;
    switch (state){
    case 1:
        for(i = 0 ; i < size; i++ ){
            if(dice[i] == dice[i+1] && dice[i+1] == dice[i+2])
                *localSum = dice[i] + dice[i+1] + dice[i+2]; 
        }
    break;
    case 2:
        for(i = 0 ; i < size; i++ ){
            if(dice[i] == dice[i+1] && dice[i+1] == dice[i+2] && dice[i+2] == dice[i+3])
                *localSum = dice[i] + dice[i+1] + dice[i+2] + dice[i+3];
        }
    break;
    case 3:
        for(i = 0 ; i < size; i++ ){
            if(dice[i] == dice[i+1] && dice[i+1] == dice[i+2] && dice[i+2] == dice[i+3] && dice[i+3] == dice[i+4])
                *localSum = 50;
        }
    break;
    }

    *mySum += *localSum;
}

/*tjekker om der er en straight*/
void straight(int *dice, int size, int *mySum, int s, int b, int *localSum){
    int i, j;

    for (i = 0; i < size; i++){
        if(dice[i] == dice[i+1])
            dice[i] = 0;
    }
    for (i = 0; i < size; i++){
        for (j = s; j <= b; j++){
            if(dice[i] == j)
                *localSum += dice[i];
        }  
    }

    switch (s){
    case 1:
        if(*localSum < 15)
            *localSum = 0;
    break;
    case 2:
        if(*localSum < 20)
            *localSum = 0;
    break;
    }

    *mySum += *localSum;
}

/*lægger de fem bedste terninger sammen*/
void chance(int *dice, int size, int *mySum, int *localSum){
    int i;
    for (i = size-1; i >= size-5; i--){
        *localSum += dice[i];
    }
    *mySum += *localSum;
}

/*tjekker om der er fuldt hus*/
void full(int *dice, int size, int *mySum, int *localSum){
    int i, localSum2 = 0;
    for (i = 0; i < size; i++){
        if(dice[i] == dice[i+1]){
            localSum2 = dice[i] + dice[i+1];
        }
    }
    if(localSum2 != 0){
        for (i = 0; i < size; i++){
                *localSum += dice[i];
        }
    }  
    *mySum += *localSum - localSum2;
}

/*her bliver de fleste funktioner kaldt. denne funktion er også med til at gøre programmet lidt mere forståeligt*/
void checkLower(int *dice, int size, int *mySum, int state, char **myCharA){
    int localSum = 0;
    switch (state){
    case Chance: printf("%s\t\t\t", myCharA[state+6]); break;
    case Yatzy:  printf("%s\t\t\t", myCharA[state+6]); break; 
    default:     printf("%s\t\t", myCharA[state+6]); break;
    }


    rollDice(dice, size);
    switch (state){
    case One_pair:          pair(dice, size, mySum, 1, &localSum);          break;
    case Two_pairs:         pair(dice, size, mySum, 2, &localSum);          break;
    case Three_of_a_kind:   kind(dice, size, mySum, 1, &localSum);          break;
    case Four_of_a_kind:    kind(dice, size, mySum, 2, &localSum);          break;
    case Small_straight:    straight(dice, size, mySum, 1, 5, &localSum);   break;
    case Large_Straight:    straight(dice, size, mySum, 2, 6, &localSum);   break;
    case Full_house:        full(dice, size, mySum, &localSum);             break;
    case Chance:            chance(dice, size, mySum, &localSum);           break;
    case Yatzy:             kind(dice, size, mySum, 3, &localSum);          break;
    }
    printf("\t%d\n", localSum);
}

/*her bliver scoren lagret samt terninger og inputtet fra scanData.
  der bliver kørt nogle for loops med check -upper og -lower 
  funktionerne som udskriver spillet på skærmen*/
void runYatzy(){
    int *cpuDice;
    int diceAmount, sum = 0, i;
    char *names[Yatzy+7] = {"Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", "One pair",  "Two pairs" ,  "Three of a kind" ,  "Four of a kind" ,  "Small straight" ,  "Large Straight" ,  "Full house" ,  "Chance" ,  "Yatzy"};
    
    printf("YATZY WHERE THE COMPUTER PLAYS ALONE\n");
    scanData(&diceAmount);
    if(diceAmount < 5)
        exit(0);
    cpuDice = (int*) malloc(diceAmount*sizeof(int));

    printf("YATZY WHERE THE COMPUTER PLAYS ALONE\n");
    printf("Round\t\t\tDice Rolled\tScore\n\n");

    for (i = 1; i <= 6; i++)
        checkUpper(cpuDice, diceAmount, &sum, i, names);
    bonus(&sum);

    printf("\nUpper Section Score: %d\n\n", sum);

    for (i = 0; i < 9; i++)
        checkLower(cpuDice, diceAmount, &sum, i, names);

    printf("\nOverall Score: %d\n", sum);
    free(cpuDice);
}

/*tjekker om der er bonus den første runde*/
void bonus(int *mySum){
    if(*mySum >= 63){
            printf("BONUS!! +50 points\n");
            *mySum += 50;
    }
}