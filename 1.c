#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
struct ListNode{
    int vertice;
    int weight;
    struct ListNode *next;
};
struct Graph{
    int vertice_count;
    struct ListNode **head;
};
struct Edge{
    int source;
    int dest;
    int weight;
    struct Edge *next;
};

struct Edge *create_edge(int source, int dest, int weight)
{
    struct Edge* new_edge = (struct Edge*)malloc(sizeof(struct Edge));
    new_edge->source = source;
    new_edge->dest = dest;
    new_edge->weight = weight;
    new_edge->next = NULL;
    return new_edge;
}

struct Graph *create_graph(int vertice_count)
{
    struct Graph *new_graph = (struct Graph *)malloc(sizeof(struct Graph));
    new_graph->vertice_count = vertice_count;
    new_graph->head = (struct ListNode **)malloc(vertice_count*sizeof(struct ListNode*));
    // init adjList
    for(int i = 0; i < vertice_count; i++)
    {
        new_graph->head[i] = NULL;
    }
    return new_graph;
}

void add_edge(struct Edge *edge, struct Graph *adj)
{
    // add a direct edge from vertice source to dest
    struct ListNode *head = adj->head[edge->source];
    struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->vertice = edge->dest;
    newNode->weight = edge->weight;
    newNode->next = head;   // insert a new node at front of a List
    adj->head[edge->source] =  newNode; // point to  the head node of the List
    // add a direct edge from vertice dest to source
    head = adj->head[edge->dest];
    newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->vertice = edge->source;
    newNode->weight = edge->weight;
    newNode->next = head;   // insert a new node at front of a List
    adj->head[edge->dest] =  newNode; // update the head node of the List
}

// find - find the root of element v.
int find(int v, int parent[])
{
    if(parent[v] == v)
    {
        return v;
    }
    else 
    {
        return find(parent[v], parent);
    }
}

// is_connect - judge element u and v wether belong to the same subset, if they belong to same return true
// else return false;
bool is_connect(int u, int v, int parent[])
{
    if(find(u, parent) == find(v, parent))
    {
        return true;
    }
    return false;
}

// union_ - union u and v if u and v divide belong to different subset and return true.
// if u and v divide belong to same subset, return false.
bool union_(int u, int v, int parent[])
{
    // if true, u and v belong to same subset,no need to union
    int root_u = find(u, parent);
    int root_v = find(v, parent);
    
    if(root_v != root_u)
    {
        // set root_u as element root_v parent, means subset root_v is a subset
        // of subset root_u
        parent[root_v] = root_u;    
        return true;
    }
    return false;
}

// insert - insert a edge into edgeList and maintain edgeList none-decrease order.
struct Edge * insert(struct Edge *head, struct Edge *insert_edge)
{
    struct Edge *traverse = head;
    if(head == NULL)    // empty list and insert insert_edge as head of list.
    {
        head = insert_edge;
        return head;
    }
    if(head->weight >= insert_edge->weight)
    {
        insert_edge->next = head;
        head = insert_edge;
        return head;
    }
    while(traverse != NULL)
    {
        if(traverse->weight <= insert_edge->weight)
        {
            if(traverse->next != NULL && traverse->next->weight >= insert_edge-> weight)
            {
                insert_edge->next = traverse->next;
                traverse->next = insert_edge;
                return head;
            }
            else if(traverse->next == NULL) 
            {
                traverse->next = insert_edge;
                return head;
            }
        }
        traverse = traverse->next;
    }
    return head;
}

struct Graph *minimum_spaning_tree(struct Graph *graph)
{
    struct Edge* edge_list = NULL;
    struct Edge* new_edge = NULL;
    struct ListNode *traverse = NULL;
    struct Graph *tree = create_graph(graph->vertice_count);
    int parent[graph->vertice_count];   
    for(int i = 0; i < graph->vertice_count; i++)   // each vertice is a subset, 
                                                    // any two subsets is no-overlapping
    {
        parent[i] = i;
    }
    // step one order edges of the undirected weight connective graph by the edge's weight.
    for(int i = 0; i < graph->vertice_count; i++)
    {
        traverse = graph->head[i];  // traverse point to the head node of List.
        while(traverse != NULL)
        {
            if(i < traverse->vertice)   // <i, traverse->vertice> <traverse->vertice, i> is equal so 
                                        // just need add once. not consider <src, dst> src = dst case.
            {
                new_edge = create_edge(i, traverse->vertice, traverse->weight);
                edge_list = insert(edge_list, new_edge);
            }
            traverse = traverse->next;
        }
    }
    // step two: image initial every vertice of the graph is independent. add minimum weight edge to it and 
    // make there no circle in it.
    struct Edge *minimum_edge = edge_list;
    int count = 0;  
    // step three: repeat step two until count equal to number of vertice - 1
    // because connect n vertice least need (n - 1) edges.
    while(count != graph->vertice_count - 1)
    {
        if(union_(minimum_edge->source, minimum_edge->dest, parent))  // no circle 
        {
            count++;
            add_edge(minimum_edge, tree);
        }
        minimum_edge = minimum_edge->next;  // get left minimum edge 
    }
    return tree;
}


int main() {
	//code
	int vertice_count = 4;
	struct Graph *adj = create_graph(4);
	struct Edge *edge_1 = create_edge(0, 1, 5);
	add_edge(edge_1, adj);
	edge_1 = create_edge(0, 2, 7);
	add_edge(edge_1, adj);
	edge_1 = create_edge(0, 3, 8);
	add_edge(edge_1, adj);
	edge_1 = create_edge(1, 2, 9);
	add_edge(edge_1, adj);
	edge_1 = create_edge(1, 3, 3);
	add_edge(edge_1, adj);
	edge_1 = create_edge(2, 3, 10);
	add_edge(edge_1, adj);
	
	struct Graph *tree = minimum_spaning_tree(adj);
	int weight_tree = 0;
	struct ListNode *traverse = NULL;
	for(int i = 0; i < tree->vertice_count; i++)
	{
	    traverse = tree->head[i];
	    while(traverse != NULL)
	    {
	        if(i < traverse->vertice)   // in a undirected graph. edge <i, traverse->vertice> and
	                                    // <traverse->vertice, i> is the same edge.thus add once.
	        {
	            weight_tree += traverse->weight;
	        }
            traverse = traverse->next;
	    }
	}
	printf("minimum_spaning_tree' weight is %d\n", weight_tree);
	return 0;
}
