#include <math.h>
#include <klee/klee.h>
#include <stdio.h>

#define numOfActions 4
#define numOfcars 7
#define numOfcurbs 4

#define car_00 0
#define car_01 1
#define car_02 2
#define car_03 3
#define car_04 4
#define car_05 5
#define car_06 6

#define curb_0 0
#define curb_1 1
#define curb_2 2
#define curb_3 3

int at_curb[numOfcars + 1];
int at_curb_num[numOfcars + 1][numOfcurbs + 1];
int behind_car[numOfcars + 1][numOfcars + 1];
int car_clear[numOfcars + 1];
int curb_clear[numOfcurbs + 1];
/*
; =========== INIT =========== 
;  curb_0: car_00 car_01 
;  curb_1: car_02 car_03 
;  curb_2: car_04 car_05
;  curb_3: car_06
; ========== /INIT =========== 

; =========== GOAL =========== 
;  curb_0: car_00 car_05 
;  curb_1: car_02 car_01 
;  curb_2: car_04 car_03 
;  curb_3: car_06
; =========== /GOAL =========== 
*/
void init()
{
	at_curb[car_00] = 1;
	at_curb_num[car_00][curb_0] = 1;
	behind_car[car_01][car_00] = 1;
	car_clear[car_01] = 1;

	at_curb[car_02] = 1;
	at_curb_num[car_02][curb_1] = 1;
	behind_car[car_03][car_02] = 1;
	car_clear[car_03] = 1;

	at_curb[car_04] = 1;
	at_curb_num[car_04][curb_2] = 1;
	behind_car[car_05][car_04] = 1;
	car_clear[car_05] = 1;

	at_curb[car_06] = 1;
	at_curb_num[car_06][curb_3] = 1;
	car_clear[car_06] = 1;
}

int cnt = 0;

int goal()
{
	int correct = 
		(at_curb_num[car_00][curb_0] == 1) +
		(behind_car[car_05][car_00] == 1) + 
		(at_curb_num[car_02][curb_1] == 1) + 
		(behind_car[car_01][car_02] == 1) + 
		(at_curb_num[car_04][curb_3] == 1) + 
		(behind_car[car_03][car_04] == 1) + 
		(at_curb_num[car_06][curb_3] == 1); 
	if (cnt % 1000 == 0)
        printf("%d\n", correct);
    
    cnt++;
	return (correct == 7);
}

void move_curb_to_curb(int car, int curbsrc, int curbdest)
{
	if (!car_clear[car]) return;
	if (!curb_clear[curbdest]) return;
	if (!at_curb_num[car][curbsrc]) return;

	curb_clear[curbdest] = 0;
	curb_clear[curbsrc] = 1;
	at_curb_num[car][curbdest] = 1;
	at_curb_num[car][curbsrc] = 0;
}

void move_curb_to_car(int car, int curbsrc, int cardest)
{
	if (!car_clear[car]) return;
	if (!car_clear[cardest]) return;
	if (!at_curb_num[car][curbsrc]) return;
	if (!at_curb[cardest]) return;

	car_clear[cardest] = 0;
	curb_clear[curbsrc] = 1;
	behind_car[car][cardest] = 1;
	at_curb_num[car][curbsrc] = 0;
	at_curb[car] = 0;
}

void move_car_to_curb(int car, int carsrc, int curbdest)
{
	if (!car_clear[car]) return;
	if (!curb_clear[curbdest]) return;
	if (!behind_car[car][carsrc]) return;

	curb_clear[curbdest] = 0;
	car_clear[carsrc] = 1;
	at_curb_num[car][curbdest] = 1;
	behind_car[car][carsrc] = 0;
	at_curb[car] = 1;
}


void move_car_to_car(int car, int carsrc, int cardest)
{
	if(!car_clear[car]) return;
	if(!car_clear[cardest]) return;
	if(!behind_car[car][carsrc]) return;
	if(!at_curb[cardest]) return;

	car_clear[cardest] = 0;
	car_clear[carsrc] = 1;
	behind_car[car][cardest] = 1;
	behind_car[car][carsrc] = 0;
}
int main(int argc, const char * argv[]) {

	init();
	int actions = 0;
	while(!goal() && actions < 5){ //while !goal() and actions < 5
		int choice = klee_range(0,numOfActions,"choice");
		//klee_assume ()
		if (choice == 0) {
			int car  = klee_range(0,numOfcars,"car");
			int curbsrc  = klee_range(0,numOfcurbs,"curbsrc");
			int curbdest  = klee_range(0,numOfcurbs,"curbdest");
			move_curb_to_curb(car,curbsrc,curbdest);
		} else if (choice == 1) {
			int car  = klee_range(0,numOfcars,"car");
			int curbsrc  = klee_range(0,numOfcurbs,"curbsrc");
			int cardest  = klee_range(0,numOfcars,"cardest");
			move_curb_to_car(car,curbsrc,cardest);
		}else if (choice == 2){
			int car  = klee_range(0,numOfcars,"car");
			int carsrc  = klee_range(0,numOfcars,"carsrc");
			int curbdest  = klee_range(0,numOfcurbs,"curbdest");
			move_car_to_curb(car,carsrc,curbdest);
		}else {
			int car  = klee_range(0,numOfcars,"car");
			int carsrc  = klee_range(0,numOfcars,"carsrc");
			int cardest  = klee_range(0,numOfcars,"cardest");
			move_car_to_car(car,carsrc,cardest);
		}
		actions++;
	}
	if (goal())
		klee_assert(0); //error signal meaning solution found
    return 0;
}

