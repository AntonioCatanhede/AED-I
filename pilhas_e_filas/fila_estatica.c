/* Implementacao de fila estatica AUTOREAJUSTAVEL usando arranjos
* LIFO - first in first out
* O primeiro a entrar eh o primeiro a sair
* Implementacao por Igor Neres Trindade :)
*/
#include <stdio.h>
#include <stdlib.h>

#define MINCAPACITY 10

typedef struct arrQueue arrQueue;
struct arrQueue{
  int *data;
  int capacity;
  int first, last;
};

arrQueue *createArrQueue(){
  arrQueue *tmp = malloc(sizeof(arrQueue));
  if(!tmp)
    return NULL;
  /* Se nao consegue alocar memoria para o arranjo
  * descarta a fila ja criada
  */
  tmp->data = malloc(MINCAPACITY*sizeof(int));
  if(!tmp->data){
    free(tmp);
    return NULL;
  }

  tmp->capacity = MINCAPACITY;
  tmp->first = 0;
  tmp->last = 0;
  return tmp;
}

int isEmpty (arrQueue *queue){
  return !queue || queue->first == queue->last;
}

/* Abaixo, usamos uma propriedade interessante para comparacao
* dado x < X, o resto de x/X eh sempre x
* assim, podemos usar x+1/X para comparar a proxima posicao
* quando x == X, o resto eh zero e temos o inicio da fila
*/
int isFull (arrQueue *queue){
  return (queue->last+1)%(queue->capacity) == queue->first;
}

int enqueue(arrQueue *queue, int elem){
    if(isFull(queue)){
      /* Poderiamos simplesmente retornar zero, se nao auto-reajustavel
      * mas dobraremos a capacidade quando estiver cheia
      */
      queue->capacity *= 2;
      queue->data = realloc(queue->data, queue->capacity * sizeof(int));
      if(!queue->data){
        free(queue);        // se nao conseguiu realocar, descarta fila
        return 0;
      }
    }
    queue->data[queue->last] = elem;
    queue->last = (queue->last + 1) % (queue->capacity);
    return 1;
}

/* A variavel como argumento, apos o retorno da funcao,
* possuirah o valor do elemento desenfileirado
* a funcao retorna sucesso ou falha
*/
int dequeue (arrQueue *queue, int *elem){
  if(isEmpty(queue))
    return 0;
  /* Se 1/4 inicial da matriz estiver ocupada somente
  * dividiremos ao meio a matriz
  */
  if(queue->first <= queue->last && queue->last <= queue->capacity/4){
    queue->capacity /= 2;
    queue->data = realloc(queue->data, queue->capacity * sizeof(int));
  }
  *elem = queue->data[queue->first];
  queue->first = (queue->first + 1) % (queue->capacity);
  return 1;
}

int main(){
  arrQueue *queue = createArrQueue();
  int i, j;
  // Testando o codigo...
  for(j = 0; j < 20; j++)
    printf("Queue no elemento: %d - Sucesso ou falha: %d\n", j, enqueue(queue, j));

  for(j = 20; j > 3; j--){
    printf("dequeue... Sucesso ou falha: %d - ", dequeue(queue, &i));
    printf("i = %d\n", i);
  }
  printf("Imprimindo variavel i - %d\nContinuemos a dar dequeue\n", i);

  for(j = 2; j >= -1; j--){
    printf("dequeue... Sucesso ou falha: %d - ", dequeue(queue, &i));
    printf("i = %d\n", i);
  }
  return 0;
}
