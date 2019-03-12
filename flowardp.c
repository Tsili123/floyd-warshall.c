/* 3Á ≈Ò„·Ûﬂ· ¡—«” ‘”…À…÷ŸÕ«” ¡Ã 1115201700170 */ 

//Libraries
#include <stdio.h>
#include <stdlib.h>//malloc,free
#include <limits.h>//representing infinity
#define INF INT_MAX
#include "header.h"//Header file for fuction declaration
#define PATH 1

int **make_array(int nodes)//Make 2-D dynamic array 
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



// Solves the all-pairs shortest path problem using Floyd Warshall algorithm [Dynamic programming]
void solve (int nodes,int **graph) 
{ 
	
    /* dist[][] will be the output matrix that will finally have the shortest  
      distances between every pair of vertices */
      
    int **dist,**path,i, j, k;
	dist=make_array(nodes);
	#ifdef PATH
	/* path[][] will be the output matrix that will finally have the node's of the shortest  
      path between every pair of vertices */
  	path=make_array(nodes);
    #endif

	/* Using infinity (INT_MAX) to represent no direct path between a pair of vertices*/
     
    for (i = 0; i < nodes; i++) 
    {
        for (j = 0; j < nodes; j++) 
        {
            
           if(graph[i][j]==-1)
           		graph[i][j]=INF;
        
    	}
    }  
       
    /* Initialize the solution matrix same as input graph matrix.  
       The initial values of shortest distances are based 
       on shortest paths considering no intermediate vertex.*/
       
    for (i = 0; i < nodes; i++) 
    {
        for (j = 0; j < nodes; j++) 
        {
            dist[i][j] = graph[i][j]; 
            
            #ifdef PATH
            if(dist[i][j]!=INF)
            	path[i][j]=i;//path will be initialized with source nodes
            
           	#endif
           
        
    	}
    }
  	
     /* Add all nodes one by one to the set of intermediate nodes. 
      --> Before start of an iteration, we have shortest distances between all 
      pairs of vertices such that the shortest distances consider only the 
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices. 
      --> After the end of an iteration, vertex no. k is added to the set of 
      intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < nodes  ; k++) 
    { 
                	
        // Pick all vertices as source one by one 
        for (i = 0; i < nodes; i++) 
        { 
            // Pick all vertices as destination for the 
            // above picked source 
            
            for (j = 0; j < nodes; j++) 
            { 
                // If vertex k is on the shortest path from 
                // i to j, then update the value of dist[i][j] 
                	
		   				if ( dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]  )
		   				{
		   					//Also, the value of INF can be taken as INT_MAX from limits.h to make sure that we handle maximum possible value. 
							//When we take INF as INT_MAX, the if condition in the above program is designed to avoid arithmetic overflow.
 							dist[i][j] = dist[i][k] + dist[k][j];//Floyd-Warshall algorithm:intermediate node -> shorter path
 							//I could have also used previous min fuction to store distances and also using -1 insted of infinity
 							//Because paths weren't printed correctly i choosed this solution
 							#ifdef PATH
 							path[i][j] = path[k][j];//I store the predecessor information in a separate 2D matrix.
 							#endif
       					}
   	 		} 
		}
	}
	
	printSolutionpath(nodes,dist,path);//Print distances and paths
	
	free_array(nodes,dist);
//	#ifdef PATH
	free_array(nodes,path);
//	#endif
}


void  printSolutionpath(int nodes,int **dist,int **path)
{
	int i,j;
	for (i = 1;  i < nodes ;  i++)
    {
    	for (j = 0;  j < i;  j++)
        {
        	if(dist[i][j]==INF)//read down triangle of distance's and path's matrix
        		printf ("From node %d to node %d: There is no path\n",i,j);
        	else
            	printf ("From node %d to node %d: Length of shortest path is %d\n",i,j,dist[i][j]);
            #ifdef PATH	
            if( dist[i][j]!=INF )//If there is path print it
        	{
        	
        		printf("Shortest path is : ");
        		printPath(i,j,path);
        		printf(" -> %2d\n",j);//Print last node of the path 
        	} 
        	#endif
        } 
        printf("\n"); //Change line for every source node
	}
}



void printPath(int i,int j,int **path)//Print paths using wikipedia's reconstructing algorithm
{
	int counter=0;
	
	for(;i!=j;i=path[j][i])//j and i variables are reversed because of a malfuction of dynamic allocated array
	{
		counter++;
		if(counter==1)//Case of first node on the path 
			printf("%2d",i);
		else
			printf(" -> %2d",i);//Print every other node
	}
}



