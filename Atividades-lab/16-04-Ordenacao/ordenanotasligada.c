#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedNode linkedNode;
struct linkedNode{
  int RA;
  int grade;
  char name[51];
  linkedNode *next, *last;
};

void attrString (char *ch1, char *ch2){
  *ch1 = *ch2;
  if(*ch2 == '\0') return;
  attrString(++ch1, ++ch2);
}

void *insertNode(linkedNode **linkedList, int RA, int grade, char *name){
  linkedNode *tmp = *linkedList, *last = NULL;

  while(tmp ? tmp->RA != RA : 0){
    last = tmp;
    tmp = tmp->next;
  }

  if(!tmp){
    linkedNode *newNode = malloc(sizeof(linkedNode));
    if(newNode == NULL) return NULL;

    newNode->RA = RA;
    newNode->grade = grade;
    attrString(newNode->name, name);
    newNode->next = newNode->last = NULL;

    if(!last) // primeiro nodo
      *linkedList = newNode;
    else{
      last->next = newNode;
      newNode->last = last;
    }
  }
  else{
    tmp->grade = grade;
    attrString(tmp->name, name);
  }
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

  attrString(tmpChar, node1->name);
  attrString(node1->name, node2->name);
  attrString(node2->name, tmpChar);
}
// modo 1 -> ordenacao por RA, modo 2 -> ordenacao por nome
long int selectionSort(linkedNode *linkedList, int mode){
  linkedNode *min, *tmp;
  long int comp = 0;

  if(!linkedList) return 0;

  while(linkedList->next){
    min = linkedList;

    for(tmp = linkedList->next; tmp; tmp = tmp->next){
      if(mode == 1 ? min-> RA > tmp->RA : strcmp(min->name, tmp->name) > 0)
        min = tmp;
      comp++;
    }

    if(linkedList->RA != min->RA)
      swapNode(linkedList, min);
    linkedList = linkedList->next;
  }
  return comp;
}

// modo 1: por RA, modo 2: por nome
long int  insertionSort(linkedNode *linkedList, int mode){
  linkedNode *tmp1, *tmp2, *key;
  long int comp = 0;

  if(!linkedList) return 0;

  for(tmp1 = linkedList->next; tmp1; tmp1 = tmp1->next){
    key = tmp1;
    tmp2 = tmp1->last;
    while(tmp2 ? ( ++comp && (mode == 1) ?  tmp2->RA > key->RA : strcmp(tmp2->name, key->name) > 0) : 0){
      swapNode(tmp2, tmp2->next);
      key = tmp2;
      tmp2 = tmp2->last;
    }
  }
  return comp;
}

int searchList(linkedNode *tmp, int RA){
  if(!tmp) return -1;
  if(tmp->RA == RA) return 0;
  int cont = searchList(tmp->next, RA);
  return (cont == -1) ? cont : cont + 1;
}

void printList(linkedNode *tmp){
  if(!tmp) return;
  printf("[%d %s %d]\n", tmp->RA, tmp->name, tmp->grade);
  printList(tmp->next);
}

void deleteList(linkedNode *tmp){
  if(!tmp) return;
  deleteList(tmp->next);
  free(tmp);
}

int main(){
  char input = 'A', name[50];
  int RA, grade, mode, algo;
  long int comp;
  linkedNode *linkedList = NULL;

  while(input != 'P'){
    scanf("\n%c", &input);
    switch (input) {
        case 'I':   // Insere novo nodo
          scanf("%d %s %d", &RA, name, &grade);
          insertNode(&linkedList, RA, grade, name);
        break;

        case 'O':   // Ordena lista
          scanf("%d %d", &algo, &mode);
          if(algo == 1)
            comp = selectionSort(linkedList, mode);
          else if(algo == 2)
            comp = insertionSort(linkedList, mode);
          printf("Comparacoes=%ld\n", comp);
        break;

        case 'B':   // Busca nodo
          scanf("%d", &RA);
          printf("Pos=%d\n", searchList(linkedList, RA));
        break;

        case 'M':   // Imprime lista ligada
          printList(linkedList);
        break;
    }
  }
  deleteList(linkedList);
  return 0;
}

/* 
void swapNode(linkedNode *node1, linkedNode *node2){
  linkedNode *swap = node2->last;
  node2->last = node1->last;
  if(swap != node1){
    node1->last = swap;
    if(node1->last) node1->last->next = node1;
  }
  else
    node1->last = node2;

  swap = node1->next;
  node1->next = node2->next;
  if(swap != node2){
    node2->next = swap;
    if(node2->next) node2->next->last = node2;
  }
  else
    node2->next = node1;

  if(node1->next) node1->next->last = node1;
  if(node2->last) node2->last->next = node2;
}

// modo 1 -> ordenacao por RA, modo 2 -> ordenacao por nome
long int selectionSort(linkedNode *linkedList, int mode){
  linkedNode *min, *tmp;
  long int comp = 0;

  while(linkedList->next){
    min = linkedList;

    for(tmp = linkedList->next; tmp; tmp = tmp->next){
      if(mode == 1 ? min-> RA > tmp->RA : strcmp(min->name, tmp->name) > 0)
        min = tmp;
      comp++;
    }

    if(linkedList->RA != min->RA)
      swapNode(linkedList, min);
    linkedList = min->next;
  }
  return comp;
}

void inNode(linkedNode *node1, linkedNode *node2){
  if(node2->last) node2->last->next = node2->next;
  if(node2->next) node2->next->last = node2->last;

  linkedNode *tmp = node1->next;
  node1->next = node2;
  node2->next = tmp;
  node2->last = node1;
  if(node2->next) node2->next->last = node2;
}

// modo 1: por RA, modo 2: por nome
long int  insertionSort(linkedNode *linkedList, int mode){
  linkedNode *tmp1, *tmp2, *tmp3;
  long int comp = 0;

  for(tmp1 = linkedList->next; tmp1; tmp1 = tmp1->next){
    tmp2 = tmp1->last;
    while(tmp2 && ++comp && (mode == 1) ?  tmp2->RA > tmp1->RA : strcmp(tmp2->name, tmp1->name) > 0){
      tmp2 = tmp2->last;
    }

    if(tmp2 ? tmp2->next != tmp1: 0){
      tmp3 = tmp1->last;
      inNode(tmp2, tmp1);
      tmp1 = tmp3;
    }
  }
  return comp;
}

*/
