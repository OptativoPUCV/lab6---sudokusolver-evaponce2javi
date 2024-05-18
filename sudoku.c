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
  // por indexacion
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

/*
Explicacion del profesor:
int k=4,p;
for(p=0;p<9;p++){
    int i=3*(k/3) + (p/3) ;
    int j=3*(k%3) + (p%3) ;
    printf("%d ",nodo->sudo[i][j]);
    if(p%3 == 2) printf("\n");
}
*/

int is_final(Node *n) {
  /*
  4.Implemente la función int is_final(Node * n). Esta función retorna 1 si el
  nodo corresponde a un nodo final (es decir, todos los valores de la matriz son
  distintos a 0) y 0 en caso contrario.
  */
  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9; k++) {
      if (n->sudo[i][k] == 0)
        return 0;
    }
  }
  return 1;
}

Node *DFS(Node *initial, int *cont) {

  // Cree un stack S (pila) e inserte el nodo.
  Stack *S = createStack();

  /*
  Operaciones en list.c para stack:
  Stack* createStack();
  void pop(Stack* s);
  void* top(Stack* s);
  void push(Stack* s, void* data);
  */
  push(S, initial);

  // Mientras el stack S no se encuentre vacío:
  while (S != NULL) {
    (*cont)++;
    // a) Saque y elimine el primer nodo de S.
    Node *nodo = first(S);
    pop(S);
    // void pop(Stack* s);

    // b) Verifique si corresponde a un estado final, si es así retorne el nodo.
    if (is_final(nodo)) {
      return nodo;
    }
    // c) Obtenga la lista de nodos adyacentes al nodo.
    List *list = get_adj_nodes(nodo);

    // d) Agregue los nodos de la lista (uno por uno) al stack S.
    Node *adjNode;
    while (list != NULL) {
      adjNode = first(list);
      popFront(list);
      push(S, adjNode);
      // void push(Stack* s, void* data);
    }
    // e) Libere la memoria usada por el nodo.
    free(list);
    free(nodo);
    // Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.
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