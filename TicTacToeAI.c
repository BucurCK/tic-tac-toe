/**
 * // TODO: Create functions cause this code is UGLY
 * // TODO: Make it impossible to rewrite symbols in the game
 * // TODO: Add TIE state
 * /////* Maybe just make the choice of symbols (X/O) automatic
 * //! Add an AI(or something like that) so you can play solo - you sad FUCK
 * //! REMOVE goto cause its stupid
 * ! Rename the variables
 * * Try to make some kind GUI for this(don't know how atm)
 * * Write the functions in different files(just to learn it -- for this kind of short code it's pretty useless)
 * // MAKE IT A VECTOR YOU STUPID FUCK :)
 */

void printTicToc(char *game);
void fillUp(char *game);
int getNum(char X[],char cond);
int checkWin(char *game, int turn);
int checkRewrite(int i, int memory[], int turn);
void artificialIntelligence(char *game, char symbol_AI,char symbol_User, int memory[], int turn);


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9

char line[10];

int main(){
    char game[SIZE]; // the X&O array
    int i; // array position
    int test = 1; // keeps the while going till a win condition is met
    char *pgame = game;
    int memory[SIZE]; //remember where X/O have been placed
    int turn = 0; // keep count of how may X/O have been placed and how many turns have passed
    int checker;

    fillUp(pgame);
    printTicToc(pgame);

    printf("Instruction: Input the line number and right next to it the symbol_AI you wish to play with(use X and O pls):\n");

    while(test == 1){

        if(turn % 2 == 0){
            printf("TURN: %d -- X\n", turn + 1);
        }else{
            printf("TURN: %d -- O\n", turn + 1);
            
            artificialIntelligence(pgame, 'O', 'X', memory, turn);
            test = checkWin(pgame, turn);
            printTicToc(pgame);
            if(test != 1){
                break;
            }
            printf("###4 turn=%d\n",turn);
            turn++;
            continue;;
        }
        printf("###5 turn=%d\n",turn);

        i = getNum("Input line(1-9): ", 'd') - 1;
        while(i < 0 || i > 8){
            printf("WRONG INPUT, please use numbers from 1 to 9\n");
            i = getNum("Input line(1-9): ", 'd') - 1;
        }
        /*Gets the position(1-9) -- turns it in a array position (0-8)
        (if it isn't O-8 it will scan it again*/

        i = checkRewrite(i, memory, turn);
        while(i == -1){
            printf("THE BOX IS ALREADY FILLED\n");
            i = getNum("Input line(1-9): ", 'd') - 1;
            while(i < 0 || i > 8){
                printf("WRONG INPUT, please use numbers from 1 to 9\n");
                i = getNum("Input line(1-9): ", 'd') - 1;
            }
            i = checkRewrite(i, memory, turn);
        }
        /*Checks if the position has already been used 
        -- re-scans it and rechecks it to be between 1-9*/
        //printf("### turn=%d\n",turn);
        
        game[i] = 'X'; // puts the symbol
        
        /*Even turns are 'O'; uneven turns are 'X'*/

        test = checkWin(pgame, turn);
        turn++;

        if( turn == 9 && test == 1){
            printf("........TIE........\n");
            printTicToc(pgame);
            break;
        }
        /*if all positions are filled than declare a TIE 
        -- also check that the last "move" wasn't the winning one*/         
       
        printTicToc(pgame);

    }
    #ifdef _WIN32
        system("pause");
    #else
        printf("Press enter to exit...");
        getchar();
    #endif  

    return 0;
}

void printTicToc(char *game){
   
    printf("   | %c | %c | %c |\n",*(game + 0), *(game + 1), *(game + 2));
    printf("   | %c | %c | %c |\n",*(game + 3), *(game + 4), *(game + 5));
    printf("   | %c | %c | %c |\n",*(game + 6), *(game + 7), *(game + 8));
    printf("\n");

}
    /*Print the state of the game*/

void fillUp(char *game){
    int i;
    int k = 49;

    for(i = 0; i < SIZE; i++){
        *(game + i) = k;
        k++;
    }
}
    /*Fill up the matrix with ASCII codes for 1-9 (starts from '49' = 1)*/

int getNum(char a[], char cond){
    int X;
    char y;

    printf("%s", a);
    switch (cond)
    {
    case ('d'):
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &X);
            return X;
        break;
    case ('c'):
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%c", &y);
            return y;
        break;
    default:
        return X;
        break;
    }
}

    /*Gets the input from user -- also checks it to be either int or char*/

