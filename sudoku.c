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

int recorrerMatriz(Node *n, int a, int b) {
  int auxSudo = n->sudo[a][b];
  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9; k++) {
      if (n->sudo[i][k] == auxSudo)
        return 0;
    }
  }
  return 1;
}

int is_valid(Node *n) {
  int auxSudo = n->sudo[0][0];
  /*
 No se repitan números en las filas
 No se repitan números en las columnas
 No se repitan números en las submatrices de 3x3
 // If numero is in sitio, return cero
 // if no está, return 1
 */
  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9; k++) {
      if (recorrerMatriz(n, i, k) == 0)
        return 0;
    }
  }
  return 1;
}

List *get_adj_nodes(Node *n) {
  List *list = createList();
  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9; k++) {
      if (n->sudo[i][k] == 0) // vacio kuak
      {
        Node *newN = copy(n);
      }
    }
  }
  return list;
}

int is_final(Node *n) { return 0; }

Node *DFS(Node *initial, int *cont) { return NULL; }

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/