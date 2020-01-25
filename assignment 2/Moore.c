#include <stdio.h>
#include <math.h>

#define TRUE (1==1)
#define FALSE (!TRUE)

#define EPS 1e-10 //.0000000001

int checkEqual(double a, double b); // Determines if two values are "equal"
double calcTotal(unsigned int numStudents, double hardwareFactor, double yearsWaited); //calculates total time needed to grade

int main(){
	unsigned int numCases, curCase, numStudents;
	double hardwareFactor, target, lowIndex, highIndex;
	
	//gets number of inputs for loop
	scanf("%d", &numCases);
	
	for (curCase = 1; curCase <= numCases; curCase++){//loop cases number of times
		scanf("%u", &numStudents);
		scanf("%lf", &hardwareFactor);
		//get user input
		
		//init range
		lowIndex = 0;
		highIndex = 1;
		
		//increase the range while the function is decreasing
		while(calcTotal(numStudents, hardwareFactor, highIndex) < calcTotal(numStudents, hardwareFactor, lowIndex)){
			highIndex = highIndex * 2;
		}

		//once more for good measure
		highIndex = highIndex * 2;
		
		while(!checkEqual(lowIndex, highIndex)){
			//first, split the range into 3 parts
			double midIndex1 = lowIndex + (highIndex - lowIndex) / 3;
			double midIndex2 = highIndex - (highIndex - lowIndex) / 3;

			//calculate the areas at the midindexs
			double time1 = calcTotal(numStudents, hardwareFactor, midIndex1);
			double time2 = calcTotal(numStudents, hardwareFactor, midIndex2);
			
			if (time1 < time2){
				/* we can eliminate the final third of the range
				because f(mid1) < f(mid2) and all values 
				after mid 2 will be higher */
				highIndex = midIndex2;
			} else {
				/* we can eliminate the first third of the range
				because f(mid2) < f(mid1) and all values 
				before mid 1 will be higher */
				lowIndex = midIndex1;
			}
			
		}
		
		//print the total time spent
		printf("%.6lf\n", calcTotal(numStudents, hardwareFactor, (lowIndex+highIndex) /2));
		
		
		
	}
	return 0;
}

int checkEqual(double a, double b)
{
    double diff = fabs(a - b);
    // return (diff < EPS);
    if (diff < EPS){ //if diff < .0000000001
        //absolute error passed
		return TRUE;
	}
	double max = (a > b) ? a:b;
	if (max * EPS > diff){//relatively small difference when compared to value
		//relative passed
		return TRUE;
	}

	//non-equal
	return FALSE;
}

double calcTotal(unsigned int numStudents, double hardwareFactor, double yearsWaited){
	//this is the given equation solved using the math functions
	return yearsWaited + (numStudents / pow(hardwareFactor, sqrt(yearsWaited)));
}