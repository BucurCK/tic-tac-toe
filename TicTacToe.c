/**
 * TODO: Create functions cause this code is UGLY
 * TODO: Make it impossible to rewrite symbols in the game
 * * Maybe just make the choice of symbols (x/o) automatic
 * ! Add an AI(or something like that) so you can play solo - you sad FUCK
 * * Try to make some kind GUI for this(don't know how atm) 
 * * Write the functions in different files(just to learn it -- for this kind of short code it's pretty useless)
 */

#include <stdio.h>

#define SIZE 3

char line[10];

int main(){
    char game[SIZE][SIZE];
    int i, j, k = 49;
    int test = 1; // keeps the while going till a win condition is met
    int pos; //position form 1-9
    char sym; //the symbol used in the game (will set in the future to only be x or o)


    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            game[i][j] = k;
            k++;
        }
    }
    /*Fill up the matrix with ASCII codes for 1-9 (starts from '49' = 1)*/
    
    printf("    | %c | %c | %c |\n",game[0][0], game[0][1], game[0][2]);
    printf("    | %c | %c | %c |\n",game[1][0], game[1][1], game[1][2]);
    printf("    | %c | %c | %c |\n",game[2][0], game[2][1], game[2][2]);
    printf("\n");
    /*Print the initial state of the game (filled with 1-9)*/

    printf("Instruction: Input the line number and right next to it the symbol you wish to play with(use x and o pls):\n");

    while(test == 1){

        resetPosition:
        printf("Input line(1-9): ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &pos);
        if(pos < 1 || pos > 9){
            printf("WRONG INPUT, please use numbers from 1 to 9\n");
            goto resetPosition;
        }
        i = (pos-1) / 3;
        j = (pos-1) % 3;
        /*Gets the position int then checks it to be between 1-9 
        (if not it will scan it again -- goto -- ) and than it 
        assigns that to a position in the matrix(by dividing and 
        assigning the whole part to i and fractional to j -- this 
        will always give the correct position in a 3by3 matrix*/

        resetSymbol:
        printf("Input symbol: ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%c", &sym);
        if(sym != 'x' && sym != 'o'){
            printf("WRONG INPUT, please use x or o\n");
            goto resetSymbol;
        }
        game[i][j] = sym;
        /*Gets the symbol char then checks it to be either x or o;
        if not it will scan it again and than assign it to a 
        position in the matrix*/

        for(i = 0; i < SIZE && test == 1; i++){
            if((game[0][i] == game[1][i]) && (game[2][i] == game[1][i])){
                printf("......YOU WON......\n");
                test = 0;
                break;
            }
            else if((game[i][0] == game[i][1]) && (game[i][2] == game[i][1])){
                printf("......YOU WON......\n");
                test = 0;
                break;
            }
            else if((game[0][0] == game[1][1]) && (game[2][2] == game[1][1])){
                printf("......YOU WON......\n");
                test = 0;
                break;
            }
            else if((game[0][2] == game[1][1]) && (game[2][0] ==  game[1][1])){
                printf("......YOU WON......\n");
                test = 0;
                break;
            }

        }
        /*it will check for a win condition by checking every line across, 
        then downward, then both diagonals*/

        //TODO: the diagonals check should be moved outside the for, because it shouldn't be checked 3 times :) )
        
    printf("   | %c | %c | %c |\n",game[0][0], game[0][1], game[0][2]);
    printf("   | %c | %c | %c |\n",game[1][0], game[1][1], game[1][2]);
    printf("   | %c | %c | %c |\n",game[2][0], game[2][1], game[2][2]);
    printf("\n");

    /*Prints the current state of the game*/

    }    

    return 0;
}


