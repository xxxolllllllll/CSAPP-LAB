#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 5
void print_mst(int parent[V], int graph[V][V])
{
    printf("edge      weight\n");
    for(int i = 1; i < V; i++)
    {
        printf("%d -- %d   %d\n", i, parent[i], graph[i][parent[i]]);
    }
}
void prim_mst(int graph[V][V])
{
    bool mst_set[V];
    int parent[V];  // mst
    int key[V];
    int number_mst = 0; // number of vertice in mst.
    int min_key = INT_MAX;
    int min_vertice = -1;
    for(int i = 0; i < V; i++)
    {
        mst_set[i] = false; 
        parent[i] = -1; 
        key[i] = INT_MAX;
    }
    key[0] = 0; // vertice 0 is picked first.
    parent[0] = 0;  // vertice 0 is the root of mst.
    while(number_mst < V)
    {
        for(int i = 0; i < V; i++)  // get minimum key value of vertice which not exisit in mst
        {
            if(!mst_set[i] && min_key > key[i])
            {
                min_key = key[i];
                min_vertice = i;
            }
        }
        min_key = INT_MAX;
        mst_set[min_vertice] = true;
        number_mst++;
        // update adj_vertice's key and parent[adj_vertice].
        for(int i = 0; i < V; i++)
        {
            if(graph[min_vertice][i] && (mst_set[i] == false) && graph[min_vertice][i] < key[i])
            {
                key[i] = graph[min_vertice][i];     
                parent[i] = min_vertice;
            }
        }
    }
    print_mst(parent, graph);
}

void main()
{
    int graph[V][V] = { {0, 2, 0, 6, 0},
                        {2, 0, 3, 8, 5},
                        {0, 3, 0, 0, 7},
                        {6, 8, 0, 0, 9},
                        {0, 5, 7, 9, 0}};
    prim_mst(graph);
}
