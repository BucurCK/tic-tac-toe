/**
 * // TODO: Create functions cause this code is UGLY
 * // TODO: Make it impossible to rewrite symbols in the game
 * // TODO: Add TIE state
 * /////* Maybe just make the choice of symbols (x/o) automatic
 * ! Add an AI(or something like that) so you can play solo - you sad FUCK
 * //! REMOVE goto cause its stupid
 * ! Rename the variables
 * * Try to make some kind GUI for this(don't know how atm)
 * * Write the functions in different files(just to learn it -- for this kind of short code it's pretty useless)
 * // MAKE IT A VECTOR YOU STUPID FUCK :)
 */

void printTicToc(char *game);
void fillUp(char *game);
int getNum(char x[],char cond);
int checkWin(char *game);
int checkRewrite(int i, int memory[], int *k);

#include <stdio.h>

#define SIZE 9

char line[10];

int main(){
    char game[SIZE]; // the x&o array
    int i; // array position
    int test = 1; // keeps the while going till a win condition is met
    char *pgame = game;
    int memory[SIZE]; //remember where x/o have been placed
    int turn = 0; // keep count of how may x/o have been placed and how many turns have passed

    fillUp(pgame);
    printTicToc(pgame);

    printf("Instruction: Input the line number and right next to it the symbol you wish to play with(use x and o pls):\n");

    while(test == 1){
        if(turn % 2 == 0){
            printf("TURN: %d -- x\n", (turn + 1));
        }else{
            printf("TURN: %d -- 0\n", (turn + 1));
        }

        i = getNum("Input line(1-9): ", 'd') - 1;
        while(i < 0 || i > 8){
            printf("WRONG INPUT, please use numbers from 1 to 9\n");
            i = getNum("Input line(1-9): ", 'd') - 1;
        }
        /*Gets the position(1-9) -- turns it in a array position (0-8)
        (if it isn't o-8 it will scan it again*/

        i = checkRewrite(i, memory, &turn);
        while(i == -1){
            printf("THE BOX IS ALREADY FILLED\n");
            i = getNum("Input line(1-9): ", 'd') - 1;
            while(i < 0 || i > 8){
                printf("WRONG INPUT, please use numbers from 1 to 9\n");
                i = getNum("Input line(1-9): ", 'd') - 1;
            }
            i = checkRewrite(i, memory, &turn);
        }
        /*Checks if the position has already been used 
        -- re-scans it and rechecks it to be between 1-9*/
        if(turn % 2 == 0){
            game[i] = 'o';
        }else{
            game[i] = 'x';
        }
        /*Even turns are 'o'; uneven turns are 'x'*/

        test = checkWin(pgame);
        if( turn == 9 && test == 1){
            printf("........TIE........\n");
            printTicToc(pgame);
            break;
        }
        /*if all positions are filled than declare a TIE 
        -- also check that the last "move" wasn't the winning one*/         
       
        printTicToc(pgame);

    }   

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
    int x;
    char y;

    printf("%s", a);
    switch (cond)
    {
    case ('d'):
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &x);
            return x;
        break;
    case ('c'):
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%c", &y);
            return y;
        break;
    default:
        return x;
        break;
    }
}

    /*Gets the input from user -- also checks it to be either int or char*/

int checkWin(char *game){
    int i;
    int j;
    int test = 1;

    if((*(game + 0) == *(game + 4)) && (*(game + 0) == *(game + 8))){
                printf("......YOU WON......\n");
                test = 0;
    }
    else if((*(game + 2) == *(game + 4)) && (*(game + 2) ==  *(game + 6))){
                printf("......YOU WON......\n");
                test = 0;

    }
   
    for(i = 0, j = 0; i < 3 && test == 1; i++, j += 2){
            if((*(game + i + j) == *(game + i + j + 1)) && (*(game + i + j) == *(game + i + j + 2))){
                printf("......YOU WON......\n");
                test = 0;
                break;
            }
            else if((*(game + i) == *(game + i + 3)) && (*(game + i) == *(game + i + 6))){
                printf("......YOU WON......\n");
                test = 0;
                break;
            }      
        }

        return test;
}
       
        /*checks for a win condition by comparing every
        line across, then downward, then both diagonals
        and return 0 for win and 1 for lose*/

int checkRewrite(int i, int memory[], int *k){
    int x;
    for(x = 0; x < *k; x++){
        if( i == *(memory + x)){
            return -1;
        }
    }
    *(memory + *k) = i;
    *k = *k + 1;
    return i;
}
        /*Checks if the position has already been used, 
        if yes => returns -1, 
        if not => saves the position in an array and returns it to main*/