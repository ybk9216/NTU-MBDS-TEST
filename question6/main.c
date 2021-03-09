#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 1E-07

typedef struct{
    double x, y;
} POINT;

typedef struct {
    double min_x, min_y, max_x, max_y;
} BOX;

FILE *fin, *fout;
POINT poly[1005];
POINT test_data[1005];


void get_bounding_box(BOX *box, POINT *poly, int N){
    int i;
    box->min_x = poly[0].x;
    box->max_x = poly[0].x;
    box->min_y = poly[0].y;
    box->max_y = poly[0].y;
    for (i=1;i<N;i++){
        if  (poly[i].x > box->max_x) box->max_x=poly[i].x;
        if  (poly[i].x < box->min_x) box->min_x=poly[i].x;
        if  (poly[i].y > box->max_y) box->max_y=poly[i].y;
        if  (poly[i].y < box->min_y) box->min_y=poly[i].y;
    }
}

int p_outside_bounding_box(BOX box, POINT p){
    int flag = 0;
    if (p.x < box.min_x || p.x > box.max_x) flag = 1;
    if (p.y < box.min_y || p.y > box.max_y) flag = 1;
    return flag;
}

//check 3 points if on one line
double cross_pro(POINT p1, POINT p2, POINT p)
{
    return ((p1.x - p.x) * (p2.y - p.y) - (p2.x - p.x) * (p1.y - p.y));
}

int p_online(POINT p1,POINT p2, POINT p){
    double area2;
    if  ((p.x == p1.x) && (p.y == p1.y)) return 1;
    if  ((p.x == p2.x) && (p.y == p2.y)) return 1;
    if  ((p.x >= p1.x) && (p.x >= p2.x)) return 0;
    if  ((p.x <= p1.x) && (p.x <= p2.x)) return 0;
    if  ((p.y >= p1.y) && (p.y >= p2.y)) return 0;
    if  ((p.y <= p1.y) && (p.y <= p2.y)) return 0;
    area2=cross_pro(p1,p2,p);
    if (fabs(area2)<EPS)  return 1;
    return 0;
}

int intersect(POINT A,POINT B, POINT C, POINT D){
    double r,s;
    double t1,t2,t3;
    t2 = (B.x - A.x) * (D.y - C.y) - (B.y-A.y) * (D.x - C.x);
    t1 = (A.y - C.y) * (D.x - C.x) - (A.x-C.x) * (D.y-C.y);
    if  ( (fabs(t2) < EPS) && (fabs(t1) < EPS) ) return -1;
    if  ( (fabs(t2) < EPS) && (fabs(t1) >= EPS) ) return 0;
    r = t1 / t2;
    if  ( (r < 0.0) || (r > 1.0)) return 0;
    t3 = (A.y-C.y)*(B.x-A.x)-(A.x-C.x)*(B.y-A.y);
    s = t3 / t2;
    if  ( (s < 0.0) || (s > 1.0)) return 0;
    return 1;
}

