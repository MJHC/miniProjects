#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum cases {lowerCase, upperCase, symbol, atQuest, number};

int randChar(int i);
int symbolGen();
void generator();
void generatePass(int length, int amount);
/*void generatePass(int length, int amount, char inLow, char inUp, char inSym, char inNum);*/

int main(){
    srand((unsigned) time(0));

    generator();

    return EXIT_SUCCESS;
}

void generator(){
    int input = 0, amount = 0;
    char ch = 'a';

    printf("How long should your password(s) be?: ");
    scanf(" %d", &input);
    printf("How many do you want?: ");
    scanf(" %d", &amount);
    generatePass(input, amount);
}

void generatePass(int length, int amount){
    int i, j, r;

    for (i = 0; i < amount; i++){

        if(1 < amount)
            printf("%d: ", i+1);

        for (j = 0; j < length; j++){     
            r = rand() % 5;
            printf("%c", randChar(r));
        }
        printf("\n");
    }
}

int randChar(int i){
    char ch = 'a';
    int j = rand() % 2;

    switch (i){
    case lowerCase: ch = (char) (rand() % (123-97) + 97); break;
    case upperCase: ch = (char) (rand() % (91-65) + 65);  break;
    case symbol:    ch = symbolGen();                     break;
    case atQuest:   ch = j == 0 ? '@' : '?';              break;
    case number:    ch = (char) (rand() % (58-48) + 48);  break;
    }

    return ch;
}

int symbolGen(){
    int s = 0;

    do{s = (rand() % (43-33) + 33);}
    while(s == 34 || s == 40 || s == 41);
    return (char) s;
}

/*int checker(int i){
    int r;
    while (r == i){
        r = rand() % 5;
    }
    return r;
}

int myBool(char i){
    if(i == 'y' || i == 'Y')
        return 1;
    else
        return 0;
}*/