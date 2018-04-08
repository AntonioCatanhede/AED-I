/* pilha(stack) adota estrategia LIFO (last in first out)
* ultimo a entrar eh o primeiro a sair
* pilha estatica: estrutura de dados utilizando arranjo
*/
#include <stdio.h>
#include <stdlib.h>

#define MINCAPACITY 10

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

/* Push retorna indice do elemento no topo da pilha
* Em uma pilha nao reajustavel: sem sucesso, retorna 0
*/
int push(arrStack *stack, int elem){
  if(isFull(stack)){
    /* Caso de pilha nao reajustavel: retornaria zero
     *return 0;
     */
     stack->capacity *= 2 ;
     stack->data = realloc(stack->data, stack->capacity * sizeof(arrStack));
     if(!stack->data){
       free(stack);
       return 0;
     }
   }
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
  if(stack->top <= stack->capacity / 4){
    stack->capacity /= 2;
    stack->data = realloc(stack->data, stack->capacity * sizeof(arrStack));
    if(!stack->data){
      free(stack);
      return 0;
    }
  }
  *elem = stack->data[--stack->top];
  return stack->top;
}

void deleteStack (arrStack *stack){
  if(stack){
    free(stack->data);
    free(stack);
  }
}

int main(){
  arrStack *stack = createArrStack();
  int i, j;
  // Testando o codigo...
  for(j = 0; j < 20; j++)
    printf("Push no elemento: %d / Indice do elemento no topo da lista: %d\n", j, push(stack, j));

  for(j = 20; j > 3; j--){
    printf("Dando pop. Indice do elemento: %d -", pop(stack, &i));
    printf("Variavel retornada: %d\n", i);
  }
  printf("Imprimindo variavel i - %d\n", i);
  return 0;
}
