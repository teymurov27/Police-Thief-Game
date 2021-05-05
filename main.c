/* Istanbul Technical University
 * Faculty of Electrical and Electronics
 * Department of Control and Automation Engineering
 * Name and Lastname: Samir Teymurov
 * School ID: 040190922
 */
//Necessary libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// If you want to change map size for the game you have to change these three definitive variables.
#define MAP_SIZE_X 16
#define MAP_SIZE_Y 16
#define SIZE 16

// If you want to change escape point coordinates you have to change these two definitive variables.
#define EPX 7  // Escape point X
#define EPY 15 // Escape point Y

// On the map underscores displaying way of motion and hashtags displaying walls.
char map[MAP_SIZE_X][MAP_SIZE_Y];

int THIEF_START_POINT_X;
int THIEF_START_POINT_Y;
int POLICE_START_POINT_X;
int POLICE_START_POINT_Y;
int n = SIZE;

// Creating open squares that police can move across all the map except walls.
int open = SIZE*SIZE;

// When game finished it is asked to restart the game again or exit.
bool question = true;
bool loop = true;
char restart;

// Functions for not crossing the wall , positions of thief and police on the map.
int manhattanDistance(int THIEF_START_POINT_X, int THIEF_START_POINT_Y, int distance_X, int distance_Y);
int locationOfPlayer(int controller, char map[][MAP_SIZE_Y], int X_POSITION, int Y_POSITION);
int positionDetector(char map[][MAP_SIZE_Y], int X_POSITION, int Y_POSITION);
int walls(int controller,  int X_POSITION, int Y_POSITION);
int movingPolice(int POLICE_MOTION, char map[][MAP_SIZE_Y], int X_POSITION2, int Y_POSITION2);

