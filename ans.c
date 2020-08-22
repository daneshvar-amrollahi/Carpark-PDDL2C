#include <math.h>
#include <klee/klee.h>

#define numOfActions 4
#define numOfcars 12
#define numOfcurbs 7

#define car_00 0
#define car_01 1
#define car_02 2
#define car_03 3
#define car_04 4
#define car_05 5
#define car_06 6
#define car_07 7
#define car_08 8
#define car_09 9
#define car_10 10
#define car_11 11

#define curb_0 0
#define curb_1 1
#define curb_2 2
#define curb_3 3
#define curb_4 4
#define curb_5 5
#define curb_6 6

bool at-curb[numOfcars + 1];
bool at-curb-num[numOfcars + 1][numOfcurbs + 1];
bool behind-car[numOfcars + 1][numOfcars + 1];
bool car-clear[numOfcars + 1];
bool curb-clear[numOfcurbs + 1];
