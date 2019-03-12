/* 3Á ≈Ò„·Ûﬂ· ¡—«” ‘”…À…÷ŸÕ«” ¡Ã 1115201700170 */ 

//Libraries
#include <stdio.h>
#include <stdlib.h>//malloc,free
#include <limits.h>//representing infinity
#define INF INT_MAX
#include "header.h"//Header file for fuction declaration
#define PATH 1

int min(int a,int b,int c)
{
	//minimum fuction that handles -1 properly
	if(b==-1||c==-1)
	{
		return a;//if Pi,k,k-1 or Pk,j,k-1 is -1 then return Pi,j,k-1 since there is no shorter path 
	}
	else if (a==-1)//Else return shorter path
		return b+c;
		
	if(a<b+c)//In case of absence of -1 we have normal min fuction
		return a;
	else
		return b+c;
}


int ***make_memo(int nodes)//make 3-D array for recursive memoization
{
	int i,j;
	 int ***array;
	
	// Allocate the 1-D array of pointers
    array = malloc(nodes * sizeof(int **));
    
    // Allocate each row of the array
    for (i = 0;  i < nodes;  i++)
    {
        // Allocate a row of ints for the array
        array[i] = malloc(nodes * sizeof(int*));
        for(j=0; j < nodes; j++)
        {
        	array[i][j] = malloc(nodes * sizeof(int));
        	//A 3-D array is like a lot of squares one above the other
		}
    }

	return array;
}
  
int **make_array(int nodes)//2-Dimensions
{
	int i,j;
	 int **array;
	
	// Allocate the 1-D array of pointers
    array = malloc(nodes * sizeof(int *));
    
    // Allocate each row of the array
    for (i = 0;  i < nodes;  i++)
    {
        // Allocate a row of ints for the array
        array[i] = malloc(nodes * sizeof(int));
    }

	return array;
}

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm [Recursive Memoization programming]
void solve(int nodes,int **graph)
{
	int i, j, **dist,***memo;
	// memo[][][] will be used for remembering same values that occur on recursive fuction
	memo=make_memo(nodes);
	/* dist[][] will be the output matrix that will finally have the shortest  
      distances between every pair of vertices */
	dist=make_array(nodes);  
	for(i=1;i<nodes;i++)
	{
		for(j=0;j<i;j++)//Calling recursive fuction for every pair of vertices(No need of 2 directions since the graph is undirected)
		{
			dist[i][j]=memoization(i,j,nodes-1,graph,memo);//N-1 node parameter required  
		}
	}
	printSolution(nodes,dist);//Print result
	
	free_array(nodes,dist);//Freeing memory
}


int memoization(int i,int j,int k,int **p,int ***m)
{
	if(k<0)//Base case of Pijk = min { Pi,j,k-1, Pi,k,k-1 + Pk,j,k-1 }, if k = 0
		//------------------->	Cij    if  k < 0
{
		if(p[i][j]==-1)
			return -1;//It means that 2 nodes are not directly connected
		else
			return p[i][j];//Cij , basically means that 2 nodes are directly connected
	}
		
	if(m[i][j][k]!= 0 && m[i][j][k]!= -1)//If not base case then we have same values
	{	
		return m[i][j][k];//So we return them instead of doing further recursive calls
	}
	else
	{
		m[i][j][k]=min(memoization(i,j,k-1,p,m),memoization(i,k,k-1,p,m),memoization(k,j,k-1,p,m));//Recursive fuction that expresses the equation
	}//Matrix's values p for edges and m for memoization need to be used for every recursive call.So they are parameters of recursive function
		return m[i][j][k];//We memorize it with 3-D matrix (A specific k for a pair of i,j nodes)
}

void  printSolution(int nodes,int **dist)
{
	int i,j;
	for (i = 1;  i < nodes ;  i++)//read down triangle of distance's matrix
    {
    	for (j = 0;  j < i;  j++)
        {
        	if(dist[i][j]==-1)//if dist[i][j] value remains -1 after solve then it means that there is no path to j node destination from source i
        		printf ("From node %d to node %d: There is no path\n",i,j);
        	else//Normal printing of distance between 2 nodes
            	printf ("From node %d to node %d: Length of shortest path is %d\n",i,j,dist[i][j]);
    
            	
        } 
        printf("\n"); //Change line for every source node
	}
}



