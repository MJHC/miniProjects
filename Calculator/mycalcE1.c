/***********************************************************
*   Eksamensopgave 1:   En regnemaskine på kommandolinjen  *
*   Lavet af:           Magnus J. Harder Christensen       *
*   Email:              mjhc20@student.aau.dk              *
*   Gruppe:             A408B                              *
*   Studie retning:     Software                           *
*   Afleveringsdato:    26.10.2020                         *
***********************************************************/

#include <stdio.h>
#include <math.h>

/*Prototyper*/
void scanData(char*, double*);
void doNext(char, double, double*);
double runCalc(char*, double*, double*);
double scanBool(char);
double division(double, double);
double square(double);


/*main hvor programmet køres*/
int main(){
    double input = 0.0, accumulator = 0.0;
    char chInput = 'a';  
    /*&chinput, ... tager adressen af variablerne ovenfor og sender til runCalc*/
    printf("Final Result: %lf\n", runCalc(&chInput, &input, &accumulator));

    return 0;
}


/*tager input*/
void scanData(char *ch, double *in){
    printf("Enter: ");
    scanf(" %c", ch);
    if(scanBool(*ch) == 1){ 
        scanf(" %lf", in);
    }  
}

/*finder ud af hvad der skal gøres med input*/
void doNext(char ch, double in, double *a){
    switch (ch){
        case '+': *a += in;                 break;
        case '-': *a -= in;                 break;
        case '*': *a *= in;                 break;
        case '^': *a = pow(*a, in);         break;
        case '/' :*a = division(in, *a);    break;
    
        case '#': *a = square(*a);          break;
        case '%': *a = -*a;                 break;
        case '!': *a = 1/ *a;               break;
    }
}

/*samler scanData og doNext i et loop så man kan blive ved med at regne på accumulator*/
double runCalc(char *ch, double *in, double *a){
    while(*ch != 'q'){
        /*scan data bruger adresserne, doNext tager data i ch og in men adresse i a*/
        scanData(ch, in); 
        doNext(*ch, *in, a);
        if(*ch != 'q')
            printf("Result: %lf\n", *a);
    }
    return *a;
}

/*små funktioner til gavn for læsbarheden af doNext og scanData*/
double scanBool(char ch){
    if(ch != '#' && ch != '%' && ch != '!' && ch != 'q')
        return 1;
}

double division(double in, double a){
    if(a == 0){
        } 
    else{
        return a /= in;
        }
}

double square(double a){
    if(a < 0){
        } 
    else{
        return a = sqrt(a);
        }
}