#include <stdio.h>
#include <stdlib.h>

typedef struct avlTreeNode avlTreeNode;
struct avlTreeNode{
  int RA;
  int grade;
  int height;
  // unsigned short balanceFactor;
  avlTreeNode *left, *right;
};

void updateHeight (avlTreeNode *n){
    if(!n) return;
    int hl = (n->left)  ? n->left->height : -1;
    int hr = (n->right) ? n->right->height : -1;
    n->height = (hl > hr ? hl : hr) + 1;
}

int balanceFactor(avlTreeNode *n) {
	if (!n)
		return 0;
	int hl = (n->left)  ? n->left->height  : -1,
	    hr = (n->right) ? n->right->height : -1;
	return hl - hr;
}

/* Rotacao simples a direita
*  o desbalanceamento estah a esquerda-esquerda
*  a subarvore esquerda de p estah mais pesada
*/
void caseLLrotateRight(avlTreeNode **pRoot) {
	avlTreeNode *p = *pRoot, *leftChild = p->left;

	p->left = leftChild->right;
	leftChild->right = p;

	updateHeight(p); // a altura do filho esquerdo se mantem o mesmo
  *pRoot = leftChild;
}

/* Rotacao simples a esquerda
*  o desbalanceamento estah a direita-direita
*  a subarvore direita de p estah mais pesada
*/
void caseRRrotateLeft(avlTreeNode **pRoot) {
	avlTreeNode *p = *pRoot, *rightChild = p->right;

  p->right = rightChild->left;
	rightChild->left = p;

	updateHeight(p);   // a altura do filho direito se mantem o mesmo
  *pRoot = rightChild;
}

/* Rotacao dupla a direita
* uma rotacao a esquerda e, depois, uma a direita
* a subarvore esquerda estah mais pesada
*/
void caseLRrotateLeftRight(avlTreeNode **pRoot) {
	avlTreeNode *p = *pRoot, *leftChild = p->left, *rightgrandChild = leftChild->right;
	// Rotacao a esquerda (leftChild)
	leftChild->right = rightgrandChild->left;
	rightgrandChild->left = leftChild;

	// Rotacao a direita (p)
	p->left = rightgrandChild->right;
	rightgrandChild->right = p;

	// atualiza todas as alturas
	updateHeight(p);
	updateHeight(leftChild);
	updateHeight(rightgrandChild);
	*pRoot = rightgrandChild;
}

/* Rotacao dupla a esquerda
*  uma rotacao a direita e, depois, uma a esquerda
*  subarvore direita estah mais pesada
*/
void caseRLrotateRightLeft(avlTreeNode **pRoot) {
	avlTreeNode *p = *pRoot, *rightChild = p->right, *leftgrandChild = rightChild->left;

	// rotacao a direita (rightChild)
	rightChild->left = leftgrandChild->right;
	leftgrandChild->right = rightChild;

	// rotacao a esquerda (p)
	p->right = leftgrandChild->left;
	leftgrandChild->left = p;

	// Atualiza todas a alturas
	updateHeight(p);
	updateHeight(rightChild);
	updateHeight(leftgrandChild);
	*pRoot = leftgrandChild;
}

int avlCheckBalance (avlTreeNode **tree){
  int balanced = 0;
  if (balanceFactor(*tree) == 2) { // lado esquerdo mais pesado
    balanced = 1;
    printf("[No desbalanceado: %d]\n", (*tree)->RA);

    if (balanceFactor((*tree)->left) == 1 || balanceFactor((*tree)->left) == 0){
      // sem joelho, rotacao simples
      printf("[Rotacao: SD]\n");
      printf("[x=%d y=%d z=%d]\n", (*tree)->left->left->RA, (*tree)->left->RA, (*tree)->RA);
      caseLLrotateRight(tree);
    }
    else{ // com joelho, rotacao dupla
      printf("[Rotacao: DD]\n");
      printf("[x=%d y=%d z=%d]\n", (*tree)->left->RA, (*tree)->left->right->RA, (*tree)->RA);
      caseLRrotateLeftRight(tree);
    }
  }
  else if (balanceFactor(*tree) == -2) { // lado direito mais pesado
    balanced = 1;
    printf("[No desbalanceado: %d]\n", (*tree)->RA);

    if (balanceFactor((*tree)->right) == -1 || balanceFactor((*tree)->right) == 0){
      // sem joelho, rotacao simples
      printf("[Rotacao: SE]\n");
      printf("[x=%d y=%d z=%d]\n", (*tree)->RA, (*tree)->right->RA, (*tree)->right->right->RA);
      caseRRrotateLeft(tree);
    }
    else{ // com joelho, rotacao dupla
      printf("[Rotacao: DE]\n");
      printf("[x=%d y=%d z=%d]\n", (*tree)->RA, (*tree)->right->left->RA, (*tree)->right->RA);
      caseRLrotateRightLeft(tree);
    }
  }
  else
    updateHeight(*tree);

  return balanced;
}

