/* pilha(stack) adota estrategia LIFO (last in first out)
* ultimo a entrar eh o primeiro a sair
* pilha dinamica: estrutura de dados utilizando lista ligada
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct linkedNode linkedNode;
struct linkedNode{
  int data;
  linkedNode *next;
};

typedef struct nodeStack nodeStack;
struct nodeStack{
  linkedNode *top;
};

nodeStack *createNodeStack(){
  nodeStack *tmp = malloc(sizeof(nodeStack));
  if(!tmp)
    return NULL;
  tmp->top = NULL;
  return tmp;
}

int isEmpty(nodeStack *stack){
  return !stack || !stack->top;
}

/* PUSH E POP:
* retorna 1 em caso de sucesso, 0 em caso de erro
* erro pode ocorrer se o programa nao conseguir alocar memoria
*/
int push(nodeStack *stack, int elem){
  linkedNode *newNode = malloc(sizeof(linkedNode));
  if(!newNode)
      return 0;
  newNode->data = elem;
  newNode->next = stack->top;
  stack->top = newNode;
  return 1;
}

int pop(nodeStack *stack, int *elem){
  linkedNode *tmp = stack->top;
  if(!tmp)
    return 0;   // pilha vazia;

  *elem = tmp->data;
  stack->top = tmp->next;
  free(tmp);
  return 1;
}

void deleteNodeStack(nodeStack *stack){
  linkedNode *tmp = stack->top, *aux;
  while(tmp){
    aux = tmp;
    tmp = tmp->next;
    free(aux);
  }
  free(stack);
}

int main(){
  nodeStack *stack = createNodeStack();
  int i, j;
  // Testando o codigo...
  for(j = 0; j < 20; j++)
    printf("Push no elemento: %d - Sucesso ou falha: %d\n", j, push(stack, j));

  for(j = 20; j > 3; j--){
    printf("Dando pop. Sucesso ou falha: %d - ", pop(stack, &i));
    printf("i = %d\n", i);
  }
  printf("Imprimindo variavel i - %d\nContinuemos a dar pop\n", i);

  for(j = 2; j >= -1; j--){
    printf("Dando pop. Sucesso ou falha: %d - ", pop(stack, &i));
    printf("i = %d\n", i);
  }
  return 0;
}
