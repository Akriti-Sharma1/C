#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LEN 100

/**
Struct definitions for Stack implementation as Linked List
*/

// Struct for your linked list (adjaceny list)
typedef struct StackNode {
	int cargo; // node's index
	struct StackNode* next;
} StackNode;

// Creating a stack struct 
typedef struct Stack {
	StackNode* top;
	int num_el;
} Stack;

/**
Struct definitions for Graph implementation as Adj Mtx
*/

// Struct for one node of the graph3
typedef struct GraphNode {

// The actual cargo (in this case the name)
char cargo[MAX_NAME_LEN]; 
// The index of each graph node
int idx;
// The previous graphnode
struct GraphNode* prev;
// If we've checked this node or not (for traversal purposes)
int explored;
} GraphNode;

// Struct for the entire graph
typedef struct Graph {
// dynamically allocated array of size num_nodes * sizeof(GraphNode*) that holds all our nodes
GraphNode** nodes; 
// dynamically allocated array of size num_nodes * sizeof(int*) that holds the contents of our adjacency matrix
int** adj_mtx; 
// The total number of nodes we have
int num_nodes;
} Graph;

/**
Stack operations
*/
// Function to initialize the stack that creates our graph
Stack* initialize_stack(){
  // Create the actual stack and alloc memory
	Stack* new_stack = (Stack*)malloc(sizeof(Stack));
  // The top is null as it is empty currently
	new_stack->top = NULL;
  // The number of elements is 0 because it is empty
	new_stack->num_el = 0;
	return new_stack;
}

// Write a function to add a node to the stack
void push(Stack* s, int val){
  // Create an actual new node and alloc memory
	StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
  // Put the value in the cargo
	new_node->cargo = val;
  // The next pointer of this node is the top node
	new_node->next = s->top;
  // This is the top node as our stack was previously empty
	s->top = new_node;
  // Increase the number of elements
	s->num_el++;
}

// Write a function to pop out a node of the stack
int pop(Stack* s){
	// Create a temporary node and make it equal to the top node (stack follows FIFO order)
	StackNode* node_to_free = s->top;
  // Store the value that you are popping out
	int result = s->top->cargo;
	// Make the top of the stack the node right below the one we're popping out
	s->top = s->top->next;
  // Decrease the number of elements
	s->num_el--;
	// Free the temporary node that you created
	free(node_to_free);
	return result;
}

/**
Graph operations
*/

// Function to print out the full graph and adjacency matrix
void print_graph(Graph* graph){
	fprintf(stdout, "Printing graph elements...\n");
	for (int i=0; i<graph->num_nodes; i++){
		fprintf(stdout, "Index %d is: %s \n", i, graph->nodes[i]->cargo);
	}
	
	fprintf(stdout, "Printing adjacency matrix...\n");
	for (int i=0; i<graph->num_nodes; i++){
		for (int j=0; j<graph->num_nodes; j++) {
			fprintf(stdout, "%d ", graph->adj_mtx[i][j]);
		} fprintf(stdout, "\n");
	} fprintf(stdout, "\n\n");
}

// Function to add a node into the graph. Takes in the pointer to the graph and the new node you want to add.
void add_node(Graph* graph, GraphNode* new_node){
	/** require that the node is not present in the graph and that the graph's adjacency matrix */
  
	// first, make more room in the nodes array
	graph->nodes = realloc(
		graph->nodes, 
		(graph->num_nodes + 1) * sizeof(GraphNode*)
	);
	// add the node to the nodes array
	graph->nodes[graph->num_nodes] = new_node;
	
	//add space in the adjacency matrix
	// add a row
	graph->adj_mtx = realloc(
		graph->adj_mtx, 
		(graph->num_nodes + 1) * sizeof(int*)
	);
	graph->adj_mtx[graph->num_nodes] = calloc(
		graph->num_nodes + 1, sizeof(int)
	);
	// modify existing rows to have additional column
	for (int i=0; i < graph->num_nodes; i++){
		graph->adj_mtx[i] = realloc(
			graph->adj_mtx[i], graph->num_nodes + 1 * sizeof(int)
		);
		graph->adj_mtx[i][graph->num_nodes] = 0;
	}
	
		// modify the graphnode's idx
	new_node->idx = graph->num_nodes;
	
	// increment the count of number of nodes
	graph->num_nodes++;
}

