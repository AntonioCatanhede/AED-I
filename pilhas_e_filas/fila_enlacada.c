/* Implementacao da Fila usando lista ligada
* FIFO - first in first out
* O primeiro a entrar eh o primeiro a sair
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct linkedNode linkedNode;
struct linkedNode{
  int data;
  linkedNode *next;
};

typedef struct nodeQueue nodeQueue;
struct nodeQueue{
  linkedNode *first, *last;
};

nodeQueue *createNodeQueue(){
  nodeQueue *tmp = malloc(sizeof(nodeQueue));
  if(!tmp)
    return NULL;
  tmp->first = NULL;
  tmp->last = NULL;
  return tmp;
}

/* ENQUEUE E DEQUEUE
* retorna 1 em caso de sucesso
* 0 caso nao tenha conseguido alocar memoria ou lista vazia
*/
int enqueue(nodeQueue *queue, int elem){
  linkedNode *tmp = malloc(sizeof(linkedNode));
  if(!tmp)
    return 0;
  tmp->data = elem;
  tmp->next = NULL;

  if(!queue->first)
    queue->first = tmp;
  else
    queue->last->next = tmp;

  queue->last = tmp;
  return 1;
}

int dequeue (nodeQueue *queue, int *elem){
  linkedNode *tmp = queue->first;
  if(!tmp)
    return 0;
  *elem = tmp->data;
  queue->first = tmp->next;
  free(tmp);
  return 1;
}

int isEmpty(nodeQueue *queue){
  return !queue || !queue->first;
}

void deleteNodeQueue(nodeQueue *queue){
  linkedNode *cur = queue->first, *prev;
  while(!cur){
    prev = cur;
    free(prev);
    cur = cur->next;
  }
  free(queue);  
}

int main(){
  nodeQueue *queue = createNodeQueue();
  int i, j;
  // Testando o codigo...
  for(j = 0; j < 20; j++)
    printf("enqueue no elemento: %d - Sucesso ou falha: %d\n", j, enqueue(queue, j));

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
