/****************************************************************************************************************************************
*	File: Graph.c
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa5
*****************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj
{
	List *adj;
	char *color;
	int *parent;
	int	*discovery;
	int *finish;
	int order;
	int size;
} GraphObj;

//Constructors-Destructors***************************************************************************************************************
//Description: Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges.
Graph newGraph(int n)
{
	int i;
	Graph G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;

	G->adj = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(char*));
	G->parent = calloc(n + 1, sizeof(int));
	G->discovery = calloc(n + 1, sizeof(int));
	G->finish = calloc(n + 1, sizeof(int));
	for(i = 1; i < n + 1; i++)
	{
		G->adj[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->discovery[i] = UNDEF;
		G->finish[i] = UNDEF;
	}

	return (G);
}							

//Description: Frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG)
{
	if(*pG != NULL && pG != NULL)
	{
		int i;

		free((*pG)->adj[0]);
		for(i = 1; i < getOrder(*pG) + 1; i++)
		{
			freeList(&(*pG)->adj[i]);	
			free((*pG)->adj[i]);
		}
		free((*pG)->adj);
		free((*pG)->color);
		free((*pG)->discovery);
		free((*pG)->finish);
		free((*pG)->parent);
		free(*pG);
		*pG = NULL;
	}
}

void visit(Graph G, int x, List* L, int* time)
{
	(*time)++;
	G->discovery[x] = (*time);
	G->color[x] = 'g';
	int y;
	moveFront(G->adj[x]);
	while(index(G->adj[x]) != -1)
	{
		y = get(G->adj[x]);
		if(G->color[y] == 'w')
		{
			G->parent[y] = x;
			visit(G, y, &(*L), &(*time));
		}
		moveNext(G->adj[x]);
	}
	G->color[x] = 'b';
	(*time)++;
	G->finish[x] = (*time);
	prepend((*L), x);
}

//Access Functions***********************************************************************************************************************
//Description: Returns the order field of a given Graph.
int getOrder(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	return(G->order);
}	

//Description: Returns the size field of a given Graph.						
int getSize(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	return(G->size);
}						

//Description: Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not yet been called.
//Precondition: 1 <= u <= getOrder(G)												
int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getParent() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	return (G->parent[u]);
}

//Description: Returns the discovery time of vertex u.
//Precondition: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getDiscover() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	return (G->discovery[u]);
}

//Description: Returns the finsih time of vertex u.
//Precondition: 1<=u<=n=getOrder(G)		 				
int getFinish(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getFinish() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getFinish() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	return (G->finish[u]);
}					

//Manipulation Procedures****************************************************************************************************************
//Description: Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(getSize(G) > 0)
	{
		int i;
		for(i = 1; i < getOrder(G) + 1; i++)
		{
			clear(G->adj[i]);
			G->color[i] = 'w';
			G->parent[i] = NIL;
			G->discovery[i] = UNDEF;
			G->finish[i] = UNDEF;
		}
		G->size = 0;
	}
}

//Description: Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
//Precondition: 1 <= u <= getOrder(G) & 1 <= v <= getOrder(G)							
void addEdge(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if(v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	//insert v into adj[u]
	if(length(G->adj[u]) == 0)
	{
		append(G->adj[u], v);
	}
	else
	{
		moveFront(G->adj[u]);
		while(index(G->adj[u]) != -1 &&  get(G->adj[u]) < v)  //look to see if entry already exists
		{
			moveNext(G->adj[u]);		
		}

		if(index(G->adj[u]) == -1)
		{
			append(G->adj[u], v);
		}
		else if(get(G->adj[u]) != v)
		{
			insertBefore(G->adj[u], v);
		}
	}

	//insert u into adj[v]
	if(length(G->adj[v]) == 0)
	{
		append(G->adj[v], u);
	}
	else
	{
		moveFront(G->adj[v]);
		while(index(G->adj[v]) != -1 &&  get(G->adj[v]) < u)  //look to see if entry already exists
		{
			moveNext(G->adj[v]);		
		}

		if(index(G->adj[v]) == -1)
		{
			append(G->adj[v], u);
		}
		else if(get(G->adj[v]) != u)
		{
			insertBefore(G->adj[v], u);
		}
	}
	G->size++;
}			 

//Description: Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
//Precondition: 1 <= u <= getOrder(G) & 1 <= v <= getOrder(G)												
void addArc(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if(v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	//insert v into adj[u]
	if(length(G->adj[u]) == 0)
	{
		append(G->adj[u], v);
	}
	else
	{
		moveFront(G->adj[u]);
		while(index(G->adj[u]) != -1 &&  get(G->adj[u]) < v)  //look to see if entry already exists
		{
			moveNext(G->adj[u]);		
		}

		if(index(G->adj[u]) == -1)
		{
			append(G->adj[u], v);
		}
		else if(get(G->adj[u]) != v)
		{
			insertBefore(G->adj[u], v);
		}
	}
	G->size++;
}			

//Description: Runs the DFS algorithm on the Graph G with List s, setting the color, parent, discovery time, and finish time fields of G accordingly.
//Precondition: length(S)==getOrder(G)
void DFS(Graph G, List s)
{
	if(G == NULL)
	{
		printf("Graph Error: calling DFS() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(s) != getOrder(G))
	{
		printf("Graph Error: length of s != getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	int i;
	int x;
	int time = 0;
	List temp = newList();

	for(i = 1; i < getOrder(G) + 1; i++)
	{
		G->color[i] = 'w';
		G->parent[i] = NIL;
	}

	moveFront(s);
	for(i = 1; i < getOrder(G) + 1; i++)
	{
		x = get(s);
		if(G->color[x] == 'w')
		{
			visit(G, x, &temp, &time);
		}
		moveNext(s);
	}
	
	clear(s);
	moveFront(temp);
	while(index(temp) != -1)
	{
		append(s, get(temp));
		moveNext(temp);
	}

	freeList(&temp);	
}						

//Other Operations***********************************************************************************************************************
//Description: Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling printGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(out == NULL)
	{
		printf("Graph Error: calling printGraph() on NULL FILE reference\n");
		exit(EXIT_FAILURE);
	}
	
	int i;
	for(i = 1; i < getOrder(G) + 1; i++)
	{
		fprintf(out, "%d: ", i);
		if(length(G->adj[i]) != 0)
		{
			moveFront(G->adj[i]);
			while(index(G->adj[i]) != -1)
			{
				fprintf(out, "%d ", get(G->adj[i]));
				moveNext(G->adj[i]);
			}
		}
		fprintf(out, "\n");
	}
}

//Description: Returns a copy of Graph G.
Graph copyGraph(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	Graph nG = newGraph(getOrder(G));
	int i;
	for(i = 1; i < getOrder(G) + 1; i++)
	{
		freeList(&nG->adj[i]);
		nG->adj[i] = copyList(G->adj[i]);
		nG->color[i] = G->color[i];
		nG->parent[i] = G->parent[i];
		nG->discovery[i] = G->discovery[i];
		nG->finish[i] = G->finish[i];
	}
	nG->order = G->order;
	nG->size = G->size;

	return (nG);
}

//Description: Returns a new Graph that is the transpose of G.
Graph transpose(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling transpose() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	Graph T;
	int i;
	int j;

	T = newGraph(getOrder(G));

	for(i = 1; i < getOrder(G) + 1; i++)
	{
		T->parent[i] = G->parent[i];
		T->color[i] = G->color[i];
		T->discovery[i] = G->discovery[i];
		T->finish[i] = G->finish[i];

		for(j = 1; j < getOrder(G) + 1; j++)
		{
			moveFront(G->adj[j]);
			while(index(G->adj[j]) != -1)
			{
				if(get(G->adj[j]) == i)
				{
					addArc(T, i, j);
				}
				moveNext(G->adj[j]);
			}
		}
	}

	return (T);
}

			