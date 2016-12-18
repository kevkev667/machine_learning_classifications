#include"knn_digits.h"
double euclidean_distance(int a[19][28],int b[19][28])
{
	double sum=0;
	int i,j;
	for(i=0;i<19;i++)
	{
		for(j=0;j<28;j++)
		{
			sum+=pow(a[i][j]-b[i][j],2);
		}
	}
	return sqrt(sum);
}

int predict(DigitBitMapData * curr)
{
	double mindistance=INT_MAX;
	double currdistance;
	int guess=-1;
	int i;
	for(i=0;i<5000;i++)
	{
		currdistance=euclidean_distance(curr->pixels,neighbors[i]->pixels);
		if(currdistance<mindistance)
		{
			mindistance=currdistance;
			guess=neighbors[i]->label;
		}
	}
	return guess;
}

void extract_features(FILE * imagesfd, DigitBitMapData * curr)
{
	int i,j,k;
	char * image_line=NULL;
	size_t image_len=0;
	ssize_t image_read;
	char whitespace;
	int prev;
	int minindex,maxindex;
	int minwidth=28,maxwidth=0;
	int widthsum;
	int num_on_line;
	int num_sets_line;
	int minheight,maxheight,heightsum;
	//strip whitespace
	whitespace=1;
	while(whitespace)
	{
		image_read=getline(&image_line,&image_len,imagesfd);
		for(i=0;i<strlen(image_line);i++)
		{
			if(!isspace(image_line[i]))
			{
				whitespace=0;
				break;
			}
		}
	}
	//populate points grid
	for(i=0;i<19;i++)
	{
		image_read=getline(&image_line,&image_len,imagesfd);
		if(image_read==-1)
		{
			break;
		}

		for(j=0;j<28;j++)
		{
			if(image_line[j]=='+' || image_line[j]=='#')
			{
				curr->pixels[i][j]=1;
			}
			else
			{
				curr->pixels[i][j]=0;
			}
		}
	}
	
}