int main(int argc, char *argv[]) {

    srand(time(NULL));
    int controller;
    int POLICE_MOTION;
    int checking;
    int checking2;

    do {
        // Creating ways of motion with underscores.
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                map[i][j] = '_';
            }

        // Walls on the map
        map[0][8] = '#', map[1][8] = '#', map[2][2] = '#', map[3][2] = '#', map[2][13] = '#', map[3][13] = '#', map[5][6] = '#', map[5][7] = '#',
        map[5][8] = '#', map[6][6] = '#', map[9][3] = '#', map[9][4] = '#', map[9][5] = '#', map[10][5] = '#', map[14][2] = '#', map[14][3] = '#',
        map[14][4] = '#', map[8][10] = '#', map[9][10] = '#', map[10][10] = '#', map[11][10] = '#', map[11][11] = '#';

        // Function for distance between escape point, thief and police.
        while(loop)
        {
            THIEF_START_POINT_X = rand() % SIZE;
            THIEF_START_POINT_Y = rand() % SIZE;
            POLICE_START_POINT_X = rand() % SIZE;
            POLICE_START_POINT_Y = rand() % SIZE;
            if((manhattanDistance(THIEF_START_POINT_X, THIEF_START_POINT_Y, EPX , EPY) >= 16) && (manhattanDistance(POLICE_START_POINT_X, POLICE_START_POINT_Y, THIEF_START_POINT_X, THIEF_START_POINT_Y) >= 16) && map[POLICE_START_POINT_X][POLICE_START_POINT_Y] != '#' && map[THIEF_START_POINT_X][THIEF_START_POINT_Y] != '#')
            {
                // Thief
                map[THIEF_START_POINT_X][THIEF_START_POINT_Y] = 'T';
                // Police
                map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = 'P';

                loop = false;
            }
        }
        loop = true;

        // Escape point
        map[EPX][EPY] = 'E';



        printf("Welcome to the Thief-Police Maze Game.\n");
        printf("You are playing the game as thief .\n");
        printf("And you need to go to the Manhattan Escape Point to win the game.\n");
        printf("Your way described as '_' and you can't cross the walls which described as '#'.\n");
        printf("And by pressing '8' you can go upwards,'2' for downwards,'4' for Left and '6' for Right \n");
        printf("P = Police, T = Thief and E = Manhattan Escape Point\n");
        printf("To begin the game you need to select the game difficulty.\n ");
        printf("Please press '1' for Easy game and '2' for Hard game.\n ");
        scanf("%d", &POLICE_MOTION);


// Starting the game

        do {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%c ", map[i][j]);
                }
                printf("\n");
            }
            printf("Enter your moving direction: ");
            scanf("%d", &controller);

            /* In the game functions returning some values. Some of them are -1 means you've lost the game,
             * returning 0 means you can't move in this case it is most probably for the walls or map boundaries
             * that you can not move, returning 2 means that you've won the game and finally returning value 1 means
             * you can pass or the situation is true.
             */

            checking = locationOfPlayer(controller, map, THIEF_START_POINT_X, THIEF_START_POINT_Y);
            if (checking == -1){
                break;
            }
            movingPolice(POLICE_MOTION, map, POLICE_START_POINT_X, POLICE_START_POINT_Y);
            checking2 = positionDetector(map, THIEF_START_POINT_X, THIEF_START_POINT_Y);
            system("clear");

        } while (checking != 2 && checking2 != -1);


        printf("Do you want to play again ?\nPlease enter y(Yes)/n(No)");
        getchar();
        scanf("%c", &restart);

        switch (restart) {
            case 'y':

                question = true;

                break;

            case 'n':

                question = false;


                break;

            default:
                printf("Please try again!\nPlease type only 'y' for Yes and 'n' for No");

                break;


        }

    }while(question);


}
// Function for manhattan distance and locationOfPlayer of the thief.
int manhattanDistance(int THIEF_START_POINT_X, int THIEF_START_POINT_Y, int distance_X, int distance_Y){

    return abs(THIEF_START_POINT_X - distance_X ) + abs(THIEF_START_POINT_Y - distance_Y );
}
// Functions for motion of thief
int locationOfPlayer(int controller, char map[MAP_SIZE_X][MAP_SIZE_Y], int X_POSITION, int Y_POSITION){

    int step_x = X_POSITION;
    int step_y = Y_POSITION;
    int checking;




    switch (controller)
    {
        case 8:
            THIEF_START_POINT_X -= 1;
            break;
        case 2:
            THIEF_START_POINT_X += 1;
            break;
        case 6:
            THIEF_START_POINT_Y += 1;
            break;
        case 4:
            THIEF_START_POINT_Y -= 1;
            break;
        default:
            printf("Please try again!\n");
            break;
    }

    checking = positionDetector(map, THIEF_START_POINT_X, THIEF_START_POINT_Y);
    if( checking == 1 && walls(controller, THIEF_START_POINT_X, THIEF_START_POINT_Y) == 1){

        char pass = map[step_x][step_y];
        map[step_x][step_y] = map[THIEF_START_POINT_X][THIEF_START_POINT_Y];
        map[THIEF_START_POINT_X][THIEF_START_POINT_Y] = pass;

        return checking;
    }


    else
    {
        THIEF_START_POINT_X = X_POSITION;
        THIEF_START_POINT_Y = Y_POSITION;

        return checking;
    }

}
// This function detects whether you are near walls(1), near police(2) or near escape point(3).
// When one of these three situations happens it displays you can not cross the walls, you've won or lost.
int positionDetector(char map[MAP_SIZE_X][MAP_SIZE_Y], int X_POSITION, int Y_POSITION)
{
    if(map[X_POSITION][Y_POSITION] == '#'){

        printf("You can't cross the walls!\n");
        int c = getchar();
        return 0;
    }
    if(map[X_POSITION][Y_POSITION] == 'P'){

        printf("You lost!\n");
        int c = getchar();
        return -1;
    }

    if(map[X_POSITION][Y_POSITION] == 'E')
    {
        printf("You won!\n");
        int c = getchar();
        return 2;
    }

    return 1;
}
// Function for not crossing the walls. It detects coordinate of player whether she/he near wants to cross walls.
int walls(int controller,  int X_POSITION, int Y_POSITION){
    // Checking map boundaries
    if(X_POSITION<0 || Y_POSITION<0 && (controller == 8 || controller == 4))
    {
        printf("Can't move there\n");
        return 0;
    }
    else if(X_POSITION<0 || Y_POSITION>15 && (controller == 8 || controller == 6))
    {
        printf("Can't move there\n");
        return 0;
    }
    else if(X_POSITION>15 || Y_POSITION<0 && (controller == 2 || controller == 4))
    {
        printf("Can't move there\n");
        return 0;
    }
    else if(X_POSITION>15 || Y_POSITION<0 && (controller == 2 || controller == 6))
    {
        printf("Can't move there\n");
        return 0;
    }

    else
        return 1;
}
// Function for motion of police. Police can not cross the walls as well.
// In the easy mode movement of police happens randomly and clearly it can barely catch you.
// But in the hard mode police moves due to your location on the map. For example if you play upwards police moves downwards for making
// distance more shorter.
int movingPolice(int POLICE_MOTION, char map[MAP_SIZE_X][MAP_SIZE_Y], int X_POSITION2, int Y_POSITION2){
    // A step before police's position.
    int step_x2 = X_POSITION2;
    int step_y2 = Y_POSITION2;
    // These variables are used for the way police moves according to the thief.
    int policeUp, policeDown, policeRight, policeLeft, policeDir;

    switch(POLICE_MOTION){
        case 1: //Easy mode: police moves randomly.
        srand(time(NULL));
            policeDir = (rand() % 4) + 1;
            if(policeDir == 1){
                if( POLICE_START_POINT_X == 0 || map[POLICE_START_POINT_X-1][POLICE_START_POINT_Y] == '#' || map[POLICE_START_POINT_X-1][POLICE_START_POINT_Y] == 'E' ){
                    while(policeDir == 1){
                        policeDir = (rand() % 4) + 1;
                    }
                }else{
                    if(map[POLICE_START_POINT_X][POLICE_START_POINT_Y] != 'T'){
                        map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = '_';
                    }
                    POLICE_START_POINT_X = POLICE_START_POINT_X-1;
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = 'P';
                }
            }
            if(policeDir == 2){
                if( POLICE_START_POINT_X == 15 || map[POLICE_START_POINT_X+1][POLICE_START_POINT_Y] == '#' || map[POLICE_START_POINT_X+1][POLICE_START_POINT_Y] == 'E' ){
                    while(policeDir == 2){
                        policeDir = (rand() % 4) + 1;
                    }
                }else{
                    if(map[POLICE_START_POINT_X][POLICE_START_POINT_Y] != 'T'){
                        map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = '_';
                    }
                    POLICE_START_POINT_X = POLICE_START_POINT_X+1;
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = 'P';
                }
            }
            if(policeDir == 3){
                if( POLICE_START_POINT_Y == 0 || map[POLICE_START_POINT_X][POLICE_START_POINT_Y-1] == '#' || map[POLICE_START_POINT_X][POLICE_START_POINT_Y-1] == 'E' ){
                    while(policeDir == 3){
                        policeDir = (rand() % 4) + 1;
                    }
                }else{
                    if(map[POLICE_START_POINT_X][POLICE_START_POINT_Y] != 'T'){
                        map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = '_';
                    }
                    POLICE_START_POINT_Y = POLICE_START_POINT_Y-1;
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = 'P';
                }
            }
            if(policeDir == 4){
                if(POLICE_START_POINT_Y == 15 || map[POLICE_START_POINT_X][POLICE_START_POINT_Y+1] == '#' || map[POLICE_START_POINT_X][POLICE_START_POINT_Y+1] == 'E' ){
                    while(policeDir == 4){
                        policeDir = (rand() % 4) + 1;
                    }
                }else{
                    if(map[POLICE_START_POINT_X][POLICE_START_POINT_Y] != 'T'){
                        map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = '_';
                    }
                    POLICE_START_POINT_Y = POLICE_START_POINT_Y+1;
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = 'P';
                }
            }
            break;

        case 2:
        srand(time(NULL));

            if( POLICE_START_POINT_X == 0 || map[POLICE_START_POINT_X-1][POLICE_START_POINT_Y] == '#' || map[POLICE_START_POINT_X-1][POLICE_START_POINT_Y] == 'E' ){
                policeUp = open;
            }
            else{
                policeUp = abs( THIEF_START_POINT_X - (POLICE_START_POINT_X-1)) + abs(THIEF_START_POINT_Y - POLICE_START_POINT_Y);
            }

            if( POLICE_START_POINT_X == 15 || map[POLICE_START_POINT_X+1][POLICE_START_POINT_Y] == '#' || map[POLICE_START_POINT_X+1][POLICE_START_POINT_Y] == 'E' ){
                policeDown = open;
            }
            else {
                policeDown = abs( THIEF_START_POINT_X - (POLICE_START_POINT_X+1)) + abs(THIEF_START_POINT_Y - POLICE_START_POINT_Y);
            }

            if (POLICE_START_POINT_Y == 0 || map[POLICE_START_POINT_X][POLICE_START_POINT_Y-1] == '#' || map[POLICE_START_POINT_X][POLICE_START_POINT_Y-1] == 'E'){
                policeLeft = open;
            }
            else {
                policeLeft = abs( THIEF_START_POINT_X - POLICE_START_POINT_X) + abs(THIEF_START_POINT_Y - (POLICE_START_POINT_Y-1));
            }

            if (POLICE_START_POINT_Y == 15 || map[POLICE_START_POINT_X][POLICE_START_POINT_Y+1] == '#' || map[POLICE_START_POINT_X][POLICE_START_POINT_Y+1] == 'E' ){
                policeRight = open;
            }
            else{
                policeRight = abs( THIEF_START_POINT_X - POLICE_START_POINT_X) + abs(THIEF_START_POINT_Y - (POLICE_START_POINT_Y+1));
            }


            if (policeUp != open && policeUp <= policeDown && policeUp <= policeRight && policeUp <= policeLeft){
                if(map[POLICE_START_POINT_X][POLICE_START_POINT_Y] != 'T'){
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = '_';

                }
                POLICE_START_POINT_X = POLICE_START_POINT_X-1;
                map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = 'P';
                break;
            }
            if (policeDown != open && policeDown <= policeUp && policeDown <= policeRight && policeDown <= policeLeft){
                if(map[POLICE_START_POINT_X][POLICE_START_POINT_Y] != 'T'){
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = '_';

                    POLICE_START_POINT_X = POLICE_START_POINT_X+1;
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = 'P';
                    break;
                }
            }
            if (policeLeft != open && policeLeft <= policeDown && policeLeft <= policeRight && policeLeft <= policeUp){
                if(map[POLICE_START_POINT_X][POLICE_START_POINT_Y] != 'T'){
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = '_';

                    POLICE_START_POINT_Y = POLICE_START_POINT_Y-1;
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = 'P';
                    break;
                }
            }
            if (policeRight != open && policeRight <= policeDown && policeRight <= policeUp && policeRight <= policeLeft){
                if(map[POLICE_START_POINT_X][POLICE_START_POINT_Y] != 'T'){
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = '_';

                    POLICE_START_POINT_Y = POLICE_START_POINT_Y+1;
                    map[POLICE_START_POINT_X][POLICE_START_POINT_Y] = 'P';
                    break;
                }

            }
            break;


    }



    return 0;
}

