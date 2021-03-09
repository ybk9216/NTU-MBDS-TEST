#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define row 9
#define column 9
FILE *fout;

long long least_sum;

long long ans[3];

void init()
{
    ans[0] = column - 1; //num of R
    ans[2] = 0;          //num of R
    ans[1] = 0;           
}
void comparing(long long diff, long long sub)
{
    ans[0] -= diff / sub;
    ans[2] += diff / sub;
    ans[1] = diff % sub;
}

void calculator(long long sum)
{
    init(); 
	long long diff = sum - least_sum;
    comparing(diff, row - 1);
    path_print(sum);
}
void path_print(long long sum)
{
    if ((fout = fopen("output_question_1(a)", "a")) == NULL)
    {
        printf("Can not open output file\n");
    }
    fprintf(fout, "%lld ", sum);
    int i;
    for (i = 0; i < ans[0]; ++i)
        fprintf(fout, "R");
    for (i = 0; i < ans[1]+1; ++i)
        fprintf(fout, "D");
    if (ans[1])
        fprintf(fout, "R");
    for (i = ans[1]+1; i < row; ++i)
        fprintf(fout, "D");
    for (i = 0; i < ans[2]; ++i)
        fprintf(fout, "R");
    fprintf(fout, "\n");
}

int main()
{
    least_sum = column + (2 + row) * (row - 1) / 2;
    //int length = sizeof(num) / sizeof(num[0]);
    calculator(65);
    calculator(72);
    calculator(90);
    calculator(110);
    return 0;
}
