#include <stdio.h>
#include <stdlib.h>

// Lista ligada simples
// elementos da lista ligada
typedef struct LinkedNode LinkedNode;
struct LinkedNode {
  int data;
  LinkedNode *next;
};

// adiciona um elemento no final da lista ligada
LinkedNode *appendNode(LinkedNode *first, int num){
  if(first != NULL)
    if(first->next != NULL)
      return NULL;

  LinkedNode *tmp = malloc(sizeof(LinkedNode));
  if(tmp == NULL) return NULL;

  tmp->data = num;
  tmp->next = NULL;

  if(first != NULL)
    first->next = tmp;

  return tmp;
}

// imprime a lista ligada
void printList(LinkedNode *first){
  LinkedNode *tmp = first;
  printf("\nSequencia: ");
  while(tmp != NULL){
    printf("%d ", tmp->data);
    tmp = tmp->next;
  }
}

// cria a lista ligada
LinkedNode *makeList (){
  LinkedNode *tmp = NULL, *first = NULL;
  int i, num;

  printf("Por favor, digite 5 numeros: ");
  for(i = 0; i < 5; i++){
    scanf("%d", &num);
    tmp = appendNode(tmp, num);
    if(first == NULL)
      first = tmp;
  }
  return first;
}

int main(){
  LinkedNode *seq = makeList();
  printList(seq);
  return 0;
}
