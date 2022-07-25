#include <stdio.h>

#define SIZE 3

int main(){
    char nr[SIZE][SIZE];
    int i, j, k = 49;
    int test = 1;
    int pos;
    char sym;


    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            nr[i][j] = k;
            k++;
        }
    }
    
    printf("| %c | %c | %c |\n",nr[0][0], nr[0][1], nr[0][2]);
    printf("| %c | %c | %c |\n",nr[1][0], nr[1][1], nr[1][2]);
    printf("| %c | %c | %c |\n",nr[2][0], nr[2][1], nr[2][2]);
    printf("\n");

    printf("Instruction: Input the line number and right next to it the symbol you wish to play with(use x and o pls):\n");

    while(test == 1){

        restart:

        printf("Input line(1-9) and the symbol:\n");
        scanf("%d", &pos);
        if(pos < 1 && pos > 9){
            printf("WRONG INPUT, please use numbers 1 to 9\n");
            goto restart;
        }
        i = (pos-1) / 3;
        j = (pos-1) % 3;

        printf("Input symbol:\n");
        scanf("%c", &sym);
        if(sym != 'x' && sym != 'o'){
            printf("WRONG INPUT, please use x or o\n");
            goto restart;
        }
        nr[i][j] = sym;

        for(i = 0; i < SIZE && test == 1; i++){
            if((nr[0][i] == nr[1][i]) && (nr[2][i] == nr[1][i])){
                printf("YOU WON\n");
                test = 0;
                break;
            }
            else if((nr[i][0] == nr[i][1]) && (nr[i][2] == nr[i][1])){
                printf("YOU WON\n");
                test = 0;
                break;
            }
            else if((nr[0][0] == nr[1][1]) && (nr[2][2] == nr[1][1])){
                printf("YOU WON\n");
                test = 0;
                break;
            }
            else if((nr[0][2] == nr[1][1]) && (nr[2][0] ==  nr[1][1])){
                printf("YOU WON\n");
                test = 0;
                break;
            }

        }

    printf("| %c | %c | %c |\n",nr[0][0], nr[0][1], nr[0][2]);
    printf("| %c | %c | %c |\n",nr[1][0], nr[1][1], nr[1][2]);
    printf("| %c | %c | %c |\n",nr[2][0], nr[2][1], nr[2][2]);
    printf("\n");
    }    

    return 0;
}