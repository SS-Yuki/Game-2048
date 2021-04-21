#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void game_setting();                     //游戏模式设置
void game_init();                        //游戏初始化
void game_execute();                     //游戏运行
void print_map();                        //打印地图
void imple_map(int *fill_p);             //操作地图
void lrchange_map();                     //左右对称
void udchange_map();                     //上下对称
void trans_map();                        //转置
void fill_map(int fill_judge, int flag); //随机填充2

int map[4][4] = {0};
int mode[2] = {64, 2048};
int sign = 1;

int main()
{
    game_setting();
    game_init();
    game_execute();
    system("pause");
    return 0;
}

void game_setting()
{
    char ch1 = 0, ch2 = 0;
    printf("2048\n(Input '-t' to switch mode.\n Enter enter to start.)\n");
    while (1)
    {
        ch1 = getch();
        if (ch1 == 13)
        {
            printf("GAME START!!\n");
            break;
        }
        else if (ch1 == '-' && (ch2 = getch()) == 't')
        {
            sign = 1 - sign;
            printf("transform into %d;\n", mode[sign]);
        }
    }
}

void game_init()
{
    int x1, x2, y1, y2;
    srand((int)time(NULL));
    do
    {
        x1 = rand() % 4;
        y1 = rand() % 4;
        x2 = rand() % 4;
        y2 = rand() % 4;
    } while (x1 == x2 && y1 == y2);
    map[x1][y1] = 2;
    map[x2][y2] = 2;
    print_map();
}

void game_execute()
{
    int flag = 0;
    do
    {
        int fill_judge = 0, *fill_p = &fill_judge;
        flag = 0;
        char ch = getch();
        if (ch == 'a') //左移
        {
            imple_map(fill_p);
        }
        else if (ch == 's') //右移
        {
            lrchange_map();
            imple_map(fill_p);
            lrchange_map();
        }
        else if (ch == 'w') //上移
        {
            trans_map();
            imple_map(fill_p);
            trans_map();
        }
        else if (ch == 'z') //下移
        {
            udchange_map();
            trans_map();
            imple_map(fill_p);
            trans_map();
            udchange_map();
        }
        else //错误输入判定
        {
            printf("Error,please input again!\n");
            fflush(stdin);
            flag = 1;
            continue;
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (map[i][j] == 0)
                    flag = 1;
            }
        }
        fill_map(fill_judge, flag);
        print_map();
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (map[i][j] == mode[sign])
                {
                    printf("Congratulations,you win!\n");
                    flag = 0;
                }
            }
        }
    } while (flag);
    printf("Game over!\n");
}

void print_map()
{
    int i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            printf("+-----");
        printf("\n");
        for (k = 0; k < 5; k++)
            (map[i][k] != 0 && k < 4) ? printf("|%5d", map[i][k]) : printf("|     ");
        printf("\n");
    }
    for (j = 0; j < 4; j++)
        printf("+-----");
    printf("\n");
}

void imple_map(int *fill_p)
{
    int i, j, k, tem[4][4];
    for (int i = 0; i < 4; i++) //数组拷贝
    {
        for (int j = 0; j < 4; j++)
        {
            tem[i][j] = map[i][j];
        }
    }
    for (i = 0; i < 4; i++) //逐行操作
    {
        for (j = 0; j < 3; j++)
        {
            for (k = j + 1; k < 4; k++)
            {
                //分情况进行讨论
                if (map[i][j] == 0 && map[i][k] != 0)
                {
                    map[i][j] = map[i][k];
                    map[i][k] = 0;
                }
                else if (map[i][j] != 0 && map[i][k] == map[i][j])
                {
                    map[i][j] = map[i][j] * 2;
                    map[i][k] = 0;
                    break;
                }
                else if (map[i][j] != 0 && map[i][k] != 0 && map[i][k] != map[i][j] && k == j + 1)
                {
                    break;
                }
                else if (map[i][j] != 0 && map[i][k] != 0 && map[i][k] != map[i][j] && k > j + 1)
                {
                    map[i][j + 1] = map[i][k];
                    map[i][k] = 0;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++) //检测数组是否改变
    {
        for (int j = 0; j < 4; j++)
        {
            if (tem[i][j] != map[i][j])
            {
                *fill_p = 1;
                break;
            }
        }
    }
}

void lrchange_map()
{
    int tem[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tem[i][j] = map[i][3 - j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            map[i][j] = tem[i][j];
        }
    }
}

void udchange_map()
{
    int tem[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tem[i][j] = map[3 - i][j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            map[i][j] = tem[i][j];
        }
    }
}

void trans_map()
{
    int tem[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tem[i][j] = map[j][i];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            map[i][j] = tem[i][j];
        }
    }
}

void fill_map(int fill_judge, int flag)
{
    int x, y;
    if (fill_judge == 0 || flag == 0)
        return;
    srand((int)time(NULL));
    do
    {
        x = rand() % 4;
        y = rand() % 4;
    } while (map[x][y] != 0);
    map[x][y] = 2;
}