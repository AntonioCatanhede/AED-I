#include <stdio.h>
#include <stdlib.h>

typedef struct linkedNode linkedNode;
struct linkedNode{
  int RA;
  linkedNode *next;
};

typedef struct treeNode treeNode;
struct treeNode{
  int value;
  treeNode *pLeft, *pRight;
};

// Funcoes para a arvore de busca binaria
treeNode *searchTreeNode(treeNode *t, int value, int *count){
  if(!t) return NULL;
  (*count)++;
  if(value == t->value) return t;
  if(value < t->value) searchTreeNode(t->pLeft, value, count);
  else searchTreeNode(t->pRight, value, count);
}

treeNode *insertTreeNode(treeNode *t, int value){
  if(!t){
    treeNode *tmp = malloc(sizeof(treeNode));
    if(tmp){
      tmp->value = value;
      tmp->pRight = tmp->pLeft = NULL;
    }
    return tmp;
  }
  if(value < t->value)
    t->pLeft = insertTreeNode(t->pLeft, value);
  else if(value > t->value)
    t->pRight = insertTreeNode(t->pRight, value);
  else
    t->value = value;
  return t;
}

// Funcoes para a lista ligada em ORDEM CRESCENTE
linkedNode *inserLinkedNode(linkedNode *seq, int RA){
  linkedNode *cur = seq, *prev = NULL;
  linkedNode *tmp = malloc(sizeof(linkedNode));
  if(!tmp) return NULL;

  if(!cur){
    tmp->RA = RA;
    tmp->next = NULL;
    return tmp;
  }
  while(cur && cur->RA < RA){
    prev = cur;
    cur = cur->next;
  }
  if(!cur){  // Chegou no ultimo elemento
    prev->next = tmp;
    tmp->next = NULL;
    tmp->RA = RA;
    return seq;
  }
  else if (!prev){ // parou no primeiro elemento
    tmp->next = cur;
    tmp->RA = RA;
    return tmp;
  }
  else{
    prev->next = tmp;
    tmp->RA = RA;
    tmp->next = cur;
    return seq;
  }
}

linkedNode *searchLinkedNode(linkedNode *seq, int RA, int *count){
  while(seq){
    (*count)++;
    if(!seq || seq->RA >= RA) break;
    seq = seq->next;
  }
  return NULL;
}

int main(){
  char inst = 'A';
  int RA = '1', c_ln = 0, c_tn = 0;
  treeNode *t = NULL;
  linkedNode *seq = NULL;

  while(inst!='P' || RA !=0){
    scanf("%c %d", &inst, &RA);
    if(inst == 'I'){
      t = insertTreeNode(t, RA);
      seq = inserLinkedNode(seq, RA);
    }
    else if(inst == 'B'){
      searchTreeNode(t, RA, &c_tn);
      searchLinkedNode(seq, RA, &c_ln);
      printf("L=%d A=%d\n", c_ln, c_tn);
      c_tn = c_ln = 0;
    }
  }

  return 0;
}
