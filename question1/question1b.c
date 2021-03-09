#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// This is an implementation of the large matrix,
//for the 9*9 dimensional problem, just simply change the value of the following parameters
#define row 90000
#define column 100000
FILE *fout;
// considering the range of data, long long type is neccessary
// least_sum stands for the least possible answer.
long long least_sum;

long long ans[3];
//ans[0] stands for the number of Rs in the first line,that also means the number of 1s
//ans[2] stands for the number of Rs in the last line,that also means the number of 100000s
//ans[1] stands for the location of the only left R
void init()
{
    ans[0] = column - 1; //num of R
    ans[2] = 0;          //num of R
    ans[1] = 0;
}
//the key to the problem, the difference between the least number and the answer decides the number of 1s and 100000s
//after several subtractions, what's left is the location of the only left R
//the advantage of this method is that the scale of data only have a slightly effect on the time of calculation
//one multiplication, one modulus operation,two divisions,and several add operations are all that required
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
//print the path given the value of array:ans
void path_print(long long sum)
{
    if ((fout = fopen("output_question_1(b)", "a")) == NULL)
    {
        printf("Can not open output file\n");
    }
    fprintf(fout, "%lld ", sum);
    int i;
    for (i = 0; i < ans[0]; ++i)
        fprintf(fout, "R");
    for (i = 0; i < ans[1] + 1; ++i)
        fprintf(fout, "D");
    if (ans[1])
        fprintf(fout, "R");
    for (i = ans[1] + 1; i < row; ++i)
        fprintf(fout, "D");
    for (i = 0; i < ans[2]; ++i)
        fprintf(fout, "R");
    fprintf(fout, "\n");
}

int main()
{
    least_sum = column + (2 + row) * (row - 1) / 2;
    //int length = sizeof(num) / sizeof(num[0]);
    /*calculator(65);
    calculator(72);
    calculator(90);
    calculator(110);*/
    calculator(87127231192);
    calculator(5994891682);
    return 0;
}
