#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  int fila[9][10] = {0};
  int columna[9][10] = {0};
  int submatriz[9][10] = {0};
  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9; k++) {
      int numero = n->sudo[i][k];
      if (numero != 0) {
        int col = (i / 3);
        int fil = (k / 3);
        int subInd = col * 3 + fil;
        if (fila[i][numero] != 0)
          return 0;
        fila[i][numero]++;
        if (columna[k][numero] != 0)
          return 0;
        columna[k][numero]++;
        if (submatriz[subInd][numero] != 0)
          return 0;
        submatriz[subInd][numero]++;
      }
    }
  }
  return 1;
}

List *get_adj_nodes(Node *n) {
  List *list = createList();
  int vacio = 0; // si encontramos o no
  for (int i = 0; i < 9 && !vacio; i++) {
    for (int k = 0; k < 9 && !vacio; k++) { // Recorridoo
      if (n->sudo[i][k] == 0) {             // hallamos vacia
        for (int j = 1; j <= 9; j++) {
          Node *newN = copy(n);
          if (newN != NULL) {
            newN->sudo[i][k] = j;
            if (is_valid(newN))
              pushBack(list, newN);
            else
              free(newN);
          } else {
            clean(list);
            return NULL;
          }
        }
        vacio = 1;
      }
    }
  }
  return list;
}

int is_final(Node *n) {
  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9; k++) {
      if (n->sudo[i][k] == 0)
        return 0;
    }
  }
  return 1;
}

Node *DFS(Node *initial, int *cont) {
  Stack *S = createStack();
  push(S, initial);

  while (!is_empty(S)) {
    (*cont)++;
    Node *nodo = top(S);
    pop(S);
    if (is_final(nodo)) {
      return nodo;
    }
    List *list = get_adj_nodes(nodo);
    Node *adjNode;
    while (!is_empty(list)) {
      adjNode = (Node *)first(list);

      popFront(list);
      push(S, adjNode);
    }
    clean(list);
    free(nodo);
  }
  return NULL;
}

/*
int main(int argc, char *argv[]) {

  Node *initial = read_file("s12a.txt");
  ;

  int cont = 0;
  Node *final = DFS(initial, &cont);
  printf("iterations:%d\n", cont);
  print_node(final);

  return 0;
}*/