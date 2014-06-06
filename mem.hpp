#ifndef __AVS_MEM
#define __AVS_MEM
template <typename Type>
int get_mem2D(Type*** (data),int D2,int D1)
{
	*data = new Type* [D2];
	for (int r = 0; r < D2; r++)
	{
		(*data)[r] = new Type [D1];
	}
	return 0;
}

template <typename Type>
int get_mem3D(Type**** data,int D3,int D2,int D1)
{
	*data = new Type** [D3];
	for (int r = 0; r < D3; r++)
	{
		get_mem2D<Type>(&((*data)[r]),D2,D1);
	}
	return 0;
}

template <typename Type>
int get_mem4D(Type***** data,int D4,int D3,int D2,int D1)
{
	*data = new Type*** [D4];
	for (int r = 0; r < D4; r++)
	{
		get_mem3D<Type>(&((*data)[r]),D3,D2,D1);
	}
	return 0;
}

template <typename Type>
int release_mem2D(Type*** data,int D2)
{
	for (int r = 0; r < D2; r++)
	{
		delete  (*data)[r];
	}
	delete *data;
	return 0;
}

template <typename Type>
int release_mem3D(Type**** data,int D3,int D2)
{
	for (int r = 0; r < D3; r++)
	{
		release_mem2D<Type>(&(*data)[r],D2);
	}
	delete *data;
	return 0;
}

template <typename Type>
int release_mem4D(Type***** data,int D4,int D3,int D2)
{
	for (int r = 0; r < D4; r++)
	{
		release_mem3D<Type>(&(*data)[r],D3,D2);
	}
	delete  *data;
	return 0;
}

int print_mat(double **mtx,int n);

int init_mat(double **mtx,int n,int val);

#endif
