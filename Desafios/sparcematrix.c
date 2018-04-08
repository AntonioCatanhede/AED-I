// Primeiro desafio de AED - Multiplicacao de matrizes esparsas
// Igor Neres Trindade
#include <stdio.h>
#include <stdlib.h>

typedef struct ElemNode ElemNode;
struct ElemNode{
  int value;
  int coord[2];           // coordenada do elemento, index: 0 = linha/ 1 = coluna
  ElemNode *nextElem[2];  /* ponteiro para os proximos elementos nao nulos
                          ** index: 0 = prox elemento a direita
                          ** index: 1 = prox elemento embaixo
                          */
};

// estrutura p/ cada indice de linha/coluna que tenha elementos nao nulos
typedef struct CoordNode CoordNode;
struct CoordNode{
  int coord;
  ElemNode *nextElem;
  CoordNode *nextCoord;
};

typedef struct Matrix Matrix;
struct Matrix{
  int size[2];              // tamanho da matriz, index: 0 = linha / index 1 = colunas
  CoordNode *nextCoord[2];  // index: 0 = CoordNode a direita / 1 = CoordNode embaixo
};

Matrix *createMatrix(int line, int col){
  Matrix *tmp = malloc(sizeof(Matrix));
  if(!tmp) return NULL;
  tmp->size[0] = line;
  tmp->size[1] = col;
  tmp->nextCoord[0] = tmp->nextCoord[1] = NULL;
  return tmp;
}

CoordNode *createCoordNode(int coord){
  CoordNode *tmp = malloc(sizeof(CoordNode));
  if(!tmp) return NULL;
  tmp->coord = coord;
  tmp->nextElem = NULL;
  tmp->nextCoord = NULL;
  return tmp;
}

ElemNode *createElemNode(int value, int line, int col){
  ElemNode *tmp = malloc(sizeof(ElemNode));
  if(!tmp) return NULL;
  tmp->value = value;
  tmp->coord[0] = line;
  tmp->coord[1] = col;
  tmp->nextElem[0] = tmp->nextElem[1] = NULL;
  return tmp;
}

void appendNode(Matrix *m, int line, int col, int value){
  ElemNode *newElem = createElemNode(value, line, col), **tmp2 = NULL;
  CoordNode **tmp1 = NULL, *newCoord = NULL;
  int i, aux;

  if(!m->nextCoord[0]){ // Se nao ha elementos na matriz ainda
    m->nextCoord[0] = createCoordNode(line);
    m->nextCoord[1] = createCoordNode(col);
    m->nextCoord[0]->nextElem = m->nextCoord[1]->nextElem = newElem;
    return;
  }

  for(i = 0; i < 2; i++){
    /* para i = 0 - percorre o indice linha no CoordNode, depois o indice coluna nos elementos
    ** para i = 1 - percorre o indice coluna no CoordNode, depois o indice linha nos elementos
    */
    tmp1 = &m->nextCoord[i];
    while((*tmp1) ? line > (*tmp1)->coord : 0) // busca pelo indice linha/coluna existente na matriz
      tmp1 = &(*tmp1)->nextCoord;

    if(!(*tmp1) || (*tmp1)->coord != line){ // se nao ha esse esse indice, cria um
      newCoord = createCoordNode(line);
      if(*tmp1)                             // se nao chegou ao final da lista ligada
        newCoord->nextCoord = *tmp1;        // insire o novo indice, que aponta para o indice onde o while parou
      *tmp1 = newCoord;                     // empurra a lista ligada para a direita
    }

    tmp2 = &(*tmp1)->nextElem;
    while((*tmp2) && col > (*tmp2)->coord[(i+1)%2])   // busca pela linha/coluna novamente (em algum elemento)
      tmp2 = &(*tmp2)->nextElem[i];

    if(*tmp2)                           // se nao chegou ao final da lista ligada
      newElem->nextElem[i] = *tmp2;     // insire o novo elemento, que aponta para o ultimo elemento do while
    *tmp2 = newElem;                    // empurra a lista ligada para a direita

    // Troca os valores de linha e coluna para a estrategia do for
    aux = line;
    line = col;
    col = aux;
  }
}

