#include "mem.hpp"
#include <iostream>


int print_mat(double **mtx,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int s = 0; s < n; s++)
		{
			std::cout<<mtx[i][s]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
	return 0;
}
int init_mat(double **mtx,int n,int val)
{
	for (int i = 0; i < n; i++)
	{
		for (int s = 0; s < n; s++)
		{
			mtx[i][s]=val;
		}
	}
	return 0;
}
