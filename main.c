/* 3Á ≈Ò„·Ûﬂ· ¡—«” ‘”…À…÷ŸÕ«” ¡Ã 1115201700170 */ 


//Libraries
#include <stdio.h>
#include <stdlib.h>//malloc,free
#include <limits.h>//representing infinity
#define INF INT_MAX
#include "header.h"//Header file for fuction declaration
#define PATH 1


//Graph creation
int **make_graph(int *nodes)
{
	int i,j;
	int **graph;
	
	 scanf("%d\n",nodes);//Read number of nodes
	
	// Allocate the 1-D array of pointers
    graph = malloc(*nodes * sizeof(int *));
    
    // Allocate each row of the array
    for (i = 0;  i < *nodes ;  i++)
    {
        // Allocate a row of ints for the array
        graph[i] = malloc(*nodes* sizeof(int));

    }
    
    for (i = 1;  i < *nodes ;  i++)//Read down triangle of input
    {
    	for (j = 0;  j < i;  j++)
        {
        		scanf("%d",&graph[i][j]);
    	}	
	}
	
   for (i = 0;  i < *nodes ;  i++)//Fill matrix diagonally with zeros
    {
    	for (j = 0;  j < i+1;  j++)
        {
        		if(j==i)
        			graph[i][j]=0;
    	}	
	}
	
	for (i = 1;  i < *nodes ;  i++)//Flip the down triangle (diagonally)
    {
    	for (j = 0;  j < i;  j++)
        {
        	graph[j][i]=graph[i][j];//Copying structure of down triangle to upper triangle
    	}	
	}
	
	
   return graph;//Return pointer to the graph's matrix
}

void free_array(int nodes,int **array)//Free dynamic allocated memory
{
	int i;
    // Free each allocated row
    for ( i = 0;  i < nodes;  i++)
    {
        if (array[i] != NULL)
            free(array[i]);
        array[i] = NULL;//Setting null value for safe deallocation
    }

    // Free the pointer array
    free(array);
}


int main(void)//main function
{
	int *nodes,**graph;//nodes variable will be shared by every source file
	//It is used for number of nodes
	graph = make_graph(nodes);//pointer to graph's matrix
	solve(*nodes,graph);//Calling solve fuction depending which source file we are running
	free_array(*nodes,graph);//free graph's matrix for saving memory

}
