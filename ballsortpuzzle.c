#include <stdio.h>
#include <stdlib.h>
#include "ballsortpuzzle.h"
#include <time.h>

bool check(const int rows, const int columns, char field[rows][columns])
{
    for (int i = 0; i < columns; i++)
    {
        if (field[rows][i] == ' ')
        {
            continue;
        }

        char tmp = field[0][i];
        for (int j = 1; j < rows; j++)
        {
            if (field[j][i] != tmp)
            {
                return false;
            }
        }
    }
    return true;
}

void generator(const int rows, const int columns, char field[rows][columns])
{
    int col1, col2;
    col1 = rand() % columns;
    col2 = rand() % columns;
    while (col1 == col2)
    {
        col2 = rand() % columns;
    }

    for (int i = 0; i < rows; i++)
    {
        field[i][col1] = ' ';
        field[i][col2] = ' ';
    }

    char symbols[10] = {'*', '&', '+', '^', '$', '#', '%', '-', '=', '@'};
    int countArr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (j == col1 || j == col2)
            {
                continue;
            }

            int index = rand() % (columns - 2); // 0 - 3
            if (countArr[index] < rows)
            {
                // we can generate
                field[i][j] = symbols[index];
                countArr[index]++;
            }
            else
            {
                while (countArr[index] >= rows)
                {
                    index = rand() % (columns - 2);
                }
                field[i][j] = symbols[index];
                countArr[index]++;
            }
        }
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y)
{
    if (x == y || x > columns || y > columns || x < 1 || y < 1)
    {
        puts("\n  ___ _ __ _ __ ___  _ __ ");
        puts(" / _ \\ '__| '__/ _ \\| '__|");
        puts("|  __/ |  | | | (_) | |   ");
        puts(" \\___|_|  |_|  \\___/|_| \n");
    }
    else
    {
        // get symbol
        char tmp = '\0';
        int i = 0;
        for (i = 0; i < rows; i++)
        {
            if (field[i][x - 1] != ' ')
            {
                tmp = field[i][x - 1];
                field[i][x - 1] = ' ';
                break;
            }
        }

        if (field[0][y - 1] != ' ')
        {
            field[i][x - 1] = tmp;
            puts("\n  ___ _ __ _ __ ___  _ __ ");
            puts(" / _ \\ '__| '__/ _ \\| '__|");
            puts("|  __/ |  | | | (_) | |   ");
            puts(" \\___|_|  |_|  \\___/|_| \n");
        }
        else
        {
            for (int j = 0; j < rows; j++)
            {
                if (field[j + 1][y - 1] == tmp)
                {
                    field[j][y - 1] = tmp;
                    break;
                }
                else if (j == rows - 1)
                {
                    field[j][y - 1] = tmp;
                }
                else if (field[j + 1][y - 1] == ' ')
                {
                    continue;
                }
                else
                {
                    field[i][x - 1] = tmp;

                    puts("\n  ___ _ __ _ __ ___  _ __ ");
                    puts(" / _ \\ '__| '__/ _ \\| '__|");
                    puts("|  __/ |  | | | (_) | |   ");
                    puts(" \\___|_|  |_|  \\___/|_| \n");
                    break;
                }
            }
        }
    }
}

void game_field(const int rows, const int columns, char field[rows][columns])
{

    printf("  ");
    for (int j = 0; j < columns; j++)
    {
        printf("----------");
    }
    printf("\n");
    for (int j = 0; j < columns; j++)
    {
        printf("       ╭  ");
    }
    printf("\n");

    for (int j = 0; j < columns; j++)
    {
        printf("       ╭╯ ");
    }
    printf("\n");

    for (int j = 0; j < columns; j++)
    {
        printf("     ╭╯╭╯ ");
    }
    printf("\n\n");

    for (int j = 0; j < columns; j++)
    {
        printf("  ╭╯    ╰╮");
    }
    printf("\n");

    for (int i = 0; i < rows; i++)
    {
        printf(" %d ", i + 1);
        for (int j = 0; j < columns; j++)
        {
            printf("▏  %c ▕    ", field[i][j]);
        }
        printf("\n");
    }

    for (int j = 0; j < columns; j++)
    {
        printf("   \\    / ");
    }
    printf("\n");

    for (int j = 0; j < columns; j++)
    {
        printf("    ----  ");
    }
    printf("\n");

    for (int j = 0; j < columns; j++)
    {
        printf("      %d   ", j + 1);
    }
    printf("\n");
}

void ball_sort_puzzle()
{
    srand(time(NULL));
    int rows, columns, x, y, correct;
    do
    {
        correct = 1;

        printf("Enter rows: ");
        if (scanf("%d", &rows) != 1 || rows <= 1)
        {
            correct = 0;
            printf("Invalid input.\n");
            while (getchar() != '\n')
            {
            }
        }
        puts("");
        printf("Enter cols: ");
        if (scanf("%d", &columns) != 1 || columns <= 3 || columns > 10)
        {
            correct = 0;
            printf("Invalid input.\n");
            while (getchar() != '\n')
            {
            }
        }
        puts("");

    } while (correct == 0);

    char field[rows][columns];

    do
    {
        generator(rows, columns, field);
    } while (check(rows, columns, field));

    while (!check(rows, columns, field))
    {
        game_field(rows, columns, field);

        printf("\n");

        do
        {
            correct = 1;

            printf("Enter what: ");
            if (scanf("%d", &x) != 1)
            {
                correct = 0;
                printf("Invalid input.\n");
                while (getchar() != '\n')
                {
                }
            }
            puts("");
            printf("Enter where: ");
            if (scanf("%d", &y) != 1)
            {
                correct = 0;
                printf("Invalid input.\n");
                while (getchar() != '\n')
                {
                }
            }
            puts("");

        } while (correct == 0);

        down_possible(rows, columns, field, x, y);
    }

    game_field(rows, columns, field);
    puts("\n⣾⡇⣿⣿⡇⣾⣿⣿⣿⣿⣿⣿⣿⣿⣄⢻⣦⡀⠁⢸⡌⠻⣿⣿⣿⡽⣿⣿     ┌─────────────────────┐");
    puts("⡇⣿⠹⣿⡇⡟⠛⣉⠁⠉⠉⠻⡿⣿⣿⣿⣿⣿⣦⣄⡉⠂⠈⠙⢿⣿⣝⣿     │ Congratulations!    │");
    puts("⠤⢿⡄⠹⣧⣷⣸⡇⠄⠄⠲⢰⣌⣾⣿⣿⣿⣿⣿⣿⣶⣤⣤⡀⠄⠈⠻⢮     │ You won!            │");
    puts("⠄⢸⣧⠄⢘⢻⣿⡇⢀⣀⠄⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠄⢀     └─────────────────────┘");
    puts("⠄⠈⣿⡆⢸⣿⣿⣿⣬⣭⣴⣿⣿⣿⣿⣿⣿⣿⣯⠝⠛⠛⠙⢿⡿⠃⠄⢸");
    puts("⠄⠄⢿⣿⡀⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⡾⠁⢠⡇⢀");
    puts("⠄⠄⢸⣿⡇⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⣫⣻⡟⢀⠄⣿⣷⣾");
    puts("⠄⠄⢸⣿⡇⠄⠈⠙⠿⣿⣿⣿⣮⣿⣿⣿⣿⣿⣿⣿⣿⡿⢠⠊⢀⡇⣿⣿");
    puts("⠒⠤⠄⣿⡇⢀⡲⠄⠄⠈⠙⠻⢿⣿⣿⠿⠿⠟⠛⠋⠁⣰⠇⠄⢸⣿⣿⣿");
}