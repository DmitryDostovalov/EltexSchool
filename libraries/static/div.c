#include"div.h"
#include<math.h>

double my_div(double numerator, double denominator)
{
	double result = 0;
	if(fabs(denominator) >= 1e-10)
	{
		result = numerator / denominator;
	}
	return result;
}
