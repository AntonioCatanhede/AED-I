#include <stdio.h>
#include <stdlib.h>

// noh para os elementos da matriz esparsa
typedef struct elementNode elementNode;
struct elementNode{
  int value;
  int column;
  int line;
  elementNode *nextElement;
};

// noh cabeça para linhas
typedef struct positionNode positionNode;
struct positionNode{
  int position;
  elementNode *nextElement;
  positionNode *nextPosition;
};

elementNode *addElementNode (elementNode *current, int value, int line, int column){
  elementNode *actual = malloc(sizeof(elementNode));
  if(actual == NULL) return NULL;

  actual->value = value;
  actual->line = line;
  actual->column = column;
  actual->nextElement = NULL;

  if(current != NULL)
    current->nextElement = actual;
  return actual;
}

positionNode *addPositionNode (positionNode *current, int position){
  positionNode *actual = malloc(sizeof(positionNode));
  if(actual == NULL) return NULL;

  actual->position = position;
  actual->nextElement = NULL;
  actual->nextPosition = NULL;

  if(current != NULL)
    current->nextPosition = actual;
  return actual;
}

positionNode *makeSparseMatrix(int line, int column){
  int i, j, num;
  int validValue = 1;
  elementNode *curElement = NULL;
  positionNode *curPosition = NULL, *firstPosition = NULL;

  printf("Digite os valores de sua matriz %dx%d:\n", line, column);
  for(i = 0; i < line; i++){
    for(j = 0; j < column; j++){
      scanf("%d", &num);

      if(num){
        curElement = addElementNode(curElement, num, i, j);

        if(validValue){
          curPosition = addPositionNode(curPosition, i);
          curPosition->nextElement = curElement;
          validValue = 0;
          if(firstPosition == NULL) // guarda o primeiro noh cabeca para return
            firstPosition = curPosition;
        }
      }
    }
    validValue = 1;
    curElement = NULL;
  }
  return firstPosition;
}

void testSparseMatriz (positionNode *firstPosition){
  printf("Teste da matriz esparsa:\n");
  positionNode *curPosition = firstPosition;
  elementNode *curElement;

  while(curPosition != NULL){
    printf("POSICAO: linha %d ->", curPosition->position);

    curElement = curPosition->nextElement;
    while(curElement != NULL){
      printf("ELEMENTO: valor %d, ( %d , %d ) ->", curElement->value, curElement->line, curElement->column);
      curElement = curElement->nextElement;
    }

    curPosition = curPosition->nextPosition;
    printf("\n");
  }
}

int main(){
  positionNode *matrix = makeSparseMatrix(6, 5);
  testSparseMatriz(matrix);

  return 0;
}
