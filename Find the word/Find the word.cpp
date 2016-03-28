# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <iostream>

# define  MAX 100

char m[MAX][MAX];
char p[20];
char percorso[20];

void Loading(int x, int y);
void Check(int rig, int col);
bool Find(int rig, int col, int k);
void Print();

FILE *fin,*fout;
int main()
{
	fin=fopen("Input.txt","r");
	fout=fopen("Output.txt","w");
	
	int r,c;

	//Loading rows and columns
	fscanf(fin,"%d",&r);
	fscanf(fin,"%d",&c);

	//Loading word to find
	fscanf(fin,"%s",p);
	
	Loading(r,c);
	Check(r,c);
		
	return 0;	
}

void Loading(int x, int y)
{
    int i, j=0;
    for(i=0;i<x;i++)
    {
    	fscanf(fin,"%c",&m[i][j]);
        for(j=0;j<y;j++)
        {
            fscanf(fin," %c",&m[i][j]);
            //printf("%c",m[i][j]);
        }
        //printf("\n");
    }
    return;
}

void Check(int rig, int col)
{
	int i,j,k;
	for(i=0;i<rig;i++)	
	    for(j=0;j<col;j++)
	        if(m[i][j]==p[0])
	        {
                //printf("Find the letter: %c in position %d %d \n",p[0],i,j);
	            if (Find(i,j,k=1))
		        Print();
	        }
	fprintf(fout,"ABSENT");
}

bool Find(int rig, int col, int k)
{
    if(k==(strlen(p))){
        percorso[k-1]='\0';
		return true;
    }
    if(p[k]==m[rig][col+1])
    {
       	//printf("In position %d %d find the letter: %c  \n",rig,col+1,p[k]);
    	if(Find(rig,col+1,k+1))
    	{ 
	        //printf("r: %d, col: %d %c=%c\n",rig,col,p[k],m[rig][col+1]);
	        //printf("R");
	        percorso[k-1]='R';
	        return true;
	    }
    }
    if(p[k]==m[rig+1][col])
    {
       	//printf("In position %d %d find the letter: %c  \n",rig+1,col,p[k]);
    	if(Find(rig+1,col,k+1))
    	{
    	    //printf("POSIZIONE rig: %d, col: %d %c=%c\n",rig,col,p[k],m[rig+1][col]);
    	    //printf("B");
    	    percorso[k-1]='B';
    	    return true;
        }
    }
    else
        return false;
}
	
void Print()
{

    fprintf(fout,"%s",percorso);

    exit(EXIT_SUCCESS);
}        