int is_inside(POINT poly[],int NN, POINT q) {
    BOX box;
    int flag_box, flag_online, flag;
    int NN_cross = 0;
    POINT qi[9], qk;   // not use 0
    int i, j, k;
    double slope, dy, dx, dy2, dx2;
    double shift_rd = 0.0;
    get_bounding_box(&box, poly, NN);
//check 1 -- BoundingBox check 
//Find the boundary of the polygon rectangle (the range of the maximum and minimum coordinate values of the vertices)
//judge whether the point is outside the boundary of the rectangle
    flag_box = p_outside_bounding_box(box, q);
    if (flag_box == 1) return 0;

//check 2 -- Vertex and Online check
//Determine whether the point coincides with the vertex or is on the edge  
    flag_online = 0;
    for (i = 0; i < NN; i++) {
        if (p_online(poly[i], poly[i + 1], q) == 1) {
            flag_online = 1;
            break;
        };
    };
    if (flag_online == 1) return 2;

// make qi[1]
//Make eight directions of rays (left, bottom, right, top, bottom left, bottom right, top right, top left) 
    srand((unsigned)time(NULL));
    qi[1].x = box.min_x - 1.0;
    qi[1].y = q.y;
    qi[2].x = box.max_x + 1.0;
    qi[2].y = q.y;
    qi[3].y = box.min_y - 1.0;
    qi[3].x = q.x;
    qi[4].y = box.max_y + 1.0;
    qi[4].x = q.x;
    shift_rd = (double) rand() / ((double) (RAND_MAX) + (double) (1)) * 2.0;
//    printf("%lf\n", shift_rd);
    qi[5].x = box.min_x - 1.0;
    qi[5].y = box.min_y - shift_rd;
    qi[6].x = box.max_x + shift_rd;
    qi[6].y = box.min_y - 1.0;
    shift_rd = (double) rand() / ((double) (RAND_MAX) + (double) (1)) * 2.0;
//    printf("%lf\n", shift_rd);
    qi[7].x = box.max_x + 1.0;
    qi[7].y = box.max_y + shift_rd;
    qi[8].x = box.min_x - shift_rd;
    qi[8].y = box.max_y + 1.0;
// which Ray
// Choose a ray that neither coincides with the edge line nor passes through any vertices. 
    k = 1;
    flag = 0;
    for (i = 0; i < NN; i++) {
        if ((poly[i].y == q.y) && (poly[i].x < q.x)) {
            flag = 1;
            break;
        };
    };
    if (flag == 0) goto Lab_K;
    k = 2;
    flag = 0;
    for (i = 0; i < NN; i++) {
        if ((poly[i].y == q.y) && (poly[i].x > q.x)) {
            flag = 1;
            break;
        };
    };
    if (flag == 0) goto Lab_K;
    k = 3;
    flag = 0;
    for (i = 0; i < NN; i++) {
        if ((poly[i].x == q.x) && (poly[i].y < q.y)) {
            flag = 1;
            break;
        };
    };
    if (flag == 0) goto Lab_K;
    k = 4;
    flag = 0;
    for (i = 0; i < NN; i++) {
        if ((poly[i].x == q.x) && (poly[i].y > q.y)) {
            flag = 1;
            break;
        };
    };
    if (flag == 0) goto Lab_K;
    k = 5;
    flag = 0;
    dx = q.x - qi[5].x;
    dy = q.y - qi[5].y;
    for (i = 0; i < NN; i++) {
        dx2 = poly[i].x - qi[5].x;
        dy2 = poly[i].y - qi[5].y;
        if (fabs(dy * dx2 - dx * dy2) < EPS) {
            flag = 1;
            break;
        };
    };
    if (flag == 0) goto Lab_K;
    k = 6;
    flag = 0;
    dx = q.x - qi[6].x;
    dy = q.y - qi[6].y;
    for (i = 0; i < NN; i++) {
        dx2 = poly[i].x - qi[6].x;
        dy2 = poly[i].y - qi[6].y;
        if (fabs(dy * dx2 - dx * dy2) < EPS) {
            flag = 1;
            break;
        };
    };
    if (flag == 0) goto Lab_K;
    k = 7;
    flag = 0;
    dx = q.x - qi[7].x;
    dy = q.y - qi[7].y;
    for (i = 0; i < NN; i++) {
        dx2 = poly[i].x - qi[7].x;
        dy2 = poly[i].y - qi[7].y;
        if (fabs(dy * dx2 - dx * dy2) < EPS) {
            flag = 1;
            break;
        };
    };
    if (flag == 0) goto Lab_K;
    k = 8;
    flag = 0;
    dx = q.x - qi[8].x;
//    if (fabs(dx) < EPS) goto Lab_9;
    dy = q.y - qi[8].y;
    for (i = 0; i < NN; i++) {
        dx2 = poly[i].x - qi[8].x;
        dy2 = poly[i].y - qi[8].y;
        if (fabs(dy * dx2 - dx * dy2) < EPS) {
            flag = 1;
            break;
        };
    };
    if (flag == 0) goto Lab_K;
    flag = 0;
    Lab_K:
    qk = qi[k];
// check 3
// Calculate the number of the selected ray across the wall, if it is an odd number, it will be inside, and an even number will be outside 
    for (i = 0; i < NN; i++) {
        flag = intersect(poly[i], poly[i + 1], qk, q);
        if (flag == 1) NN_cross++;
    };
    if (NN_cross % 2 == 1) {
        return 1;
    } else {
        return 0;
    }
}
int main(){
    POINT q;
    int flag;
    if ((fin = fopen("input_question_6_polygon","r"))==NULL){
        printf("Can not open input file\n");
    }
    int number_of_ploy_point = 0;
    while(fscanf(fin, "%lf %lf", &poly[number_of_ploy_point].x, &poly[number_of_ploy_point].y)!=EOF){
        number_of_ploy_point++;
    }
    fclose(fin);
    poly[number_of_ploy_point] = poly[0];

    if ((fin = fopen("input_question_6_points","r"))==NULL){
        printf("Can not open input file\n");
    }
    int number_of_test_data = 0;
    while(fscanf(fin, "%lf %lf", &test_data[number_of_test_data].x, &test_data[number_of_test_data].y)!=EOF){
        number_of_test_data++;
    }
    fclose(fin);
    if ((fout = fopen("output_question_6","w"))==NULL){
        printf("Can not open output file\n");
    }

    for(int i=0;i<number_of_test_data;i++){
        flag = is_inside(poly, number_of_ploy_point, test_data[i]);
        fprintf(fout, "%.0f %.0f ", test_data[i].x, test_data[i].y);
        if(flag>0){
            fprintf(fout, "inside\n");
        }
        else{
            fprintf(fout, "outside\n");
        }
    }
    return 0;
}
