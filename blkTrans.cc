#include <iostream>
#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include "dct.hpp"
#include "mem.hpp"

using namespace std;
double **dctmtxD;
double **dctmtxDT;
int **dctmtxI;
int DCT_SIZE=8;
int main(int argc, const char *argv[])
{
	cal_dct(&dctmtxD,&dctmtxDT,DCT_SIZE);
	//print(dctmtxD,DCT_SIZE); puts("==========\n"); print(dctmtxDT,DCT_SIZE);

	cv::Mat img;
	if(argc != 2)
	{
		return -1;
	}

	img = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

	// Get the basename
	char fn[256];
	strcpy(fn,argv[1]);
	*strrchr(fn,'.')=0;

	if(img.data==NULL)
	{
		puts("Error read image!");
		return -1;
	}

	//print_mat(dctmtxD,DCT_SIZE);

	int blkr=img.rows/DCT_SIZE,blkc=img.cols/DCT_SIZE;
	//cout<<img.rows<<" "<<img.cols<<endl; cout<<blkr<<" "<<blkc<<endl;

	// DCT results for each block
	double ****dct_res;
	get_mem4D<double>(&dct_res,blkr,blkc,DCT_SIZE,DCT_SIZE);

	// p is a pointer to dct_res elements.
	double **p,**temp;
	get_mem2D<double>(&temp,DCT_SIZE,DCT_SIZE);

	// DCT
	for (int r = 0; r < blkr; r++)
	{
		for (int c = 0; c < blkc; c++)
		{
			int Dh = r*DCT_SIZE , Dw = c*DCT_SIZE;
			// F = Df
			p = dct_res[r][c];
			for (int h = 0; h < DCT_SIZE; h++)
			{
				for (int w = 0; w < DCT_SIZE; w++)
				{
					temp[h][w] = 0;
					for (int k = 0; k < DCT_SIZE; k++)
					{
						temp[h][w]+=dctmtxD[h][k]*(double)img.at<uchar>(Dh+k,Dw+w);
					}
				}
			}
			// F = DfD'
			for (int h = 0; h < DCT_SIZE; h++)
			{
				for (int w = 0; w < DCT_SIZE; w++)
				{
					for (int k = 0; k < DCT_SIZE; k++)
					{
						p[h][w]+=temp[h][k]*dctmtxDT[k][w];
					}
				}
			}
		}
	}

	// Get a copy of img.
	cv::Mat img_res;
	img.copyTo(img_res);

	// Inverse DCT with ZigZag scan.
	for (int r = 0; r < blkr; r++)
	{
		for (int c = 0; c < blkc; c++)
		{
			int Dh = r*DCT_SIZE , Dw = c*DCT_SIZE;
			// f = D'F
			p = dct_res[r][c];
			// A simpler ZigZag scan.
			for (int h = 0; h < DCT_SIZE; h++)
			{
				for (int w = 0; w < DCT_SIZE; w++)
				{
					if(h+w>DCT_SIZE)p[h][w]=0;
				}
			}
			for (int h = 0; h < DCT_SIZE; h++)
			{
				for (int w = 0; w < DCT_SIZE; w++)
				{
					temp[h][w] = 0;
					for (int k = 0; k < DCT_SIZE; k++)
					{
						temp[h][w] += dctmtxDT[h][k]*p[k][w];
					}
				}
			}

			// F = D'fD
			for (int h = 0; h < DCT_SIZE; h++)
			{
				for (int w = 0; w < DCT_SIZE; w++)
				{
					for (int k = 0; k < DCT_SIZE; k++)
					{
						p[h][w] += temp[h][k]*dctmtxD[k][w];
					}
					img_res.at<uchar>(Dh+h,Dw+w)=(uchar)p[h][w];
				}
			}
		}
	}

	char res_fn[256];
	strcpy(res_fn,fn);
	strcat(res_fn,"_dct_rec.bmp");
	imwrite(res_fn,img_res);

	release_mem4D<double>(&dct_res,blkr,blkc,DCT_SIZE);
	release_mem2D<double>(&temp,DCT_SIZE);
	return 0;
}
