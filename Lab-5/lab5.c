//#include "lab5.h"
#include "extras.c"
//#include "extras.c"
#define INFINITY 9999
#define MAX 10

char **plan_route(Graph *gr, char *start, char *dest){

}

void add(Graph *gr, char *station){
  Vnode *new_node = (struct Vnode*) malloc(sizeof(Vnode));
  strcpy(new_node->station, station);
	// add the node to the nodes array
  gr->adj_list = realloc(
		gr->adj_list, 
		(gr->count + 1) * sizeof(Vnode)
	);
	gr->adj_list[gr->count] = calloc(
		gr->count + 1, sizeof(Vnode)
	);
  gr->adj_list[gr->count]->edges = NULL;
  
  
	gr->adj_list[gr->count] = new_node;
  gr->count++; 
}

void update(Graph *gr, char *start, char *dest, int weight){
  int index;
  for(int i = 0; i < gr->count; i++){
    if(strcmp(gr->adj_list[i]->station, start) == 0){
      index = i;
      break;
    }
  }
  Enode* new_edge = (Enode *)malloc(sizeof(struct Enode));
  
  
  gr->adj_list[index]->edges = new_edge;
  
  if(gr->adj_list[index]->edges == NULL){
    //strcpy(gr->adj_list[index]->edges->vertex, dest);
    strcpy(new_edge->vertex, dest);
    new_edge->weight = weight;
    new_edge->next = gr->adj_list[index]->edges;
    gr->adj_list[index]->edges = new_edge;
  } else if(gr->adj_list[index]->edges->weight == 0){
    gr->adj_list[index]->edges = NULL;
  }
}

void disrupt(Graph *gr, char *station){
  Enode* temp = (Enode*) malloc(sizeof(Enode));
  for(int i = 0; i < gr->count; i++){
    if((gr->adj_list[i]->station == station)){
      temp = &gr->adj_list[i]->edges[i];
      gr->adj_list[i]->edges[i].next = gr->adj_list[i]->edges[i+1].next;
    }
  }
  free(temp);
}
/*
int main(){
  Graph *gr = initialize_graph();
  add(gr, "Kipling");
  add(gr, "Spadina");
  add(gr, "Yorkdale");

  update(gr, "Kipling", "Spadina", 12);
  update(gr, "Spadina", "Yorkdale", 8);
  update(gr, "Spadina", "Bay", 2);
  update(gr, "Spadina", "Union", 4);
  update(gr, "Bay", "Bloor-Yonge", 1);
  update(gr, "Union", "Bloor-Yonge", 3);
  update(gr, "Bloor-Yonge", "Kennedy", 14);
  update(gr, "Bloor-Yonge", "Sheppard-Yonge", 11);
  update(gr, "Sheppard-Yonge", "Finch", 3);
  update(gr, "Sheppard-Yonge", "Don Mills", 6);
  disrupt(gr, "Bay");
}*/