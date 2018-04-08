#include <stdio.h>
#include <stdlib.h>

typedef struct linkedNode linkedNode;
struct linkedNode{
  int RA;
  int codTopic;
  linkedNode *next;
};

linkedNode *appendNode (linkedNode *first, int RA, int codTopic){
  linkedNode *prev = NULL, *cur, *tmp = malloc(sizeof(linkedNode));
  if(tmp == NULL) return NULL;

  tmp->RA = RA;
  tmp->codTopic = codTopic;
  tmp->next = NULL;

  if(first != NULL){
    cur = first;
    while(cur != NULL ? cur->RA != RA : 0){
      prev = cur;
      cur = cur->next;
    }
    if(cur == NULL){
      prev->next = tmp;
    }
    else{
      while(cur != NULL ? cur->RA == RA : 0){
        prev = cur;
        cur = cur->next;
      }
      if(cur == NULL){
        prev->next = tmp;
      }
      else{
        prev->next = tmp;
        tmp->next = cur;
      }
    }
  }
  return tmp;
}

linkedNode *makeList(){
  int RA, codTopic;
  linkedNode *first = NULL, *seq;
  do{
    scanf("%d", &RA);
    scanf("%d", &codTopic);
    if (RA != -1 || codTopic != -1){
      seq = appendNode(first, RA, codTopic);
      if(first == NULL)
        first = seq;
    }
  } while(RA != -1 || codTopic != -1);
  return first;
}

void printList(linkedNode *seq){
  while(seq != NULL){
    printf("%d %d\n", seq->RA, seq->codTopic);
    seq = seq->next;
  }
}

int main(){
    linkedNode *seq = makeList();
    printList(seq);
    return 0;
}
