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
  printf("\n\n");
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

// divide a lista ao meio, retornando primeiro elemento da segunda metade
LinkedNode* splitList(LinkedNode *seq1){
  int i, size = 0;
  LinkedNode *tmp = seq1;
  while(seq1 != NULL){
    seq1 = seq1->next;
    size++;
  }
  seq1 = tmp;

  for(i = 0; i < (size/2) - 1; i++)
    seq1 = seq1->next;
  // se tamanho da lista eh impar, segunda metade do tamanho eh impar
  if(size%2 == 1 && (size/2)%2 == 1)
    seq1 = seq1->next;
  // quebra a lista e retorna segunda metade
  tmp = seq1->next;
  seq1->next = NULL;
  return tmp;
}

// Deleta ultimo elemento, seja a lista circular ou nao
LinkedNode *deleteLastElement(LinkedNode *seq){
  LinkedNode *first = seq;
  while(seq->next != first && seq->next != NULL)
    seq = seq->next;
  free(seq);
  return first;
}

// Inverte a lista sobre ela mesma (sem criar uma nova)
LinkedNode *reverseList(LinkedNode *seq){
    LinkedNode  *prev = NULL, *next;
    while(seq->next != NULL){
      next = seq->next;
      seq->next = prev;
      prev = seq;
      seq = next;
    }
    seq->next = prev;
    return seq;
}

int main(){
  // cria primeira lista ligada
  printf("Primeira sequencia - ");
  LinkedNode *seq1 = makeList();
  printList(seq1);

  // adicionando um elemento apos o primeiro elemento;
  printf("Adicionando um elemento a tal sequencia - ");
  LinkedNode *appendedNode = appendNode(seq1, 98);
  printList(seq1);

  // segunda sequencia, concatena com a primeira
  printf("Segunda sequencia - ");
  LinkedNode *seq2 = makeList();
  printList(seq2);
  connectList(seq1, seq2);
  printf("Lista concatenada - ");
  printList(seq1);

  // adiciona um elemento na posicao 4
  printf("Adicionando um elemento na posicao 4 da primeira lista - ");
  addNode(seq1, 4);
  printList(seq1);

  // dividindo as listas ao meio
  printf("Dividindo a lista ao meio - ");
  LinkedNode *seq3 = splitList(seq1);
  printList(seq1);
  printList(seq3);

  // inverte a primeira Lista
  printf("Invertendo a primeira sequencia - ");
  seq1 = reverseList(seq1);
  printList(seq1);
  return 0;
}
