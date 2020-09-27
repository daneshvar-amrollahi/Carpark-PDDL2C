#include <math.h>
#include <klee/klee.h>

#define numOfActions 4
#define numOfcars 5
#define numOfcurbs 3

#define car_00 0
#define car_01 1
#define car_02 2
#define car_03 3
#define car_04 4

#define curb_0 0
#define curb_1 1
#define curb_2 2

int at_curb[numOfcars + 1];
int at_curb_num[numOfcars + 1][numOfcurbs + 1];
int behind_car[numOfcars + 1][numOfcars + 1];
int car_clear[numOfcars + 1];
int curb_clear[numOfcurbs + 1];

void init()
{
	at_curb[car_00] = 1;
	at_curb_num[car_00][curb_0] = 1;
	behind_car[car_01][car_00] = 1;
	car_clear[car_01] = 1;
	at_curb[car_02] = 1;
	at_curb_num[car_02][curb_1] = 1;
	car_clear[car_02] = 1;
	at_curb[car_03] = 1;
	at_curb_num[car_03][curb_2] = 1;
	behind_car[car_04][car_03] = 1;
	car_clear[car_04] = 1;
}

int goal()
{
	if(
		at_curb[car_00] == 1 && 
		at_curb_num[car_00][curb_0] == 1 && 
		behind_car[car_04][car_00] == 1 && 
		car_clear[car_04] == 1 && 
		at_curb[car_02] == 1 && 
		at_curb_num[car_02][curb_1] == 1 && 
		behind_car[car_01][car_02] == 1 && 
		car_clear[car_01] == 1 && 
		at_curb[car_03] == 1 && 
		at_curb_num[car_03][curb_2] == 1 && 
		car_clear[car_03] == 1 
	)
		return 1;
	else
		return 0;
}

void move_curb_to_curb(int car, int curbsrc, int curbdest)
{
	if (!car_clear[car]) exit(0);
	if (!curb_clear[curbdest]) exit(0);
	if (!at_curb_num[car][curbsrc]) exit(0);

	curb_clear[curbdest] = 0;
	curb_clear[curbsrc] = 1;
	at_curb_num[car][curbdest] = 1;
	at_curb_num[car][curbsrc] = 0;
}

void move_curb_to_car(int car, int curbsrc, int cardest)
{
	if (!car_clear[car]) exit(0);
	if (!car_clear[cardest]) exit(0);
	if (!at_curb_num[car][curbsrc]) exit(0);
	if (!at_curb[cardest]) exit(0);

	car_clear[cardest] = 0;
	curb_clear[curbsrc] = 1;
	behind_car[car][cardest] = 1;
	at_curb_num[car][curbsrc] = 0;
	at_curb[car] = 0;
}

void move_car_to_curb(int car, int carsrc, int curbdest)
{
	if (!car_clear[car]) exit(0);
	if (!curb_clear[curbdest]) exit(0);
	if (!behind_car[car][carsrc]) exit(0);

	curb_clear[curbdest] = 0;
	car_clear[carsrc] = 1;
	at_curb_num[car][curbdest] = 1;
	behind_car[car][carsrc] = 0;
	at_curb[car] = 1;
}


void move_car_to_car(int car, int carsrc, int cardest)
{
	if(!car_clear[car]) exit(0);
	if(!car_clear[cardest]) exit(0);
	if(!behind_car[car][carsrc]) exit(0);
	if(!at_curb[cardest]) exit(0);

	car_clear[cardest] = 0;
	car_clear[carsrc] = 1;
	behind_car[car][cardest] = 1;
	behind_car[car][carsrc] = 0;
}
int main(int argc, const char * argv[]) {

	init();

	while(!goal()){
		int choice = klee_range(0,numOfActions+1,"choice");
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
	}

	klee_assert(0); //error signal meaning solution found
    return 0;
}

