#include <stdio.h>
#include <stdlib.h>

// nodo para os elementos da matriz esparsa
typedef struct elementNode elementNode;
struct elementNode{
  int value;
  int column;
  int line;
  elementNode *nextElement;
};

// nodo cabeça para linhas
typedef struct positionNode positionNode;
struct positionNode{
  int position;
  elementNode *nextElement;
  positionNode *nextPosition;
};

// cria um nodo de elemento e, se o nodo anterior nao for nulo, faz a ligacao
elementNode *addElementNode (elementNode *current, int value, int line, int column){
  elementNode *actual = malloc(sizeof(elementNode));
  if(actual == NULL) return NULL;
  // atribuicoes de valores ao nodo criado
  actual->value = value;
  actual->line = line;
  actual->column = column;
  actual->nextElement = NULL;
  // se o argumento nao for nulo, faz a ligacao
  if(current != NULL)
    current->nextElement = actual;
  return actual;
}

// cria um nodo de posicao (cabeca) e, se o nodo anterior nao for nulo, faz a ligacao
positionNode *addPositionNode (positionNode *current, int position){
  positionNode *actual = malloc(sizeof(positionNode));
  if(actual == NULL) return NULL;
  // atribuicoes de valores ao nodo criado
  actual->position = position;
  actual->nextElement = NULL;
  actual->nextPosition = NULL;
  // se o argumento nao for nulo, faz a ligacao
  if(current != NULL)
    current->nextPosition = actual;
  return actual;
}

// funcao para criacao de matriz esparsa
positionNode *makeSparseMatrix(int line, int column){
  int i, j, num;
  int validValue = 1; // garante que criemos somente uma elementNode por linha
  elementNode *curElement = NULL;
  positionNode *curPosition = NULL, *firstPosition = NULL; // firstPosition usado para o return

  printf("Digite os valores de sua matriz %dx%d:\n", line, column);
  for(i = 0; i < line; i++){
    for(j = 0; j < column; j++){
      scanf("%d", &num);
      // adicionamos na matriz esparsa numeros != 0
      if(num){
        curElement = addElementNode(curElement, num, i, j);
        if(validValue){
          // se eh o primeiro numero != 0 de tal linha
          curPosition = addPositionNode(curPosition, i);
          curPosition->nextElement = curElement;
          validValue = 0;
          if(firstPosition == NULL) // guarda o primeiro nodo para return
            firstPosition = curPosition;
        }
      }
    }
    validValue = 1;
    curElement = NULL;
  }
  return firstPosition;
}

// funcao para teste da matriz esparsa
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

void insertElement (positionNode *curPosition, int value, int line, int column){
  elementNode *curElement, *prevElement = NULL;
  positionNode *prevPosition;
  if(curPosition == NULL) return;

  while(curPosition != NULL ? curPosition->position < line : 0){
    prevPosition = curPosition;
    curPosition = curPosition->nextPosition;
  }

  if(curPosition == NULL){
    if(value){
      prevPosition = addPositionNode(prevPosition, line);
      curElement = addElementNode(prevPosition->nextElement, value, line, column);
      prevPosition->nextElement = curElement;
    }
  }
  else{
    if(curPosition->position == line){
      if(value){
        curElement = curPosition->nextElement;
        while(curElement != NULL ?  curElement->column < column : 0){
          prevElement = curElement;
          curElement = curElement->nextElement;
        }

        if(curElement == NULL){
          curElement = addElementNode(prevElement, value, line, column);
        }
        else{
          if(curElement->column == column){
            curElement->value = value;
          }
          else{
            prevElement = addElementNode(prevElement, value, line, column);
            prevElement->nextElement = curElement;
            if(curPosition->nextElement == curElement)
              curPosition->nextElement = prevElement;
          }
        }
      }
    }
    else{
      // line < curPosition->position, entao devemos colocar novo nodo entre o prev e o current
      if(value){
        prevPosition = addPositionNode(prevPosition, line);
        curElement = addElementNode(prevPosition->nextElement, value, line, column);
        prevPosition->nextElement = curElement;
        prevPosition->nextPosition = curPosition;
      }
    }
  }
}

void printSparseMatrix (positionNode *firstPosition, int line, int column){
  positionNode *curPosition = firstPosition;
  elementNode *curElement = firstPosition->nextElement;
  int i, j;

  for(i = 0; i < line; i++){
    if(curPosition != NULL ? curPosition->position == i : 0){
      // verifica se linha atual possui um nodo cabeca (algum elemento !=0)
      // isso pode ocorrer somente no caso de curPosition nao nulo
      for(j = 0; j < column; j++){
        if(curElement != NULL ? curElement->column == j : 0){
          printf("%3d", curElement->value);
          curElement = curElement->nextElement;
        }
        else{
          printf("%3d", 0);
        }
      }
      curPosition = curPosition->nextPosition;
      if(curPosition != NULL)
        curElement = curPosition->nextElement;
    }
    else{
      // curPosition null ou linha com elementos nulos somente
      for(j = 0; j < column; j++)
        printf("%3d", 0);
    }
    printf("\n");
  }
}

int main(){
  positionNode *matrix = makeSparseMatrix(6, 5);
  //testSparseMatriz(matrix);
  printf("\nImprimindo a matriz esparsa:\n");
  printSparseMatrix(matrix, 6, 5);

  printf("\nAdicionando um novo numero na matriz:\n");
  insertElement(matrix, 100, 4, 0);
  printSparseMatrix(matrix, 6, 5);

  printf("\nAdicionando um novo numero na matriz:\n");
  insertElement(matrix, 50, 5, 4);
  printSparseMatrix(matrix, 6, 5);

  printf("\nMudando o ultimo elemento adicionado:\n");
  insertElement(matrix, 100, 5, 4);
  printSparseMatrix(matrix, 6, 5);

  printf("\nAdicionando um novo numero na matriz:\n");
  insertElement(matrix, 100, 2, 2);
  printSparseMatrix(matrix, 6, 5);
  return 0;
}

/* Sugestao de matriz esparsa para teste:
0 0 0 5 0
0 9 0 0 0
4 0 0 6 0
0 0 0 0 0
0 7 0 0 0
0 0 0 0 0
*/
