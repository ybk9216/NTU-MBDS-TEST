#include <stdio.h>

FILE *fin,*fout;
int a[10010],b[10010][2];
int main() {
//    printf("Hello, World!\n");
    ;
    if ((fin = fopen("input_index_7_1.txt", "r"))==NULL){
        printf("Can not open output file\n");
    }

    int L1,L2;
    L1=50;
    L2=57;
    int ct=0;
    char temp[100];
    fscanf(fin, "%s", temp);
    while(fscanf(fin, "%d", &a[ct])!=EOF){
        ct++;
    }
    printf("%d\n", ct);
    fclose(fin);
    fout = fopen("output_coordinates_7_1.txt", "w");
    fprintf(fout, "x1\tx2\n");
    for(int i=0;i<ct;i++){
        int x2 = a[i]/L1;
        int x1 = a[i]-x2*L1;
        fprintf(fout, "%d\t%d\n", x1, x2);
    }
    fclose(fout);

    if ((fin = fopen("input_coordinates_7_1.txt", "r"))==NULL){
        printf("Can not open output file\n");
    }
    ct=0;
    fscanf(fin, "%s %s", temp, temp);
    while(fscanf(fin, "%d %d", &b[ct][0], &b[ct][1])!=EOF){
        ct++;
    }
    printf("%d\n", ct);
    fclose(fin);
    fout = fopen("output_index_7_1.txt", "w");
    fprintf(fout, "index\n");
    for(int i=0;i<ct;i++){
        int index = b[i][1]*L1+b[i][0];
        fprintf(fout, "%d\n",index);
    }

    return 0;
}
