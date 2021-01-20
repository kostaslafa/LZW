#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define N 288 /* frame dimension  */
#define M 352 /* frame dimension  */

char UncodedData[N*M+1][5];
int output[N*M-1];
char Dictionary[4096][1000];
int current[N][M];
int row[N*M];
int i,j;

int k,l;
int times,pos;
int address;
int at;
int exists;
char str[1000];
char ch[5];
char temp[1000];


// reads raw data from image
// using this image as an example ‘akiyo_cif_0_yuv420.yuv’
void read()
{
	FILE *frame_c;
	if((frame_c=fopen("akiyo_cif_0_yuv420.yuv","rb"))==NULL)
	{
		printf("current frame doesn't exist\n");
		exit(-1);
	}

	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			current[i][j]=fgetc(frame_c);
		}
	}
}

void compress()
{
	strcpy(UncodedData[N*M],"last"); 
//we add the string "last" after the last element
//in order to use it as mark that data have ended 

//conversion of image which is matrix in a single row 
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			row[352*i+j] = current[i][j]; 
		}
	}
//conversion of data from int to char	
	for (i = 0 ; i < N*M ; i++)
	{
	    sprintf(UncodedData[i], "%d", row[i]);
	    
 	}
//initiate the dictionary for positions 0 to 255
	for (i = 0 ; i < 256 ; ++i)
	{
	    sprintf(Dictionary[i], "%d", i);
	}
	
	address = 0; //the address where we write on the output 
	at = 256; // the address where we write on the dictionary 
	times = 0; //keeps how many times a string or an element with its //next exist in the dictionary, set to zero every time that anything //does not exists 
	pos =-1; //keeps the position when an element with its next exist in //dictionary 
	k=0;
	exists = 1; //keeps whenever an element with its next exist or not in dictionary, exists = 0 means exist, exists!= 0 does NOT exist
	strcpy(str,UncodedData[0]); 
	while(k<N*M)
	{
		strcpy(ch,UncodedData[(k+1)]); //we keep the next element
	//check if the next element is the last one
		if(strcmp(ch,"last")==0)
		{
			break;
		}
	//we join the string or the element which is being checked, with the next element with the symbol ‘&’ between them and we check if it’s in the dictionary
		strcpy(temp,str);
		strcat(temp,"&");
		strcat(temp,ch);
		for(l=256;l<at;l++)
		{
			exists = strcmp(temp,Dictionary[l]);
			//check if the string is in the dictionary
			if(exists == 0) 
			{
				strcpy(str, temp);
				pos = l; //we keep the position where a string is in dictionary
				times++;
				k++;
				break;
			}
		}
		// case where a string is not in dictionary
		if(exists != 0)
		{
			if(at<4096) //check if there is empty position in dictionary in order to fill it
			{
				strcpy(Dictionary[at],temp);
				at++;
			}
			//case where an element (not string) with its next is not in dictionary
			if(times==0)
			{
				output[address] = row[k]; //we set as an output the element that we are checking
				address++;

			}
			//case where a string was in dictionary but the string with the next element was not in dictionary
			else
			{
				output[address] = pos;
				address++;
				times = 0;
			}
			strcpy(str,ch); //we keep the next element as this that it will be checked
			k++;
		}
	}
	
	// check if the last element is part of a string that exists in the dictionary
	if(exists == 0)
	{			
		output[address] =	pos;
	}
	else
	{
		output[address] = row[N*M-1]; 
	}	
}

int main()
{
	read();
	compress();
	
	//print the last output
	printf("output[%d] = %d\n",address,output[address]);
	printf("Dictionary[%d] = %s\n",256,Dictionary[256]);	
	
}
