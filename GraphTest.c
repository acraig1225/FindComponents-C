/****************************************************************************************************************************************
*	File: GraphTest.c
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa5
*****************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "List.h"
#include "Graph.h"

//Returns a random number within a given range
int random(int lowerBound, int upperBound)
{
	return (rand() % (upperBound - lowerBound + 1) + lowerBound);
}

int main()
{
	srand(time(NULL));			//Needed to generate different random number during each execution
	int n = 10;
	int i;
	int p;
	int r = random(1, 20);		//range of how many edges to be generated
	int num1;
	int num2;
	int ran1;
	int temp;
	int ssc;
	Graph G = newGraph(n);
	Graph T = NULL;
	List L = newList();
	List S = newList();

	//Generate a random number of randomly generated edges within the bounds of the Graph
	for(i = 1; i < r; i++)
	{
		num1 = random(1, n);
		num2 = random(1, n);
		addArc(G, num1, num2);
	}

	for(i = 1; i < n + 1; i++)
	{
		append(S, i);
	}

	//Print the resulting Graph
	printf("Graph G has %d vertices and %d edges\n", getOrder(G), getSize(G));
	printGraph(stdout, G);
	printf("\n");
	
	printf("\nDFS result 1:\n");
	DFS(G, S);
	printf("x:  d  f  p\n");
	for(i = 1; i < n + 1; i++)
	{
		printf("%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
	}

	T = transpose(G);
	printf("\nThe tranpose of G has %d vertices and %d edges\n", getOrder(T), getSize(T));
	printGraph(stdout, T);
	printf("\n");

	printf("\nDFS result 2:\n");
	DFS(T, S);
	printf("x:  d  f  p\n");
	for(i = 1; i < n + 1; i++)
	{
		printf("%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
	}

	moveFront(S);
	while(index(S) != -1)
	{
		if(getParent(T, get(S)) == NIL)
		{
			ssc++;
		}
		moveNext(S);
	}
	printf("\nG contains %d strongly connected components:\n", ssc);

	
	//Pick a random vertex and print parents starting at the random vertex until NIL
	ran1 = random(1, n);
	printf("\nParent Check:\n");
	printf("Picking a random vertex (%d) in the graph and printing parents until NIL.\n", ran1);
	p = getParent(G, ran1);
	printf("The parent of %d is %d\n", ran1, p);
	if(p != NIL)
	{
		while(getParent(G, p) != NIL)
		{
			temp = p;
			p = getParent(G, p);
			printf("The parent of %d is %d\n", temp, p);
		}
	}

	//Make graph Null and print out message if unsuccessful
	makeNull(G);
	if(getSize(G) != 0)
	{
		printf("makeNull unsucessful\n");
	}


	freeList(&L);
	freeList(&S);
	freeGraph(&G);
	freeGraph(&T);

	return (0);
}