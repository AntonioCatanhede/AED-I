#include <stdio.h>
#include <stdlib.h>

// Lista ligada simples
// elementos da lista ligada
typedef struct LinkedNode LinkedNode;
struct LinkedNode {
  int data;
  LinkedNode *next;
};

// adiciona um elemento a lista e retorna o adicionado- utilizado nas outras funcoes
LinkedNode *appendNode(LinkedNode *first, int num){
  LinkedNode *tmp = malloc(sizeof(LinkedNode));
  if(tmp == NULL) return NULL;

  tmp->data = num;
  tmp->next = NULL;
  if(first != NULL)
    first->next = tmp;

  return tmp;
}

// add - 1
// remove - 0
void addRemoveNode(LinkedNode **seq, int position, int mode){
  int i, num;
  LinkedNode *current = *seq, *prev = NULL;
  if((mode != 1 && mode != 0) || seq == NULL) return;

  for(i = 1; i < position && current != NULL; i++){
    prev = current;
    current = current->next;
  }
  if (current == NULL) return;

  if(mode == 0){  // remover
    prev->next = current->next;
    free(current);
  }
  else{ // adicionar
    printf("Qual o valor do proximo elemento da lista? ");
    scanf("%d", &num);
    LinkedNode *newNode = malloc(sizeof(LinkedNode));
    if(newNode == NULL) return;

    newNode->data = num;
    newNode->next = prev->next;
    prev->next = newNode;
  }
}

// Concatena a primeira lista (como argumento) com a segunda
void *connectList (LinkedNode *f1, LinkedNode *f2){
  LinkedNode *tmp = f1;
  while(tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = f2;
}

// imprime a lista ligada
void printList(LinkedNode *seq){
  printf("Sequencia: ");
  while(seq != NULL){
    printf("%d ", seq->data);
    seq = seq->next;
  }
  printf("\n");
}

// Cria a lista ligada de acordo com o argumento (tamanho)
LinkedNode *makeList (int size){
  LinkedNode *tmp = NULL, *first = NULL;
  int i, value;

  printf("Por favor, digite %d numeros:\n", size);
  for(i = 0; i < size; i++){
    scanf("%d", &value);
    tmp = appendNode(tmp, value);
    if(first == NULL)
      first = tmp;
  }
  return first;
}

// Divide a lista ao meio, retornando primeiro elemento da segunda metade
LinkedNode* splitList(LinkedNode *seq1){
  int i, size = 0;
  LinkedNode *tmp = seq1;

  if(seq1 == NULL) return NULL;

  while(seq1 != NULL){
    seq1 = seq1->next;
    size++;
  }
  seq1 = tmp;

  for(i = 0; i < (size/2) - 1; i++)
    seq1 = seq1->next;
  if(size%2 == 1 && (size/2)%2 == 1) // se tamanho da lista eh impar, segunda metade do tamanho eh impar
    seq1 = seq1->next;
  // quebra a lista e retorna segunda metade
  tmp = seq1->next;
  seq1->next = NULL;
  return tmp;
}

// Deleta ultimo elemento, seja a lista circular ou nao
void deleteLastElement(LinkedNode **seq){
  LinkedNode *tmp = *seq, *prev = NULL;
  if(tmp == NULL) return;

  while(tmp->next != *seq && tmp->next != NULL){
    prev = tmp;
    tmp = tmp->next;
  }
  prev->next = NULL;
  free(tmp);
}

// Inverte a lista sobre ela mesma (sem criar uma nova)
void reverseList(LinkedNode **seq){
    LinkedNode  *prev = NULL, *current = *seq, *next;

    if(seq == NULL) return;

    while(current->next != NULL){
      next = current->next;   //salva o valor da frente
      current->next = prev;   // pega o ultimo valor de tras
      prev = current;         // atualiza o valor de tras
      current = next;         // vai para frente
    }
    current->next = prev;
    (*seq) = current;
}

int main(){ //main para testar as funcoes
  // cria primeira lista ligada
  printf("\nPrimeira sequencia...");
  LinkedNode *seq1 = makeList(5);
  printList(seq1);

  // adicionando um elemento apos o primeiro elemento;
  printf("\nAdicionando um elemento a tal sequencia...");
  LinkedNode *appendedNode = appendNode(seq1, 98);
  printList(seq1);

  // segunda sequencia, concatena com a primeira
  printf("\nSegunda sequencia...");
  LinkedNode *seq2 = makeList(5);
  printList(seq2);
  connectList(seq1, seq2);
  printf("\nLista concatenada...");
  printList(seq1);

  // adiciona um elemento na posicao 4
  printf("\nAdicionando um elemento na posicao 4 da primeira lista...");
  addRemoveNode(&seq1, 4, 1);
  printList(seq1);

  // removendo esse mesmo elemento da posicao 4
  printf("\nRemovendo o elemento anterior da posicao 4 da primeira lista...");
  addRemoveNode(&seq1, 4, 0);
  printList(seq1);

  // dividindo as listas ao meio
  printf("\nDividindo a lista ao meio...");
  LinkedNode *seq3 = splitList(seq1);
  printList(seq1);
  printList(seq3);

  // inverte a primeira Lista
  printf("\nInvertendo a primeira sequencia...");
  reverseList(&seq1);;
  printList(seq1);

  // deleta o ultimo elemento da primeira lista
  printf("\nDeletando ultimo elemento da primeira lista...");
  deleteLastElement(&seq1);
  printList(seq1);
  return 0;
}
