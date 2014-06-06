#include <iostream>
#include <cstdlib>
#include <cmath>
#include "mem.hpp"
#define PI 3.1415926
int cal_dct(double ***dctm,double ***dctmT,int n)
{
	get_mem2D<double>(dctm,n,n);
	get_mem2D<double>(dctmT,n,n);
	double coe = sqrt(2.0/n);
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
				(*dctm)[r][c] = coe / (r==0?sqrt(2):1) * cos(PI * (2 * c + 1) * r / (2 * n));
				(*dctmT)[c][r]=(*dctm)[r][c];
		}
	}
	return 0;
}
