#include <stdio.h>

FILE* fout;

char m2[65][65];
int main() {

    // Q1
    int L,R,B;
    L = 5;R = 12;B = 13;
    if ((fout = fopen("output_question_5_1","w"))==NULL){
        printf("Can not open output file\n");
    }
    for(int i=0;i<5;i++){
        if(i%2==0){
            fprintf(fout, "B R B R B\n");
        }
        else{
            fprintf(fout, "R B R B R\n");
        }
    }
    fclose(fout);

    // Q2
    int G,W,Y;
    L=64;R=139;B=1451;G=977;W=1072;Y=457;
    if ((fout = fopen("output_question_5_2","w"))==NULL){
        printf("Can not open output file\n");
    }
    for(int i=0;i<L;i++){
        if(i%2==0){
            for(int j=0;j<L/2;j++){
                if(G>0){
                    m2[i][2*j] = 'G';
                    G--;
                }
                else{
                    m2[i][2*j] = 'W';
                    W--;
                }

                if(R>0){
                    m2[i][2*j+1] = 'R';
                    R--;
                }
                else if(B>0){
                    m2[i][2*j+1] = 'B';
                    B--;
                }
                else if(Y>0){
                    m2[i][2*j+1] = 'Y';
                    Y--;
                }
            }
        }
        else{
            for(int j=0;j<L/2;j++){
                if(R>0){
                    m2[i][2*j] = 'R';
                    R--;
                }
                else if(B>0){
                    m2[i][2*j] = 'B';
                    B--;
                }
                else if(Y>0){
                    m2[i][2*j] = 'Y';
                    Y--;
                }

                if(G>0){
                    m2[i][2*j+1] = 'G';
                    G--;
                }
                else{
                    m2[i][2*j+1] = 'W';
                    W--;
                }
            }
        }
    }
    m2[63][62] = m2[0][0];
    m2[0][0] = 'W';

    for(int i=0;i<L;i++){
        for(int j=0;j<L;j++){
            fprintf(fout, "%c ", m2[i][j]);
        }
        fprintf(fout, "\n");
    }
    return 0;
}
