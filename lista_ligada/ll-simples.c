#include <stdio.h>
#include <stdlib.h>

// Lista ligada simples
// elementos da lista ligada
typedef struct LinkedNode LinkedNode;
struct LinkedNode {
  int data;
  LinkedNode *next;
};

// adiciona um elemento a lista e retorna a posicao desse tempo;
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

LinkedNode *addNode(LinkedNode *seq, int position){
  int i, num;
  for(i = 0; i < position && seq != NULL; i++)
    seq = seq->next;
  if (seq == NULL) return NULL;

  printf("Qual o valor do proximo elemento da lista? ");
  scanf("%d", &num);
  LinkedNode *tmp = appendNode(seq - i, num);
}

// concatena a primeira lista (como argumento) a segunda
void *connectList (LinkedNode *f1, LinkedNode *f2){
  LinkedNode *tmp = f1;
  while(tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = f2;
}

// imprime a lista ligada
void printList(LinkedNode *first){
  LinkedNode *tmp = first;
  printf("Sequencia: ");
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

  printf("Por favor, digite 5 numeros:\n");
  for(i = 0; i < 5; i++){
    scanf("%d", &num);
    tmp = appendNode(tmp, num);
    if(first == NULL)
      first = tmp;
  }
  printf("\n");
  return first;
}

LinkedNode *reverseList(LinkedNode *seq){
    LinkedNode  *prev = NULL, *next;
    while(seq->next != NULL){
      next = seq->next;
      seq->next = prev;
      prev = seq;
      seq = next;
    }
    printList(seq);
    return seq;
}

int main(){
  // primeira sequencia
  LinkedNode *seq1 = makeList();
  printList(seq1);
  /* adicionando um elemento apos o primeiro elemento;
  LinkedNode *appendedNode = appendNode(seq1, 98);
  printList(seq1);
  // segunda sequencia, concatena com a primeira
  LinkedNode *seq2 = makeList();
  printList(seq2);
  connectList(seq1, seq2);
  printf("Lista concatenada! ");
  printList(seq1);
  // adiciona um elemento na posicao 4
  addNode(seq1, 4);
  printList(seq1);*/
  // inverte a lista ligada
  seq1 = reverseList(seq1);
  printList(seq1);

  return 0;
}
