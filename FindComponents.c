/****************************************************************************************************************************************
*	File: FindComponents.c
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa5
*****************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[])
{
	//Check for appropriate number of arguments. 
	if(argc != 3)
	{
		fprintf(stderr, "FindComponents Error: incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}

	//Open up input and output files.
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");

	//Check to see if the files were successfully opened.
	if(in == NULL)
	{
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(out == NULL)
	{
		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	int n;
	int a;
	int b;
	int i;
	int ssc = 0;
	List S = newList();
	Graph G = NULL;
	Graph T = NULL;

	fscanf(in, "%d", &n);
	G = newGraph(n);

	for(i = 1; i < n + 1; i++)
	{
		append(S, i);
	}

	//Generate edges from the in file until the line "0 0" is found
	while(!feof(in))
	{
		fscanf(in, "%d", &a);
		fscanf(in, "%d", &b);
		if(a == 0 && b == 0)
		{
			break;
		}
		addArc(G, a, b);
	}

	//Print out the resulting graph
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);

	//Run DFS on G, find the transpose of T, then run DFS again on the resulting transpose
	DFS(G, S);
	T = transpose(G);
	DFS(T, S);


	//Find the number of SCCs
	moveFront(S);
	while(index(S) != -1)
	{
		if(getParent(T, get(S)) == NIL)
		{
			ssc++;
		}
		moveNext(S);
	}


	//Store the SCCs in an array of Lists, keeping them in topologically sorted order
	List *SCC = calloc(ssc, sizeof(List));

	moveFront(S);
	for(i = 0; i < ssc; i++)
	{
		SCC[(ssc - 1) - i] = newList();
		append(SCC[(ssc - 1) - i], get(S));
		moveNext(S);
		while(index(S) != -1)
		{
			if(getParent(T, get(S)) == NIL)
			{
				break;
			}
			append(SCC[(ssc - 1) - i], get(S));
			moveNext(S);
		}
	}

	//Print out the SCCs in topologically sorted order
	fprintf(out, "\nG contains %d strongly connected components:\n", ssc);
	for(i = 0; i < ssc; i++)
	{
		fprintf(out, "Component %d: ", i + 1);
		printList(out, SCC[i]);
		fprintf(out, "\n");
	}

	for(i = 0; i < ssc; i++)
	{
		freeList(&SCC[i]);
		free(SCC[i]);
	}
	free(SCC);

	freeGraph(&G);
	freeGraph(&T);
	freeList(&S);

	//Close input and output files.
	fclose(in);
	fclose(out);

	return (0);
}