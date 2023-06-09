#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i, j, k;
    
    for (i = 0; i < 9; i++) {
        int used[10] = {0};
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] != 0) {
                if (used[n->sudo[i][j]] == 1) {
                    return 0;
                } else {
                    used[n->sudo[i][j]] = 1;
                }
            }
        }
    }

  for (j = 0; j < 9; j++) {
        int used[10] = {0};
        for (i = 0; i < 9; i++) {
            if (n->sudo[i][j] != 0) {
                if (used[n->sudo[i][j]] == 1) {
                    return 0;
                } else {
                    used[n->sudo[i][j]] = 1;
                }
            }
        }
    }

  for (i = 0; i < 9; i += 3) {
        for (j = 0; j < 9; j += 3) {
            int used[10] = {0};
            for (k = 0; k < 9; k++) {
                int r = i + k/3;
                int c = j + k%3;
                if (n->sudo[r][c] != 0) {
                    if (used[n->sudo[r][c]] == 1) {
                        return 0;
                    } else {
                        used[n->sudo[r][c]] = 1;
                    }
                }
            }
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int i, j, k;
    
    for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
              for (k = 1; k <= 9; k++) {
                    Node* nodoAdj = copy(n);
                    nodoAdj->sudo[i][j] = k;
                    if (is_valid(nodoAdj)) {
                        pushBack(list, nodoAdj);
                    } else {
                        free(nodoAdj);
                    }
                }
              return list;
            }
        }
    }
    
  return list;
}


int is_final(Node* n){
  int i, j;
  for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
          if (n->sudo[i][j] == 0) {
              return 0;
          }
      }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *stack = createStack();
  push(stack, initial);
  while(!is_empty(stack)){
    Node* current = (Node*)top(stack);
    pop(stack);
    if(is_final(current))
      return current;
    List *adj_nodes = get_adj_nodes(current);
    
    while(!is_empty(adj_nodes)){
      Node *nodoLadito = (Node*)top(adj_nodes);
      pop(adj_nodes);
      push(stack, nodoLadito);
    }
    free(current);
    free(adj_nodes);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/