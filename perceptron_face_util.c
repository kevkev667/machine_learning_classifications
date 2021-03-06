#include"perceptron_face.h"

int predict()
{
	int i,j,k;
	int guess=-1;
	long long highestactivation=LLONG_MIN;
	long long activations[2]={0};

	for(i=0;i<2;i++)
	{
		activations[i]+=classes[i].bias;
		for(j=0;j<66;j++)
		{
			for(k=0;k<60;k++)
			{
				activations[i]+=classes[i].pixel_weights[j][k]*curr.pixels[j][k];
			}
		}
	}
	for(i=0;i<2;i++)
	{
		if(activations[i]>highestactivation)
		{
			highestactivation=activations[i];
			guess=i;
		}
	}
	return guess;
	
}

void update_weights(int guessed,int correct)
{
	int i,j;
	
	classes[guessed].bias--;
	
	for(i=0;i<66;i++)
	{
		for(j=0;j<60;j++)
		{
			classes[guessed].pixel_weights[i][j]-=curr.pixels[i][j];
		}
	}

	classes[correct].bias++;
	
	for(i=0;i<66;i++)
        {
                for(j=0;j<60;j++)
                {
                        classes[correct].pixel_weights[i][j]+=curr.pixels[i][j];
                }
        }
}

void extract_features(FILE * imagesfd)
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
	for(i=0;i<66;i++)
	{
		image_read=getline(&image_line,&image_len,imagesfd);
		if(image_read==-1)
		{
			break;
		}

		for(j=0;j<60;j++)
		{
			if(image_line[j]=='+' || image_line[j]=='#')
			{
				curr.pixels[i][j]=1;
			}
			else
			{
				curr.pixels[i][j]=0;
			}
		}
	}
	
}

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}