void add_edge(Graph* graph, GraphNode* node1, GraphNode* node2){
	// require that node 1 and node 2 are already in the graph
	graph->adj_mtx[node1->idx][node2->idx] = 1;
	graph->adj_mtx[node2->idx][node1->idx] = 1;
}

// FUnction to initialize and create an empty graph node
GraphNode* initialize_graph_node(char name[]){
  // Create an actual graph node and alloc memory
	GraphNode* gn = (GraphNode*)malloc(sizeof(GraphNode));
  // Set the index of the graphnode 
	gn->idx = -1;
  // Add the cargo (the name)
	strcpy(gn->cargo, name);
  // The previous node is NULL as our graph is empty now
	gn->prev = NULL;
  // It has not been explored
	gn->explored = 0;
	return gn;
}

// Function to initialize and create a new graph
Graph* initialize_graph(){
  // Create the actual graph and alloc memory
	Graph* graph = (Graph*)malloc(sizeof(Graph));
  // There are no nodes yet
	graph->nodes = NULL;
  // There is no adjacency matrix yet
	graph->adj_mtx = NULL;
  // There are no nodes yet
	graph->num_nodes = 0;
	return graph;
}

// Function to delete/free our graph
void delete_graph(Graph** graph){
  
	for (int i=0; i<(*graph)->num_nodes; i++){
    // Free each individual node of the graph
		free((*graph)->nodes[i]); 
    // remove the rows
		free((*graph)->adj_mtx[i]); 
	}	
	// Free the nodes array in general
	free((*graph)->nodes);
  // Free the adjacency matrix
	free((*graph)->adj_mtx);
  // Free the entire graph
	free(*graph);
	*graph = NULL;
}
/**
DFS
*/


void reset_graph_post_dfs(Graph* graph){
	for (int i=0; i<graph->num_nodes; i++){
		graph->nodes[i]->explored = 0;
		graph->nodes[i]->prev = NULL;
	}
}

// Function to perform depth-first search on the graph
int dfs(Graph* graph, int start_idx, int end_idx){	
	/** Assumption: start_idx and end_idx are both valid indices in the Graph */
  // create and initialize a stack
	Stack *s = initialize_stack();
	
	// stores whatever node we pop from the stack
	int curr_idx = -1;
	
	push(s, start_idx);
	while (s->num_el != 0 && curr_idx != end_idx) {
		// pop a new node
		curr_idx = pop(s);
		fprintf(stdout, "Now expanding node ... %s\n", graph->nodes[curr_idx]->cargo);
		// expand the new node by adding its neighbors to the stack
		// make sure you are not adding nodes that are already explored!!
		for (int i=0; i<graph->num_nodes; i++){
			if (graph->adj_mtx[curr_idx][i] == 1 && curr_idx != i){
				// found a valid edge, i.e. a neighbor
				// the node here is the node at index i of the nodes array
				if (graph->nodes[i]->explored == 0 && graph->nodes[i]->prev == NULL) {
					// 0 means not yet explored
					fprintf(stdout, "\tFound neighbor %s\n", graph->nodes[i]->cargo);
					push(s, i);
					graph->nodes[i]->prev = graph->nodes[curr_idx];
				}
			}
		}
		// set the explored field of the explored node
		graph->nodes[curr_idx]->explored = 1;
	}
	
	// dfs is done
	if (curr_idx == end_idx){
		fprintf(stdout, "A path was found!\n");
		// print the path
		while (curr_idx != start_idx){
			fprintf(stdout, "\t %s\n",  graph->nodes[curr_idx]->cargo);
			curr_idx = graph->nodes[curr_idx]->prev->idx;
		} fprintf(stdout, "\t %s\n",  graph->nodes[curr_idx]->cargo);
	} else {
		fprintf(stdout, "A path was not found.\n");
	}	
	
	// print out the path that i get
}


