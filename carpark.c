
#include <math.h>
#include <klee/klee.h>

#define numOfActions 4
#define numOfCars 6
#define numOfCurbs 5

#define car0 0
#define car1 1
#define car2 2
#define car3 3
#define car4 4
#define car5 5

#define curb0 0
#define curb1 1
#define curb2 2
#define curb3 3
#define curb4 4

int carat[6];
int curb_clear[5];
int car_clear[6];


int goal ()
{
	if (carat[car0] == curb0 &&
		carat[car5] == car0 &&
		carat[car1] == curb1 &&
		carat[car2] == curb2 &&
		carat[car3] == curb3 &&
		carat[car4] == curb4)
		return 1;
	return 0;
}

void init()
{
	// Note the 3 global arrays are initialized here
	curb_clear[curb4] = 1;

	car_clear[car0] = 1;
	carat[car0] = curb3;
	curb_clear[curb3] = 0;
	
	car_clear[car5] = 1;
	carat[car5] = curb2;
	curb_clear[curb2] = 0;
	car_clear[car1] = 1;
	carat[car1] = car4;
	car_clear[car4] = 0;
	carat[car4] = curb1;
	curb_clear[curb1] = 0;
	car_clear[car2] = 1;
	carat[car2] = car3;
	car_clear[car3] = 0;
	carat[car3] = curb0;
	curb_clear[curb0] = 0;
}


void move_curb_to_curb(int car,int curbsrc, int curbdest)
{
	klee_assume(curbsrc != curbdest);
	klee_assume(curb_clear[curbsrc] == 0);
	klee_assume(curb_clear[curbdest] == 1);
	klee_assume(carat[car] == curbsrc);
	carat[car] = curbdest;
	curb_clear[curbsrc] = 1;
	curb_clear[curbdest] = 0;
}

void move_curb_to_car(int car,int curbsrc, int cardest)
{
	klee_assume(car != cardest);
	klee_assume(curb_clear[curbsrc] == 0);
	klee_assume(car_clear[cardest] == 1);
	klee_assume(carat[car] == curbsrc);
	carat[car] = cardest;
	curb_clear[curbsrc] = 1;
	car_clear[cardest] = 0;
}

void move_car_to_curb(int car,int carsrc, int curbdest)
{
	klee_assume(carsrc != car);
	klee_assume(car_clear[carsrc] == 0);
	klee_assume(curb_clear[curbdest] == 1);
	klee_assume(carat[car] == carsrc);
	carat[car] = curbdest;
	car_clear[carsrc] = 1;
	curb_clear[curbdest] = 0;
}

void move_car_to_car(int car,int carsrc, int cardest)
{
	klee_assume(carsrc != cardest);
	klee_assume(car_clear[carsrc] == 0);
	klee_assume(car_clear[cardest] == 1);
	klee_assume(carat[car] == carsrc);
	carat[car] = cardest;
	car_clear[carsrc] = 1;
	car_clear[cardest] = 0;
}




int main(int argc, const char * argv[]) {

	init();

	while(!goal()){
		int choice = klee_range(0,numOfActions+1,"choice");
		//klee_assume ()
		if (choice == 0) {
			int car  = klee_range(0,numOfCars+1,"car");
			int curbsrc  = klee_range(0,numOfCurbs+1,"curbsrc");
			int curbdest  = klee_range(0,numOfCurbs+1,"curbdest");
			move_curb_to_curb(car,curbsrc,curbdest);
		} else if (choice == 2) {
			int car  = klee_range(0,numOfCars+1,"car");
			int curbsrc  = klee_range(0,numOfCurbs+1,"curbsrc");
			int cardest  = klee_range(0,numOfCars+1,"cardest");
			move_curb_to_car(car,curbsrc,cardest);
		}else if (choice == 2){
			int car  = klee_range(0,numOfCars+1,"car");
			int carsrc  = klee_range(0,numOfCars+1,"carsrc");
			int curbdest  = klee_range(0,numOfCurbs+1,"curbdest");
			move_car_to_curb(car,carsrc,curbdest);
		}else {
			int car  = klee_range(0,numOfCars+1,"car");
			int carsrc  = klee_range(0,numOfCars+1,"carsrc");
			int cardest  = klee_range(0,numOfCars+1,"cardest");
			move_car_to_car(car,carsrc,cardest);
		}
	}
	
    return 0;
}
