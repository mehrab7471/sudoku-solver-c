#include <stdio.h>
#include <sys/time.h>

int sudoku[9][9];

int get_row[9];

int get_col[9];

int get_box[3][3];

int empty_cells = 0;

int check(int row, int col, int number);

void create_row(int index);

void create_col(int index);

void create_box(int row, int col);

int diagnose_row_and_col(int index);

void print();

int read();

long long current_time_millis();

int main()
{
    long long start = current_time_millis();

    if (!read())
    {
        return 0;
    }

    printf("\nyour sudoku is : \n\n");
    print();
    printf("\nsolving...\n\n");
    int empty_rows[empty_cells];
    int empty_cols[empty_cells];
    int count = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j] != 0)
                continue;
            empty_rows[count] = i;
            empty_cols[count] = j;
            count++;
        }
    }

    int append_value[empty_cells];
    for (int i = 0; i < empty_cells; i++)
    {
        append_value[i] = 0;
    }

    for (int i = 0; i < empty_cells; i++)
    {
        for (int j = append_value[i] + 1; j <= 9; j++)
        {
            if (check(empty_rows[i], empty_cols[i], j))
            {
                append_value[i] = j;
                break;
            }
        }
    label:
        if (sudoku[empty_rows[i]][empty_cols[i]] == 0)
        {
            check(empty_rows[i - 1], empty_cols[i - 1], 0);
            append_value[i] = 0;
            if (append_value[i - 1] != 9)
            {
                i -= 2;
            }
            else
            {
                i--;
                goto label;
            }
        }
    }

    printf("here you are :)\n\n");
    print();
//    getchar();
    long long end = current_time_millis();
    printf("time: %lld", end - start);


    return 0;
}

long long current_time_millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

void print()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%i ", sudoku[i][j]);
            if (j == 2 || j == 5)
                printf("| ");
        }
        printf("\n");
        if (i == 2 || i == 5)
            printf("---------------------\n");
    }
}

int diagnose_row_and_col(int index)
{
    index++;
    if (index <= 3)
        return 3;
    if (index <= 6)
        return 6;
    return 9;
}

void create_box(int row, int col)
{
    int temp_col = col;

    for (int i = 0; i < 3; i++)
    {
        col = temp_col;
        for (int j = 0; j < 3; j++)
        {
            get_box[i][j] = sudoku[row - 3][col - 3];
            col++;
        }
        row++;
    }
}

void create_row(int index)
{

    for (int i = 0; i < 9; i++)
    {
        get_row[i] = sudoku[index][i];
    }
}

void create_col(int index)
{

    for (int i = 0; i < 9; i++)
    {
        get_col[i] = sudoku[i][index];
    }
}

int check(int row, int col, int number)
{
    if (number != 0)
    {
        create_row(row);
        create_col(col);
        for (int i = 0; i < 9; i++)
        {
            if (get_row[i] == number ||
                get_col[i] == number)
            {
                return 0;
            }
        }
        int diagnosed_row = diagnose_row_and_col(row);
        int diagnosed_col = diagnose_row_and_col(col);
        create_box(diagnosed_row, diagnosed_col);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (get_box[i][j] == number)
                {
                    return 0;
                }
            }
        }
    }
    sudoku[row][col] = number;
    return 1;
}

int read()
{
    FILE *file;
    int number;
    file = fopen("sudoku.txt", "r");
    if (file == NULL)
    {
        printf("sudoku.txt is not available\n");
        return 0;
    }

    int row = 0;
    int col = 0;
    while ((number = fgetc(file)) != EOF)
    {
        if (number != '\n')
        {
            if (!check(row, col, number - 48))
            {
                printf("sudoku is not valid\n");
                fclose(file);
                return 0;
            }
            if (number == '0')
                empty_cells++;
        }
        else
        {
            row++;
            col = -1;
        }

        col++;
        if (col == 9)
            col = 0;
    }

    fclose(file);
    return 1;
}