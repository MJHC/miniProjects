/***********************************************************
*   Eksamensopgave 3:   Fodboldturnering                   *
*   Lavet af:           Magnus J. Harder Christensen       *
*   Email:              mjhc20@student.aau.dk              * 
*   Gruppe:             A408B                              *
*   Studie retning:     Software                           *
*   Afleveringsdato:    3.12.2020                          *
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*symbolic constants for easy change in values*/
#define GAMES_AMOUNT        182
#define TEAMS_AMOUNT        14
#define MAX_LINE_LENGTH     75
#define MAX_CH_LENGTH       4

/*Structs*/
typedef struct game{
    char weekday[MAX_CH_LENGTH];
    int day;
    int month;
    int hour;
    int minute;

    char team1[MAX_CH_LENGTH];
    char team2[MAX_CH_LENGTH];

    int t1Goals;
    int t2Goals;

    int spec;

}game;

typedef struct team{
    char name[3];
    int points;
    int goals;
    int goalsAgainst;

}team;

/*Prototypes*/
void readFile(game* game, FILE* input);
int comAlphabet(const void* a, const void* b);
int com (const void *a, const void *b);
void calcTeamScore(game* game, team* team);
void scoreboard(game* game, team* team, FILE* file);

/*Initializes the required arrays and specifies what file should be read*/
int main(){
    game game[GAMES_AMOUNT];
    team team[TEAMS_AMOUNT] = {0};
    FILE* file = fopen("kampe-2019-2020.txt", "r");
    
    scoreboard(game, team, file);
    fclose(file);
    return 0;
}

/*Runs program - this function is also here to declutter main*/
void scoreboard(game* game, team* team, FILE* file){
    int i;

    readFile(game, file);
    calcTeamScore(game, team);

    printf("%-10s %-10s %-10s %-10s %-10s\n", "Position", "Team", "Points", "Goals", "Goals Against");
    for (i = 0; i < TEAMS_AMOUNT; i++){
        printf("%-10d %-10s %-10d %-10d %-10d\n", 
                i+1, team[i].name, team[i].points, team[i].goals, team[i].goalsAgainst);
    }
}

/*Reads specified File*/
void readFile(game* game, FILE* input){
    char line[MAX_LINE_LENGTH];
    int i;

    for (i = 0; i < GAMES_AMOUNT; i++){
        fgets(line, MAX_LINE_LENGTH, input);
        sscanf(line, "%s %d/%d %d.%d %s - %s %d - %d %d",
            (game + i)->weekday, &(game + i)->day, &(game + i)->month,
            &(game + i)->hour, &(game + i)->minute, (game + i)->team1,
            (game + i)->team2, &(game + i)->t1Goals, &(game + i)->t2Goals,
            &(game + i)->spec);
    }
}

/*Sorts in an aplhabetic order*/
int comAlphabet(const void* a, const void* b){
    char *a1 = ((game*)a)->team1; 
    char *b1 = ((game*)b)->team1;
    int res = 0;

    while(*b1 != '\0' && *a1 != '\0'){
        res = *a1++ - *b1++;
        if (res != 0)
            return res;
    }
    return res;
}

/*Sorts in an numeric order*/
int com (const void *a, const void *b){
    team *a1 = (team*)a;
    team *b1 = (team*)b;

    return (int)(b1->points - a1->points);
}

/*Sorts and calculates team score*/
void calcTeamScore(game* game, team* team){
    int i, j = 0, k = 0,l = 0;
    qsort(game, GAMES_AMOUNT, sizeof(struct game), comAlphabet);

    for (i = 0; i < GAMES_AMOUNT; i++){
        if(j != TEAMS_AMOUNT){
            k = strcmp(game[i].team1, game[i+1].team1);
            if(k != 0){
                strcpy(team[j].name, game[i].team1);
                j++;
            }
        }
    }

    for (i = 0; i < TEAMS_AMOUNT; i++){
        for (j = 0; j < GAMES_AMOUNT; j++){
            k = strcmp(team[i].name, game[j].team1);
            l = strcmp(team[i].name, game[j].team2);

            if (k == 0){
                team[i].goals += game[j].t1Goals;
                team[i].goalsAgainst += game[j].t2Goals;

                if(game[j].t1Goals > game[j].t2Goals)
                    team[i].points += 3;
                else if(game[j].t1Goals == game[j].t2Goals)
                    team[i].points += 1;             
            }

            if(l == 0){
                team[i].goals += game[j].t2Goals;
                team[i].goalsAgainst += game[j].t1Goals;

                if(game[j].t1Goals < game[j].t2Goals)
                    team[i].points += 3;
                else if(game[j].t1Goals == game[j].t2Goals)
                    team[i].points += 1;
            }
        }
    }
    qsort(team, TEAMS_AMOUNT, sizeof(struct team), com);
}