#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point {
    double x;
    double y;
};


typedef struct {
    double* ptr;
    int max_el;
    int count_el;

} FancyList;


double euclidean_dist(struct Point p1, struct Point p2) {

    double x_term = pow((p1.x-p2.x), 2);
    double y_term = pow((p1.y-p2.y), 2);

    return pow(x_term + y_term, 0.5);
}


void append(FancyList *one, double app) {

    if ((*one).max_el > (*one).count_el) {
        *((*one).ptr + (*one).count_el) = app;
        (*one).count_el++;
    }
    else {
        (*one).ptr = realloc((*one).ptr, ((*one).max_el+1 * sizeof(double)));
        (*one).max_el++;
        *((*one).ptr + (*one).count_el) = app;
        (*one).count_el++;
    }
    printf("%lf\n", *((*one).ptr + (*one).count_el-1));

    return;
}


int main(void) {

    /*
    double x1, y1, x2, y2;

    printf("Enter x1: ");
    scanf("%lf", &x1);
    printf("Enter y1: ");
    scanf("%lf", &y1);
    printf("Enter x2: ");
    scanf("%lf", &x2);
    printf("Enter y2: ");
    scanf("%lf", &y2);
    
    struct Point point_1 = {x1, y1};
    struct Point point_2;
    point_2.x = x2;
    point_2.y = y2;

    double distance = euclidean_dist(point_1, point_2);

    printf("%lf", distance);
    */

    FancyList *bouji_list;
    bouji_list = (FancyList *)malloc(sizeof(FancyList));
    (*bouji_list).max_el = 3;
    (*bouji_list).count_el = 0;
    (*bouji_list).ptr = malloc((*bouji_list).max_el * sizeof(double));
    *((*bouji_list).ptr) = 1;

    while (1==1) {
        printf("Enter a number (-1 to quit): ");
        double temp;
        scanf("%lf", &temp);

        if (temp == -1) {
            break;
        }

        append(bouji_list, temp);
    }

    for (int i = 0; i<(bouji_list->count_el); i++) {
        printf("%lf\n", *(bouji_list->ptr + i));
    }

    free(bouji_list);

    return 0;
}