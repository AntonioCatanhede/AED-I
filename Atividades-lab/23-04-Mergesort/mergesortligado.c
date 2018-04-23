#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedNode linkedNode;
struct linkedNode{
  int RA;
  int grade;
  linkedNode *next, *last;
};

void *insertNode(linkedNode **linkedList, int RA, int grade){
  linkedNode *tmp = *linkedList, *last = NULL;

  while(tmp ? tmp->RA != RA : 0){
    last = tmp;
    tmp = tmp->next;
  }

  if(!tmp){
    // caso RA nao esteja na lista, ele eh adicionado
    linkedNode *newNode = malloc(sizeof(linkedNode));
    if(newNode == NULL) return NULL;

    newNode->RA = RA;
    newNode->grade = grade;
    newNode->next = newNode->last = NULL;

    if(!last)
      // primeiro nodo (quando a lista esta vazia)
      *linkedList = newNode;
    else{
      // quando a lista jah possui algum elemento
      last->next = newNode;
      newNode->last = last;
    }
  }
  else
    // caso contrario, atualiza a nota
    tmp->grade = grade;

}

void swapNode(linkedNode *node1, linkedNode *node2){
  int tmpInt;
  char tmpChar[51];

  tmpInt = node1->RA;
  node1->RA = node2->RA;
  node2->RA = tmpInt;

  tmpInt = node1->grade;
  node1->grade = node2->grade;
  node2->grade = tmpInt;
}

// modo 1 -> ordenacao por RA, modo 2 -> ordenacao por nome
void mergeSort(linkedNode *linkedList, int mode){

}

void printList(linkedNode *tmp){
  if(!tmp) return;
  printf("[%d %d]\n", tmp->RA, tmp->grade);
  printList(tmp->next);
}

void deleteList(linkedNode *tmp){
  if(!tmp) return;
  deleteList(tmp->next);
  free(tmp);
}

int main(){
  int input = 1, RA, grade, mode;
  linkedNode *linkedList = NULL;

  while(input != 0){
    scanf("\n%d", &input);
    switch (input) {
        case 1:   // Insere novo nodo
          scanf("%d %d", &RA, &grade);
          insertNode(&linkedList, RA, grade);
        break;

        case 2:   // Imprime a lista
          printList(linkedList);
        break;

        case 6:   // Busca nodo

        break;

        case 9:   // Imprime lista ligada

        break;
    }
  }
  deleteList(linkedList);
  return 0;
}
