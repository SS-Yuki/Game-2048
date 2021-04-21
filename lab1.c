#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void print_map(int num[4][4]);
int rand_num(int num[4][4], char ch);

int main()
{
    int num[4][4] = {0};
    int flag = 0;
    print_map(num);
    do{
        char ch = getchar();   
        if (rand_num(num, ch))
            continue;
        print_map(num);
        flag++;
    }while(flag < 16);
    printf("game over\n");
    system("pause");
    return 0;
}

int rand_num(int num[4][4], char ch){
    int x, y;
    if (ch == 'n'){
        srand((int)time(NULL));
        do{
            x = rand() % 4;
            y = rand() % 4; 
        }while(num[x][y] == 1);
        num[x][y] = 1;
        fflush(stdin);
        return 0;
    }
    printf("Error,please input again!\n");
    fflush(stdin);
    return 1;
}

void print_map(int num[4][4]){
    int i, j, k;
    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++)
            printf("+-----");
        printf("\n");
        for (k = 0; k < 5; k++){
            if (num[i][k] == 1 && k < 4)
                printf("|  2  ");
            else printf("|     ");
        }
        printf("\n");
    }
    for (j = 0; j < 4; j++)
        printf("+-----");
    printf("\n");
}