void printMatrix(Matrix *matrix){
  if(!matrix){ // Matriz inexistente
    printf("ERRO\n");
    return;
  }

  int line = matrix->size[0], column = matrix->size[1];
  int i = 0, j = 0, k = 0, l = 0;
  CoordNode *m = matrix->nextCoord[0];
  ElemNode *tmp;

  if(!m){ // Matriz Nula -> Imprime zeros
    for(k = 0; k < matrix->size[1]; k++){
      for(l = 0; l < matrix->size[0]; l++){
        if(l == 0)
          printf("[");
        printf("0 ");
      }
      printf("]\n");
    }
    return;
  }

  while(m){
    while(i++ < m->coord){
      printf("[");
      while(j++ < column)
        printf("0 ");
      printf("]\n");
      j = 0;
    }
    printf("[");
    tmp = m->nextElem;
    while(tmp){
      while(j++ < tmp->coord[1])
        printf("0 ");
      printf("%d ", tmp->value);
      tmp = tmp->nextElem[0];
    }

    while(j++ < column)
      printf("0 ");
    printf("]\n");
    m = m->nextCoord;
    j = 0;
  }
  // Caso em que ha linhas de elementos nulos ainda
  while(i++ < line){
    printf("[");
    while(j++ < column)
      printf("0 ");
    printf("]\n");
    j = 0;
  }
  printf("\n");
}

Matrix *multiplyMatrix (Matrix *mA, Matrix *mB){
  if(mA->size[1] != mB->size[0]) return NULL;

  int sum = 0;
  Matrix *m = createMatrix (mA->size[0], mB->size[1]);
  CoordNode *coord1 = NULL, *coord2 = NULL;
  ElemNode *elem1 = NULL, *elem2 = NULL;
  /* Para para CoordNode de linha e CoordNode de coluna,
  ** percorre-se os elementos de cada linha e coluna
  */
  for(coord1 = mA->nextCoord[0]; coord1; coord1 = coord1->nextCoord){
    for(coord2 = mB->nextCoord[1]; coord2; coord2 = coord2->nextCoord){
      for(elem1 = coord1->nextElem; elem1; elem1 = elem1->nextElem[0]){
        for(elem2 = coord2->nextElem; elem2 ? elem1->coord[1] > elem2->coord[0] : 0; elem2 = elem2->nextElem[1]);
        if(elem2 ? elem1->coord[1] == elem2->coord[0] : 0)
          sum += elem1->value * elem2->value;
      }
      appendNode(m, coord1->coord, coord2->coord , sum);
      sum = 0;
    }
  }
  return m;
};

int main(){
  /* Ln - linhas da Matriz n
  *  Cn - colunas da Matriz n
  *  Nn - numeros de elementos nao nulos da Matriz n
  */
  int LA, CA, NA, LB, CB, NB, value, line, col;
  char command = '\0';
  Matrix *mA = NULL, *mB = NULL, *m = NULL;

  scanf("%d %d %d %d %d %d", &LA, &CA, &NA, &LB, &CB, &NB);
  mA = createMatrix(LA, CA);
  mB = createMatrix(LB, CB);
  // Acrescentando os elementos a cada matriz
  for(; NA > 0; NA--){
    scanf("%d %d %d", &line, &col, &value);
    appendNode(mA, line, col, value);
  }
  for(; NB > 0; NB--){
    scanf("%d %d %d", &line, &col, &value);
    appendNode(mB, line, col, value);
  }
  m = multiplyMatrix(mA, mB);
  while(command != 'S'){
    scanf("%c", &command);
    if(command == 'A')  // mostrar matriz A
      printMatrix(mA);
    else if (command == 'B')  // mostrar matriz  B
      printMatrix(mB);
    else if (command == 'M')  // mostrar matriz resultado da multiplicacao
      printMatrix(m);
  }
  return 0;
}
