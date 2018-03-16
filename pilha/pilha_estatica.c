/* pilha(stack) adota estrategia LIFO (last in first out)
* ultimo a entrar eh o primeiro a sair
* pilha estatica: estrutura de dados utilizando arranjo
*/
#include <stdio.h>
#include <stdlib.h>

#define MINCAPACITY 15

typedef struct arrStack arrStack;
struct arrStack{
  int *data ;     // ponteiro para o vetor alocado
  int capacity;   // tamanho do vetor alocado
  int top;        // indice do elemento no topo da pilha
                  // adotemos uma convecao: se top == 0, entao pilha vazia
};

arrStack *createArrStack(){
  arrStack *tmp = malloc(sizeof(arrStack));
  if(!tmp)
    return NULL;
  tmp->data = malloc(MINCAPACITY*sizeof(int));
  if(!tmp->data){
    // se nao consegue alocar memoria para os elementos, deleta tudo
    free(tmp);
    return NULL;
  }

  tmp->top = 0;                 // nenhum elemento ainda
  tmp->capacity = MINCAPACITY;  // capacidade minima de inicio
  return tmp;
}

int isEmpty(arrStack *stack){
  return !stack || !stack->top;   // nao pode dar algum problema?!
}

int isFull(arrStack *stack){
  return stack->top == stack->capacity;
}

/* Em caso de sucesso, push retorna indice do elemento no topo da pilha
* no caso contrario, retorna 0
*/
int push(arrStack *stack, int elem){
  if(isFull(stack))
    return 0;
  stack->data[stack->top] = elem;
  return ++stack->top;
}

/* na funcao pop, modificamos o valor da var dentro da funcao
* para poder retornar o indice do elemento, em caso de sucesso
* ou -1, caso contrario
*/
int pop(arrStack *stack, int *elem){
  if(isEmpty(stack))
    return -1;
  *elem = stack->data[--stack->top];
  return stack->top;
}

void deleteStack (arrStack *stack){
  if(!stack){
    free(stack->data);
    free(stack);
  }
}

int main(){
  arrStack *stack = createArrStack();
  int i;
  // Testando o codigo...
  printf("Dando push no elemento 1 - %d\n", push(stack, 1));
  printf("Dando push no elemento 145 - %d\n", push(stack, 145));
  printf("Dando pop na variavel i - %d\n", pop(stack, &i));
  printf("Imprimindo variavel i - %d\n", i);
  return 0;
}
