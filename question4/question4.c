#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define row 10
#define column 20
//This is an implementation of the 8-connectivity problem using DFS.

FILE *fin, *fout;
// flag is used to count the number of clusters
int flag = 1;
// the answer and input array
int **a;
// mark for the visited unit
_Bool **visited;

int max(a, b)
{
    if (a < b)
        return b;
    return a;
}

int min(a, b)
{
    if (a > b)
        return b;
    return a;
}
//initialize a[][] and visited[][] based on the dimensions required
//dynamic arrays are used so that the program can be used for other dimensions
void init()
{
    a = (int **)malloc(sizeof(int *) * row);
    visited = (_Bool **)malloc(sizeof(_Bool *) * row);
    int i, j;
    for (i = 0; i < row; ++i)
    {
        a[i] = (int *)malloc(sizeof(int) * column);
        visited[i] = (_Bool *)malloc(sizeof(_Bool) * column);
    }
    for (i = 0; i < row; ++i)
        for (j = 0; j < column; ++j)
            visited[i][j] = 0;
}
// for every unit of the input array, check the status of all of its neighbours using DFS method
// the status check process include check whether this unit is visited and whether the value of the unit is 1
void search()
{
    int i, j;
    for (i = 0; i < row; ++i)
        for (j = 0; j < column; ++j)
        {
            if (visited[i][j])
                continue;
            visited[i][j] = 1;
            if (a[i][j])
            {
                a[i][j] = flag;
                DFS(i, j);
                //for another new cluster, the value of flag is increased
                flag++;
            }
        }
}
void DFS(int r, int c)
{
    //the following steps are used to check the 8 neighbours of the unit
    //in case of boundary violation, neccessary comparations are made
    int imin, imax, jmin, jmax;
    imin = max(0, r - 1);
    imax = min(r + 1, row - 1);
    jmin = max(0, c - 1);
    jmax = min(c + 1, column - 1);
    int i, j;
    for (i = imin; i <= imax; ++i)
        for (j = jmin; j <= jmax; ++j)
        {
            if (visited[i][j])
                continue;
            visited[i][j] = 1;
            if (a[i][j])
            {
                a[i][j] = flag;
                DFS(i, j);
            }
        }
}
int main()
{
    init();
    int i, j;
    if ((fin = fopen("input_question_4", "r")) == NULL)
        printf("Can not open input file\n");
    for (i = 0; i < row; ++i)
        for (j = 0; j < column; ++j)
            fscanf(fin, "%d", &a[i][j]);
    fclose(fin);

    search();
    if ((fout = fopen("output_question_4", "w")) == NULL)
    {
        printf("Can not open output file\n");
    }
    for (i = 0; i < row; ++i)
    {
        for (j = 0; j < column; ++j)
            fprintf(fout, "%d ", a[i][j]);
        fprintf(fout, "\n");
    }
}
