#include <stdio.h>
#include <stdlib.h>

typedef struct avlTreeNode avlTreeNode;
struct avlTreeNode{
  char word[20];
  int count;
  avlTreeNode *left, *right;
};

void updateHeight (avlTreeNode *n){
    if(!n) return;
    int hl = (n->left) ? n->left->height : -1;
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
  *pRoot = leftChild;

	updateHeight(p); // a altura do filho esquerdo se mantem o mesmo
}

/* Rotacao simples a esquerda
*  o desbalanceamento estah a direita-direita
*  a subarvore direita de p estah mais pesada
*/
void caseRRrotateLeft(avlTreeNode **pRoot) {
	avlTreeNode *p = *pRoot, *rightChild = p->right;

  p->right = rightChild->left;
	rightChild->left = p;
  *pRoot = rightChild;

	updateHeight(p);   // a altura do filho direito se mantem o mesmo
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

void avlCheckBalance (avlTreeNode **tree){
  if (balanceFactor(*tree) == 2) { // lado esquerdo mais pesado
    if (balanceFactor((*tree)->left) == 1 || balanceFactor((*tree)->left) == 0)
      caseLLrotateRight(tree);  // sem joelho, rotacao simples
    else
      caseLRrotateLeftRight(tree); // com joelho, rotacao dupla
  }
  else if (balanceFactor(*tree) == -2) { // lado direito mais pesado
    if (balanceFactor((*tree)->right) == -1 || balanceFactor((*tree)->right) == 0)
      caseRRrotateLeft(tree); // sem joelho, rotacao simples
    else
      caseRLrotateRightLeft(tree); // com joelho, rotacao dupla
  }
  else
    updateHeight(*tree);
}

void avlInsert(avlTreeNode **treeRoot,	char word, int count) {
	if (*treeRoot == NULL) {
    // atualiza a raiz para apontar a um novo nodo
		avlTreeNode *newNode = malloc(sizeof(avlTreeNode));
		*treeRoot = newNode;

    if (!newNode)
      return;

		newNode->key = key;
		newNode->left = newNode->right = NULL;
		newNode->height = 0;
		return;
	}

	if (key == (*treeRoot)-> key)
    return;

  if (key < (*treeRoot)->key)  // move-se recursavimanete para a esquerda
    avlInsert(&(*treeRoot)->left, key);
  else //  move-se recursivamente para a direita
    avlInsert(&(*treeRoot)->right, key);

  avlCheckBalance(treeRoot) ;
}

avlTreeNode *minNode(avlTreeNode *t){
  while(t->left)
    t = t->left;
  return t;
}

void avlRemoveNode (avlTreeNode **treeRoot, int key){
  avlTreeNode *tmp = NULL;
  if (!(*treeRoot))
    return;

  if (key < (*treeRoot)->key)
    avlRemoveNode(&(*treeRoot)->left, key);
  else if (key > (*treeRoot)->key)
    avlRemoveNode(&(*treeRoot)->right, key);
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
        (*treeRoot)->key = tmp->key;
        avlRemoveNode(&(*treeRoot)->right, tmp->key);
      }
      updateHeight(*treeRoot);
  }
	avlCheckBalance(treeRoot);
  updateHeight(*treeRoot);
}

void printTree(avlTreeNode *root)
{
	if (!root) return;
  printf("%s ", root->word);
  printf("%d\n", root->count);
  printTree(root->left);
  printTree(root->right);
}


int main(){

  return 0;
}
