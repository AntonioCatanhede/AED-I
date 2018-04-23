#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedNode linkedNode;
struct linkedNode{
  int RA;
  int grade;
  linkedNode *next, *last;
};

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

linkedNode* midNode (linkedNode *first, linkedNode *last){
  linkedNode *tmp = first;
  int count = 0, i;

  while(tmp ? tmp != last : 0){
    tmp = tmp->next;
    count++;  // tamanho da lista ligada
  }

  for(i = 0; i < count/2 -1; i++)
    first = first->next;

  printf("Test do MidNode: ");
  if(first) printf("[%d %d]", first->RA, first->grade);
  else printf("nao");
  printf(" FIM DO TESTE \n");
  return first;
}

int antecessor(linkedNode *node1, linkedNode *node2){
  do{
    node1 = node1->next;
  } while(node1 ? node1 != node2 : 0);
  if(node1 == node2)
    return 1;
  return 0;
}

void mergeSort(linkedNode *low, linkedNode *high){

    if(antecessor(low, high)){
      printf("%d %d    ===== ", low ? low->RA : -50, high ? high->RA : -50);
      linkedNode *mid = midNode(low, high);
      mergeSort(low, mid);
      mergeSort(mid->next, high);

    //merge(low, mid, high);
    }

}

void insertNode(linkedNode **linkedList, int RA, int grade){
  linkedNode *tmp = *linkedList, *last = NULL;

  while(tmp ? tmp->RA != RA : 0){
    last = tmp;
    tmp = tmp->next;
  }

  if(!tmp){
    // caso RA nao esteja na lista, ele eh adicionado
    linkedNode *newNode = malloc(sizeof(linkedNode));
    if(newNode == NULL) return;

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
/*
void merge(linkedNode *low, linkedNode *mid, linkedNode *high){
  linkedNode *tmp = mid, *aux = NULL;
  while(low != mid->next && tmp != high->next){
    if(low->RA < tmp->RA){
      insertNode(&aux, low->RA, low->grade);
      low = low->next;
    }
    else{
      insertNode(&aux, tmp->RA, tmp->grade);
      tmp = tmp->next;
    }
  }
  while(low != mid->next){
    insertNode(&aux, low->RA, low->grade);
    low = low->next;
  }
  while(tmp != high->next){
    insertNode(&aux, tmp->RA, tmp->grade);
    tmp = tmp->next;
  }
  //printList(aux);
  //deleteList(aux);
  printf("acabou");
}*/

int main(){
  int input = 1, RA, grade, mode;
  linkedNode *linkedList = NULL, *high = NULL;

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
          high = linkedList;
          while(high->next)
            high = high->next;
          mergeSort(linkedList, high);

        break;

        case 9:   // Imprime lista ligada

        break;
    }
  }
  deleteList(linkedList);
  return 0;
}
