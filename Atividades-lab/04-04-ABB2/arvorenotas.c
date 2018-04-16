#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode treeNode;
struct treeNode{
  int RA;
  int grade;
  treeNode *pLeft, *pRight;
};

// Funcoes para a arvore de busca binaria
treeNode *searchTreeNode(treeNode *t, int RA, int *grade, int *count){
  if(!t){
    *grade = -1;
    return NULL;
  }
  (*count)++;
  if(RA == t->RA){
    *grade = t->grade;
    return t;
  }
  if(RA < t->RA) searchTreeNode(t->pLeft, RA, grade, count);
  else searchTreeNode(t->pRight, RA, grade, count);
}

treeNode *insertTreeNode(treeNode *t, int RA, int grade){
  if(!t){   // cria o nodo inicial na ABB
    treeNode *tmp = malloc(sizeof(treeNode));
    if(tmp){
      tmp->RA = RA;
      tmp->grade = grade;
      tmp->pRight = tmp->pLeft = NULL;
    }
    return tmp;
  }
  if(RA < t->RA)
    t->pLeft = insertTreeNode(t->pLeft, RA, grade);
  else if(RA > t->RA)
    t->pRight = insertTreeNode(t->pRight, RA, grade);
  else{
    t->grade = grade;
  }
  return t;
}

treeNode *minNode(treeNode *t){
  while(t->pLeft)
    t = t->pLeft;
  return t;
}

treeNode* deleteNode(struct treeNode* root, int RA)
{
    if (!root)
      return root;

    if (RA < root->RA)
      root->pLeft = deleteNode(root->pLeft, RA);
    else if (RA > root->RA)
      root->pRight = deleteNode(root->pRight, RA);
    else
    {
        if (!root->pLeft)
        {
            struct treeNode *tmp = root->pRight;
            root = NULL;
            free(root);
            return tmp;
        }
        else if (!root->pRight)
        {
            struct treeNode *tmp = root->pLeft;
            root = NULL;
            free(root);
            return tmp;
        }

        struct treeNode* tmp = minNode(root->pRight);
        root->RA = tmp->RA;
        root->grade = tmp->grade;
        root->pRight = deleteNode(root->pRight, tmp->RA);
    }
    return root;
}

void treeHeight(treeNode *t, int *height){
  if(!t) return;

  int h1 = 0, h2 = 0;
  (*height)++;
  treeHeight(t->pLeft, &h1);
  treeHeight(t->pRight, &h2);
  if(h1 < h2)
    *height += h2;
  else
    *height += h1;
}

void deleteTree(treeNode *t){
  if(!t) return;
  deleteTree(t->pLeft);
  deleteTree(t->pRight);
  free(t);
}

int main(){
  char inst = '\0';
  int RA, grade, height, count;
  treeNode *t = NULL, *tmp;

  while(inst!='P'){
    scanf("\n%c", &inst);
    if(inst == 'I'){
      scanf("%d %d", &RA, &grade);
      t = insertTreeNode(t, RA, grade);
    }
    else if(inst == 'R'){
      scanf("%d", &RA);
      t = deleteNode(t, RA);
    }
    else if(inst == 'B'){
      scanf("%d", &RA);
      count = 0;
      searchTreeNode(t, RA, &grade,  &count);
      printf("C=%d Nota=%d\n", count, grade);
    }
    else if(inst == 'A'){
      height = -1;
      treeHeight(t, &height);
      printf("A=%d\n", height);

    }
  }

  deleteTree(t);

  return 0;
}