int checkWin(char *game, int turn){
    int i;
    int j;
    int test = 1;
    char symbol_WIN;

    if(turn % 2 == 0){
        symbol_WIN = 'X';
    }else{
        symbol_WIN = 'O';
    }

    if((*(game + 0) == *(game + 4)) && (*(game + 0) == *(game + 8))){
                printf("......%c WON......\n", symbol_WIN);
                test = 0;
    }
    else if((*(game + 2) == *(game + 4)) && (*(game + 2) ==  *(game + 6))){
                printf("......%c WON......\n", symbol_WIN);
                test = 0;

    }
   
    for(i = 0, j = 0; i < 3 && test == 1; i++, j += 2){
            if((*(game + i + j) == *(game + i + j + 1)) && (*(game + i + j) == *(game + i + j + 2))){
                printf("......%c WON......\n", symbol_WIN);
                test = 0;
                break;
            }
            else if((*(game + i) == *(game + i + 3)) && (*(game + i) == *(game + i + 6))){
                printf("......%c WON......\n", symbol_WIN);
                test = 0;
                break;
            }      
        }

        return test;
}
       
        /*checks for a win condition by comparing every
        line across, then downward, then both diagonals
        and return 0 for win and 1 for lose*/

int checkRewrite(int i, int memory[], int turn){
    int X;
    for(X = 0; X < turn; X++){
        if( i == *(memory + X)){
            return -1;
        }
    }
    *(memory + turn) = i;

    return i;
}
        /*Checks if the position has already been used, 
        if yes => returns -1, 
        if not => saves the position in an array and returns it to main*/

void artificialIntelligence(char *game, char symbol_AI,char symbol_User, int memory[], int turn){
    int i;
    int j;
    int test = 0;
    
    while(1){
        if(*(game + 0) == *(game + 4) && *(game + 8) != symbol_AI && *(game + 8) != symbol_User){
            *(game + 8) = symbol_AI;
            *(memory + turn) = 8;
            break;
        }else if(*(game + 0) == *(game + 8) && *(game + 4) != symbol_AI && *(game + 4) != symbol_User){
            *(game + 4) = symbol_AI;
            *(memory + turn) = 4;
            break;
        }else if(*(game + 4) == *(game + 8) && *(game + 0) != symbol_AI && *(game + 0) != symbol_User){
            *(game + 0) = symbol_AI;
            *(memory + turn) = 0;
            break;
        }
        /*first diagonal*/

        if(*(game + 2) == *(game + 4) && *(game + 6) != symbol_AI && *(game + 6) != symbol_User){
            *(game + 6) = symbol_AI;
            *(memory + turn) = 6;
            break;
        }else if(*(game + 2) == *(game + 6) && *(game + 4) != symbol_AI && *(game + 4) != symbol_User){
            *(game + 4) = symbol_AI;
            *(memory + turn) = 4;
            break;
        }else if(*(game + 4) == *(game + 6) && *(game + 2) != symbol_AI && *(game + 2) != symbol_User){
            *(game + 2) = symbol_AI;
            *(memory + turn) = 2;
            break;
        }
        /*second diagonal*/

     for(i = 0, j = 0; i < 3; i++, j += 2){
            if(*(game + i + j) == *(game + i + j + 1) && *(game + i + j + 2) != symbol_AI && *(game + i + j + 2) != symbol_User){
                *(game + i + j + 2) = symbol_AI;
                *(memory + turn) =( i + j + 2);
                test++;
                break;
            }else if(*(game + i + j) == *(game + i + j + 2) && *(game + i + j + 1) != symbol_AI && *(game + i + j + 1) != symbol_User){
                *(game + i + j + 1) = symbol_AI;
                *(memory + turn) = (i + j + 1);
                test++;
                break;
            }else if(*(game + i + j + 1) == *(game + i + j + 2) && *(game + i + j) != symbol_AI && *(game + i + j) != symbol_User){
                *(game + i + j) = symbol_AI;
                *(memory + turn) = (i + j);
                test++;
                break;
            }
        /* across */
            if(*(game + i) == *(game + i + 3) && *(game + i + 6) != symbol_AI && *(game + i + 6) != symbol_User){
                *(game + i + 6) = symbol_AI;
                *(memory + turn) = (i + 6);
                test++;
                break;
            }else if(*(game + i) == *(game + i + 6) && *(game + i + 3) != symbol_AI && *(game + i + 3) != symbol_User){
                *(game + i + 3) = symbol_AI;
                *(memory + turn) = (i + 3);
                test++;
                break;
            }else if(*(game + i + 3) == *(game + i + 6) && *(game + i) != symbol_AI && *(game + i) != symbol_User){
                *(game + i) = symbol_AI;
                *(memory + turn) = i;
                test++;
                break;
            }
        /* downward */
        }
        if(test != 0){ //if no symbol_AI has been placed than let code enter random assignment
            break;
        }
            int rand_num;
            srand(time(0));
            while(1){ //random assignment
                rand_num = rand() % 9;
                if(*(game + rand_num) != symbol_AI && *(game + rand_num) != symbol_User){
                    *(game + rand_num) = symbol_AI;
                    *(memory + turn) = rand_num;
                    break;
                }   
            }
        break;
    }
}

// *(game + i + j) -     0 3 6
// *(game + i + j + 1) - 1 4 7
// *(game + i + j + 2) - 2 5 8

// *(game + i) -     0 1 2
// *(game + i + 3) - 3 4 5
// *(game + i + 6) - 6 7 8
