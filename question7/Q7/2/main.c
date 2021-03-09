#include <stdio.h>

FILE *fin,*fout;
int a[50010],b[50010][6];
int main() {
    if ((fin = fopen("input_index_7_2.txt", "r"))==NULL){
        printf("Can not open output file\n");
    }


    int L[6] ={4,8,5,9,6,7};
    int ct=0;
    char temp[100];
    fscanf(fin, "%s", temp);
    while(fscanf(fin, "%d", &a[ct])!=EOF){
        ct++;
    }
    printf("%d\n", ct);
    fclose(fin);

    fout = fopen("output_coordinates_7_2.txt", "w");
    fprintf(fout, "x1\tx2\tx3\tx4\tx5\tx6\n");
    for(int i=0;i<ct;i++){
        int tmp=a[i];

        for(int j=0;j<6;j++){
            int x = tmp%L[j];
            fprintf(fout, "%d\t", x);
            tmp = (tmp-x)/L[j];
        }
        fprintf(fout, "\n");
    }
    fclose(fout);

    if ((fin = fopen("input_coordinates_7_2.txt", "r"))==NULL){
        printf("Can not open output file\n");
    }
    ct=0;
    fscanf(fin, "%s %s %s %s %s %s", temp, temp, temp, temp, temp, temp);
    while(fscanf(fin, "%d %d %d %d %d %d", &b[ct][0], &b[ct][1], &b[ct][2], &b[ct][3], &b[ct][4], &b[ct][5])!=EOF){
        ct++;
    }
    printf("%d\n", ct);
    fclose(fin);
    fout = fopen("output_index_7_2.txt", "w");
    fprintf(fout, "index\n");
    for(int i=0;i<ct;i++){
        int index = L[0]*L[1]*L[2]*L[3]*L[4]*b[i][5] + L[0]*L[1]*L[2]*L[3]*b[i][4] + L[0]*L[1]*L[2]*b[i][3] + L[0]*L[1]*b[i][2] + L[0]*b[i][1] + b[i][0];
        fprintf(fout, "%d\n",index);
    }

    return 0;
}
