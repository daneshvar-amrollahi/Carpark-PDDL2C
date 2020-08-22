#include <math.h>
#include <klee/klee.h>

#define numOfActions 4
#define numOfcars 14
#define numOfcurbs 8

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
#define car_12 12
#define car_13 13

#define curb_0 0
#define curb_1 1
#define curb_2 2
#define curb_3 3
#define curb_4 4
#define curb_5 5
#define curb_6 6
#define curb_7 7

bool at-curb[numOfcars + 1];
bool at-curb-num[numOfcars + 1][numOfcurbs + 1];
bool behind-car[numOfcars + 1][numOfcars + 1];
bool car-clear[numOfcars + 1];
bool curb-clear[numOfcurbs + 1];

void init()
{
	at-curb[car_06] = 1;
	at-curb-num[car_06][curb_0] = 1;
	behind-car[car_04][car_06] = 1;
	car-clear[car_04] = 1;
	at-curb[car_02] = 1;
	at-curb-num[car_02][curb_1] = 1;
	behind-car[car_08][car_02] = 1;
	car-clear[car_08] = 1;
	at-curb[car_07] = 1;
	at-curb-num[car_07][curb_2] = 1;
	behind-car[car_10][car_07] = 1;
	car-clear[car_10] = 1;
	at-curb[car_11] = 1;
	at-curb-num[car_11][curb_3] = 1;
	behind-car[car_03][car_11] = 1;
	car-clear[car_03] = 1;
	at-curb[car_01] = 1;
	at-curb-num[car_01][curb_4] = 1;
	behind-car[car_09][car_01] = 1;
	car-clear[car_09] = 1;
	at-curb[car_12] = 1;
	at-curb-num[car_12][curb_5] = 1;
	behind-car[car_13][car_12] = 1;
	car-clear[car_13] = 1;
	at-curb[car_05] = 1;
	at-curb-num[car_05][curb_6] = 1;
	behind-car[car_00][car_05] = 1;
	car-clear[car_00] = 1;
	curb-clear[curb_7] = 1;
}

void goal()
{
	return(
		at-curb-num[car_00][curb_0] == 1 && 
		behind-car[car_08][car_00] == 1 && 
		at-curb-num[car_01][curb_1] == 1 && 
		behind-car[car_09][car_01] == 1 && 
		at-curb-num[car_02][curb_2] == 1 && 
		behind-car[car_10][car_02] == 1 && 
		at-curb-num[car_03][curb_3] == 1 && 
		behind-car[car_11][car_03] == 1 && 
		at-curb-num[car_04][curb_4] == 1 && 
		behind-car[car_12][car_04] == 1 && 
		at-curb-num[car_05][curb_5] == 1 && 
		behind-car[car_13][car_05] == 1 && 
		at-curb-num[car_06][curb_6] == 1 && 
		at-curb-num[car_07][curb_7] == 1 
	)
}void move_curb_to_curb(int car, int curbsrc, int curbdest)
{
	klee_assume(car-clear[car] == 1);
	klee_assume(curb-clear[curbdest] == 1);
	klee_assume(at-curb-num[car][curbsrc] == 1);

	curb-clear[curbdest] = 0;
	curb-clear[curbsrc] = 1;
	at-curb-num[car][curbdest] = 1;
	at-curb-num[car][curbsrc] = 0;
}

void move-curb-to-car(int car, int curbsrc, int cardest)
{
	klee_assume(car-clear[car] == 1);
	klee_assume(car-clear[cardest] == 1);
	klee_assume(at-curb-num[car][curbsrc] == 1);
	klee_assume(at-curb[cardest] == 1);

	car-clear[cardest] = 0;
	curb-clear[curbsrc] = 1;
	behind-car[car][cardest] = 1;
	at-curb-num[car][curbsrc] = 0;
	at-curb[car] = 0;
}

void move-car-to-curb(int car, int carsrc, int curbdest)
{
	klee_assume(car-clear[car] == 1);
	klee_assume(curb-clear[curbdest] == 1);
	klee_assume(behind-car[car][carsrc] == 1);

	curb-clear[curbdest] = 0;
	car-clear[carsrc] = 1;
	at-curb-num[car][curbdest] = 1;
	behind-car[car][carsrc] = 0;
	at-curb[car] = 1;
}


void move-car-to-car(int car, int carsrc, int cardest)
{
	klee_assume(car-clear[car] == 1);
	klee_assume(car-clear[cardest] == 1);
	klee_assume(behind-car[car][carsrc] == 1);
	klee_assume(at-curb[cardest] == 1);

	car-clear[cardest] = 0;
	car-clear[carsrc] = 1;
	behind-car[car][cardest] = 1;
	behind-car[car][carsrc] = 0;
}
int main(int argc, const char * argv[]) {

	init();

	while(!goal()){
		int choice = klee_range(0,numOfActions+1,"choice");
		//klee_assume ()
		if (choice == 0) {
			int car  = klee_range(0,numOfcars+1,"car");
			int curbsrc  = klee_range(0,numOfcurbs+1,"curbsrc");
			int curbdest  = klee_range(0,numOfcurbs+1,"curbdest");
			move_curb_to_curb(car,curbsrc,curbdest);
		} else if (choice == 2) {
			int car  = klee_range(0,numOfcars+1,"car");
			int curbsrc  = klee_range(0,numOfcurbs+1,"curbsrc");
			int cardest  = klee_range(0,numOfcars+1,"cardest");
			move_curb_to_car(car,curbsrc,cardest);
		}else if (choice == 2){
			int car  = klee_range(0,numOfcars+1,"car");
			int carsrc  = klee_range(0,numOfcars+1,"carsrc");
			int curbdest  = klee_range(0,numOfcurbs+1,"curbdest");
			move_car_to_curb(car,carsrc,curbdest);
		}else {
			int car  = klee_range(0,numOfcars+1,"car");
			int carsrc  = klee_range(0,numOfcars+1,"carsrc");
			int cardest  = klee_range(0,numOfcars+1,"cardest");
			move_car_to_car(car,carsrc,cardest);
		}
	}
	
    return 0;
}

