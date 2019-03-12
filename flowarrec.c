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

int **make_array(int nodes)
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

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm [Recursive  programming]
void solve(int nodes,int **graph)
{
	int i, j, **dist;
	/* dist[][] will be the output matrix that will finally have the shortest  
      distances between every pair of vertices */
	dist=make_array(nodes);  
	for(i=1;i<nodes;i++)//Calling recursive fuction for every pair of vertices(No need of 2 directions since the graph is undirected)
	{
		for(j=0;j<i;j++)
		{
			dist[i][j]=recursion(i,j,nodes-1,graph);//N-1 node parameter required  
			//Also graph matrix that contains node's edges is inserted in recursive call 
		}
	}
	printSolution(nodes,dist);//Print result
	
	free_array(nodes,dist);//Freeing memory
}


int recursion(int i,int j,int k,int **p)
{
	if(k<0)//Base cases
	{	
		if(p[i][j]==-1)//It means that 2 nodes are not directly connected
			return -1;
		else
			return p[i][j];//Cij , basically means that 2 nodes are directly connected
	}
	else 
	{	
			return min(recursion(i,j,k-1,p),recursion(i,k,k-1,p),recursion(k,j,k-1,p));
			//Simple recursive implementation of the equation tht is given 
			//p parameter is used for carrying edge's value with pointer
	}
		
}

void  printSolution(int nodes,int **dist)
{
	int i,j;
	for (i = 1;  i < nodes ;  i++)//read down triangle of distance's matrix
    {
    	for (j = 0;  j < i;  j++)//if dist[i][j] value remains -1 after solve then it means that there is no path to j node destination from source i
        {
        	if(dist[i][j]==-1)//if dist[i][j] value remains -1 after solve then it means that there is no path to j node destination from source i
        		printf ("From node %d to node %d: There is no path\n",i,j);
        	else//Normal printing of distance between 2 nodes
            	printf ("From node %d to node %d: Length of shortest path is %d\n",i,j,dist[i][j]);
    
            	
        } 
        printf("\n"); //Change line for every source node
	}
}



