#include <stdio.h>
#include <stdlib.h>

// Lista ligada simples
// elementos da lista ligada
typedef struct LinkedNode LinkedNode;
struct LinkedNode {
  int data;
  LinkedNode *next;
};

// adiciona um elemento a lista
LinkedNode *appendNode(LinkedNode *first, int num){
  LinkedNode *tmp = malloc(sizeof(LinkedNode));
  if(tmp == NULL) return NULL;

  tmp->data = num;
  tmp->next = NULL;

  if(first != NULL){
    if(first->next != NULL)
      tmp->next = first->next;
    first->next = tmp;
  }
  return tmp;
}

// concatena o primeiro argumento ao segundo
void *connectList (LinkedNode *f1, LinkedNode *f2){
  LinkedNode *tmp = f1;
  while(tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = f2;
}

// imprime a lista ligada
void printList(LinkedNode *first){
  LinkedNode *tmp = first;
  printf("\nSequencia: ");
  while(tmp != NULL){
    printf("%d ", tmp->data);
    tmp = tmp->next;
  }
  printf("\n");
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

LinkedNode *reverseList(LinkedNode *first){
    LinkedNode *tmp = first, *prev, *next;

}

int main(){
  LinkedNode *seq1 = makeList();
  printList(seq1);  // imprimiu primeira sequencia

  LinkedNode *appendedNode = appendNode(seq1, 98); // coloquei um item no meio
  printList(seq1);

  LinkedNode *seq2 = makeList();
  printList(seq2);  // imprimiu segunda sequencia
  connectList(seq1, seq2);  // concatena a segunda na primeira
  printf("Lista concatenada! ");
  printList(seq1);  // imprime lista concatenada


  return 0;
}