void avlInsert(avlTreeNode **treeRoot,	int RA, int grade, int *balanced) {
	if (*treeRoot == NULL) {
    // atualiza a raiz para apontar a um novo nodo
		avlTreeNode *newNode = malloc(sizeof(avlTreeNode));
		*treeRoot = newNode;
    if (!newNode) return;

		newNode->RA = RA;
    newNode->grade = grade;
		newNode->left = newNode->right = NULL;
		newNode->height = 0;
		return;
	}

	if (RA == (*treeRoot)-> RA){
    (*treeRoot)->grade = grade;
    return;
  }

	if (RA < (*treeRoot)->RA)  // move-se recursavimanete para a esquerda
		avlInsert(&(*treeRoot)->left, RA, grade, balanced);
	else //  move-se recursivamente para a direita
		avlInsert(&(*treeRoot)->right, RA, grade, balanced);

  *balanced += avlCheckBalance(treeRoot) ;
}

avlTreeNode *minNode(avlTreeNode *t){
  while(t->left)
    t = t->left;
  return t;
}

void avlRemoveNode (avlTreeNode **treeRoot, int RA, int *balanced){
  avlTreeNode *tmp = NULL;
  if (!(*treeRoot))
    return;

  if (RA < (*treeRoot)->RA)
    avlRemoveNode(&(*treeRoot)->left, RA, balanced);
  else if (RA > (*treeRoot)->RA)
    avlRemoveNode(&(*treeRoot)->right, RA, balanced);
  else{
      /* Verificamos primeiros os casos em que ha um unico filho
      * Apos, se ha os dois filhos, reduzimos ao primeiro casos*/
      if (!(*treeRoot)->left){ // sem filho a esquerda
          tmp = *treeRoot;
          *treeRoot = (*treeRoot)->right;
          free(tmp);
      }
      else if (!(*treeRoot)->right){ // sem filho a direita
          tmp = *treeRoot;
          *treeRoot = (*treeRoot)->left;
          free(tmp);
      }
      else{ // caso haja os dois filhos
        tmp = minNode((*treeRoot)->right);
        (*treeRoot)->RA = tmp->RA;
        (*treeRoot)->grade = tmp->grade;
        avlRemoveNode(&(*treeRoot)->right, tmp->RA, balanced);
      }
      updateHeight(*treeRoot);
  }
	*balanced += avlCheckBalance(treeRoot);
  updateHeight(*treeRoot);
}

void printPostOrder(avlTreeNode *root){
	if (!root) return;
	printPostOrder(root->left);
	printPostOrder(root->right);
  printf("%d ", root->RA);
}

void avlDelete(avlTreeNode *t){
  if(!t) return;
  avlDelete(t->left);
  avlDelete(t->right);
  free(t);
}

avlTreeNode *avlSearch(avlTreeNode *t, int RA, int *grade, int *count){
  if(!t){
    *grade = -1;
    return NULL;
  }
  (*count)++;
  if(RA == t->RA){
    *grade = t->grade;
    return t;
  }
  if(RA < t->RA) avlSearch(t->left, RA, grade, count);
  else avlSearch(t->right, RA, grade, count);
}

int main(){
  int RA, grade, count = 0, balanced = 1;
  avlTreeNode *t = NULL;
  char input = '\0';

  while(input != 'P'){
    balanced = 0;
    scanf("\n%c", &input);
    switch (input) {
      case 'I':   // insere um novo nodo na arvore
        scanf("%d %d", &RA, &grade);
        avlInsert(&t, RA, grade, &balanced);
        if(!balanced)
          printf("[Ja esta balanceado]\n");
      break;

      case 'R':   // remove um nodo da arvore
        scanf("%d", &RA);
        avlRemoveNode(&t, RA, &balanced);
        if(!balanced)
          printf("[Ja esta balanceado]\n");
      break;

      case 'B':   // busca um novo na arvore
        scanf("%d", &RA);
        avlSearch(t, RA, &grade, &count);
        printf("C=%d Nota=%d\n", count, grade);
        count = 0;
      break;

      case 'A':   // imprime a altura da arvore
        printf("A=%d\n", t ? t->height : -1);
      break;

      case 'P':   // Imprime a arvore em pos-ordem
        printf("[");
        printPostOrder(t);
        printf("]\n");
        avlDelete(t);
      break;
    }
  }
  return 0;
}
